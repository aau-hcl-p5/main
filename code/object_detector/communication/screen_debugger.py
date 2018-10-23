"""
Everything regarding debugging the data to the screen.
So when doing some kind of object recognition and you want to draw on the screen,
these methods help.
"""
from typing import Callable

import cv2
import numpy as np

from algorithms.utilities import Vector


def screen_debug_wrapper(algorithm: Callable[[np.ndarray], Vector], frame: np.ndarray) -> Vector:
    """
    A wrapper that takes a algorithm as input and runs it,
    and then displays the output to a image renderer
    :param algorithm: The algorithm in question
    :param frame:
    :return:
    """
    target = algorithm(frame)
    # target = Vector(100,100)

    if target:
        for x in range(-10, 10):
            for y in range(-10, 10):
                new_x = int(target.x + x)
                new_y = int(target.y + y)
                try:
                    frame[new_y, new_x] = [0, 0x70, 0]
                except IndexError:
                    pass

    cv2.imshow('hottie', frame) # pylint: disable=no-member

    return target
