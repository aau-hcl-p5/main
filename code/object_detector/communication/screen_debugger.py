"""
Everything regarding debugging the data to the screen.
So when doing some kind of object recognition and you want to draw on the screen,
these methods help.
"""

import cv2

from algorithms import Result, Status, Vector
from webcam import VideoController
from .output_device import OutputDevice

SIZE_OF_MARKER = 10


class ScreenDebugger(OutputDevice):
    """
    Everything regarding debugging the data to the screen.
    So when doing some kind of object recognition and you want to draw on the screen,
    these methods help.
    """
    def __init__(self, video_controller: VideoController) -> None:
        """
        Initializes the debugger based on the video feed, and results from the algorithms
        :param video_controller: The current in-use video controller
        """
        self.video_controller = video_controller

    def write_data(self, data: Result) -> None:
        location = data.location
        frame = self.video_controller.get_last_frame()
        if data.status is Status.TARGET_FOUND:
            location = location + Vector(frame.shape[1], frame.shape[0]) // 2
            for x in range(-SIZE_OF_MARKER, SIZE_OF_MARKER):
                for y in range(-SIZE_OF_MARKER, SIZE_OF_MARKER):
                    new_x = int(location.x + x)
                    new_y = int(location.y + y)
                    try:
                        frame[new_y, new_x] = [0, 0x70, 0]
                    except IndexError:
                        pass

        cv2.imshow('debug view', frame)  # pylint: disable=no-member
