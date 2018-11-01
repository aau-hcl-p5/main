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
import datetime
import sys
import time
from threading import Thread
from typing import Callable, Optional

import cv2
import numpy as np

import algorithms
import webcam
from algorithms import Result, Vector, screen_location_to_relative_location
from communication import NxtUsb
from communication import screen_debug_wrapper
from communication.nxt_usb import DeviceNotFound


class FlatController:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: Callable[[np.ndarray], Vector],
                 capture_type: webcam.CaptureDeviceType = webcam.CaptureDeviceType.CAMERA,
                 ) -> None:
        """
        Initializes the controller
        :param algorithm: The algorithm to use for image processing
        :param capture_type: What type the capturing device should be.
        """
        self.video_controller = webcam.VideoController(capture_type)
        self._algorithm = algorithm
        try:
            self.usb_connection = NxtUsb()
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
                    ts = 1  # nt(time.time())
                    self.usb_connection.write_data(Result(loc, ts))
                else:
                    self.usb_connection.write_data(None)
            k = cv2.waitKey(5) & 0xFF  # escape char
            if k == 27:
                break

    def _get_next_location(self) -> Vector:
        """

        :return: Vector in range {algorithms.COMMUNICATION_OUT_RANGE}
        """
        frame = self.video_controller.get_current_frame()
        res = screen_location_to_relative_location(frame, self._algorithm(frame))
        screen_debug_wrapper(res, frame)
        return res


# check if this file is run directly.
if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='obj_fill',
        type=str, metavar='[name]',
        help="Choose which algorithm to run "
             f"[{', '.join(a.name for a in algorithms.AlgorithmType)}]. default='obj_fill'")

    ARGS = PARSER.parse_args()

    cont = FlatController(algorithms.get_from_str(ARGS.alg_name))
    cont.run()
