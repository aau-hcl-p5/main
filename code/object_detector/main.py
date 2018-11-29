"""
The entry file of the object detection module.
This project is intended to contain half of the F.L.A.T project
The project is explained in detail in the report at
https://github.com/aau-hcl-p5/main
This program is intended to analyze input from a webcam,
and then find a ball or balloon in the picture,
and then send the relative location, compared to a given crosshair,
to the other device in the system, being the NXT;
which will handle movement of motors etc.


"""
import argparse
from typing import Callable, Union

import cv2
import numpy as np

import algorithms
import webcam
from algorithms import Vector, screen_location_to_relative_location
from calibration import save_data
from communication import NxtUsb, screen_debug_wrapper, Status
from communication.nxt_usb import DeviceNotFound
from test_data import Generator


class FlatController:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: Callable[[np.ndarray], Vector],
                 capture_type: webcam.CaptureDeviceType = webcam.CaptureDeviceType.CAMERA,
                 calibration_algorithm: Union[Callable[[], None], None] = None,
                 ) -> None:
        """
        Initializes the controller
        :type calibration_algorithm: a function that takes calibration packages,
            and handles them in some unknown way (either logs them or sends them back)
        :param algorithm: The algorithm to use for image processing
        :param capture_type: What type the capturing device should be.
        """
        self.video_controller = webcam.VideoController(capture_type)
        self._algorithm = algorithm
        try:
            self.usb_connection = NxtUsb()
            if calibration_algorithm:
                print("Calibrate? (Y/n)")
                if input() not in ['n', 'N']:
                    calibration_algorithm(self.usb_connection)
        except DeviceNotFound as e:
            print(f"Usb initialization failed. Starting without ({e})")
            self.usb_connection = None

        self.terminating = False

    def run(self) -> None:
        """
        Start a separate thread for running the 'run' method,
        and continuously run this.
        """
        while True:
            loc = self._get_next_location()
            if self.usb_connection is not None:
                if loc is not None:
                    self.usb_connection.write_location(loc)
                else:
                    self.usb_connection.write_status(Status.NO_TARGET_FOUND)

            k = cv2.waitKey(5) & 0xFF  # escape char
            if k == 27:
                break

    def _get_next_location(self) -> Vector:
        """

        :return: Vector in range {algorithms.COMMUNICATION_OUT_RANGE}
        """
        frame = self.video_controller.get_current_frame()
        timer = cv2.getTickCount()
        res = screen_location_to_relative_location(frame, self._algorithm(frame))
        fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
        cv2.putText(frame, "FPS : " + str(int(fps)), (100, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50, 170, 50), 2)
        screen_debug_wrapper(res, frame)
        return res


# check if this file is run directly.
if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='thresh_moment',
        type=str, metavar='[name]',
        help="Choose which algorithm to run "
             f"[{', '.join(a.name for a in algorithms.AlgorithmType)}]. default='thresh_moment'")

    PARSER.add_argument(
        '-g', '--generate',
        dest='test_data_dir', default=None,
        type=str, metavar='[test_data_dir]',
        help="Path to a directory containing video files for test data. default=None")

    PARSER.add_argument(
        '-d', '--delete',
        dest='delete_test_data', default=False,
        type=bool, metavar='[delete_test_data]',
        help="Whether to delete generated test data. default=False")

    ARGS = PARSER.parse_args()

    if ARGS.test_data_dir is None:
        cont = FlatController(algorithms.get_from_str(ARGS.alg_name), calibration_algorithm=save_data.save_packages)
        cont.run()
    else:
        # Generate test data
        generator = Generator(algorithms.get_from_str(ARGS.alg_name), ARGS.test_data_dir)
        if ARGS.delete_test_data:
            generator.remove_results()
        else:
            generator.generate()
