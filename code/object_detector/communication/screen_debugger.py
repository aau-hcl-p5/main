"""
Everything regarding debugging the data to the screen.
So when doing some kind of object recognition and you want to draw on the screen,
these methods help.
"""
from typing import Callable

import cv2
import numpy as np

from algorithms.utilities import Vector


def screen_debug_wrapper(
        location: Vector,
        frame: np.ndarray,
        size: int = 10,
) -> None:  # pragma: no cover
    """
    A wrapper that takes a algorithm as input and runs it,
    and then displays the output to a image renderer
    :param location: location to highlight
    :param frame: the current frame
    :param size: the size of the debugging point
    """

    if location:
        location = location + Vector(frame.shape[1], frame.shape[0])//2
        for x in range(-size, size):
            for y in range(-size, size):
                new_x = int(location.x + x)
                new_y = int(location.y + y)
                try:
                    frame[new_y, new_x] = [0, 0x70, 0]
                except IndexError:
                    pass

    cv2.imshow('debug view', frame)  # pylint: disable=no-member

