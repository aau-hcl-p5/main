from typing import Callable, Union, List, Optional, Tuple

import cv2
import numpy as np
from webcam import VideoController

from algorithms import screen_location_to_relative_location, Vector
from output_devices import Status, render_debugscreen, NxtUsb
from output_devices.output_device import OutputDevice


class FlatController:
    """
    The controller that handles the image processing and output_devices with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: Callable[[np.ndarray], Optional[Tuple[Vector, bool]]],
                 output_device: OutputDevice,
                 input_device: VideoController,
                 calibration_algorithm: Union[Callable[[OutputDevice], None], None] = None,
                 debug=True
                 ) -> None:
        """
        Initializes the controller

        :type debug: whether to open the debug view
        :param algorithm: The algorithm to use for image processing
        :param output_device: The device to send data to
        :param input_device: What type the capturing device should be.
        :param calibration_algorithm: a function that takes calibration packages,
            and handles them in some unknown way (either logs them or sends them back)
        """
        self.debug = debug
        self.input_device = input_device
        self._algorithm = algorithm
        self.output_device = output_device

        if calibration_algorithm:
            print("Calibrate? (y/N)")
            if input() in ['y', 'Y']:
                calibration_algorithm(self.output_device)

        self.terminating = False

    def _iteration(self) -> None:
        data = self._get_next_location()
        if data is not None:
            # TODO maybe refactor
            self.output_device.write_location(data)
        else:
            self.output_device.write_status(Status.NO_TARGET_FOUND)

    def run(self) -> None:
        """
        Start a separate thread for running the 'run' method,
        and continuously run this.
        """
        while True:
            self._iteration()

            k = cv2.waitKey(5) & 0xFF  # escape char
            if k == 27:
                break

    def _get_next_location(self) -> Optional[Tuple[Vector, bool]]:
        """

        :return: Vector in range {algorithms.COMMUNICATION_OUT_RANGE}
        """
        frame = self.input_device.get_current_frame()
        if self.debug:
            timer = cv2.getTickCount()
        data = screen_location_to_relative_location(frame, self._algorithm(frame))

        if self.debug:
            fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
            cv2.putText(
                frame,
                "FPS : " + str(int(fps)),
                (100, 50),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.75,
                (50, 170, 50),
                2
            )
            render_debugscreen(data, frame)
        return data

