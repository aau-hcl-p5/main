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
from typing import Callable

import cv2
import numpy as np

import algorithms
import webcam
from algorithms import Result, Vector
from communication import NxtUsb
from communication import screen_debug_wrapper


class FlatController:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: Callable[[np.ndarray], Vector],
                 capture_type: webcam.CaptureDeviceType = webcam.CaptureDeviceType.CAMERA) -> None:
        """
        Initializes the controller
        :param algorithm: The algorithm to use for image processing
        :param capture_type: What type the capturing device should be.
        """
        self.video_controller = webcam.VideoController(capture_type)
        self._algorithm = algorithm
        self.usb_connection = NxtUsb()

    def start(self) -> None:
        """
        Start a separate thread for running the 'run' method,
        and continuously run this.
        """
        while 1:
            self._get_next_location()
            k = cv2.waitKey(5) & 0xFF
            if k == 27:
                break
        pass

    def stop(self) -> None:
        """
        stop the thread running the FLAT object recognition
        """
        self.usb_connection.disconnect()

    def _run(self):
        pass

    def _get_next_location(self) -> Vector:
        res = screen_debug_wrapper(self._algorithm, self.video_controller.get_current_frame())
        try:
            self.usb_connection.write_data(Result(int(res.x / 10), int(res.y / 10), 1))
        except:
            pass
        return res


# check if this file is run directly.
if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='goturn',
        type=str, metavar='[name]',
        help="Choose which algorithm to run ['goturn', 'yolo']. default='goturn'")

    ARGS = PARSER.parse_args()
    FlatController(algorithms.ObjectFillController().locate_center).start()
