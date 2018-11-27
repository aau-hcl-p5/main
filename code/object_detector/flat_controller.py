from typing import List, Union, Callable, Optional

import cv2
import numpy as np

from webcam import VideoController
from algorithms import Result, Status, Vector
from communication import NxtUsb, OutputDevice


class FlatController:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: Callable[[np.ndarray], Vector],
                 video_controller: VideoController,
                 output_devices: Union[OutputDevice, List[OutputDevice], None] = None,
                 ) -> None:
        """
        Initializes the controller
        :param output_devices: The device to send data to
        :param algorithm: The algorithm to use for image processing
        :param video_controller: The controller handling the input video
        :type VideoController
        """
        self.video_controller = video_controller
        self._algorithm = algorithm

        if output_devices is None:
            output_devices = NxtUsb()
        if 
        if not isinstance(output_devices, List):
            output_devices = [output_devices]

        self.output_devices = output_devices
        self.terminating = False

    def run(self) -> None:
        """
        Start a separate thread for running the 'run' method,
        and continuously run this.
        """
        while True:
            loc = self._get_next_location()
            if self.output_devices is not None:
                if loc is not None:
                    for device in self.output_devices:
                        device.write_data(Result(loc, Status.TARGET_FOUND))
                else:
                    for device in self.output_devices:
                        device.write_data(Result(Vector(0, 0), Status.NO_TARGET_FOUND))
            k = cv2.waitKey(5) & 0xFF  # escape char
            if k == 27:
                break

    def _get_next_location(self) -> Vector:
        """

        :return: Vector in range {algorithms.COMMUNICATION_OUT_RANGE}
        """
        frame = self.video_controller.get_current_frame()
        res = screen_location_to_relative_location(frame, self._algorithm(frame))
        return res


COMMUNICATION_OUT_RANGE = 255  # 2**8 -1


def _screen_location_to_relative_location(frame: np.ndarray, position: Optional[Vector],
                                          polynomial: bool = False) -> Optional[Vector]:
    """
    This transforms the location on the screen to a value between -127, 127
    and does this with scaling in the sense of:
    f(x) = (x/480)^2 * 255
    where 480 is the input range, and 255 is the output range.
    :param polynomial: whether to use the linear value or the polynomial
    :param frame: the image that the position is on.
    :param position: The position on the frame
    :return: The output vector in range on x -y  [-127,127]
    """
    if position is None:
        return None

    half_size = Vector(frame.shape[1], frame.shape[0]) // 2

    val = (half_size - position) / half_size

    # dir is used because val.x * val.x will not keep the direction (negative or positive).
    if polynomial:
        return val ** 2 * - val.dir() * (COMMUNICATION_OUT_RANGE // 2)
    else:
        return -val * (COMMUNICATION_OUT_RANGE // 2)
