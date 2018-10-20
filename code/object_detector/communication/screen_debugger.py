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
                new_x = target.x + x
                new_y = target.y + y

                if 0 < new_y < frame.shape[1] and 0 < new_x < frame.shape[0]:
                    old_color = frame[target.x + x, target.y + y]
                    frame[target.x + x, target.y + y] = [old_color[0] + 50, old_color[1] + 50, 0]

    cv2.imshow('hottie', frame) # pylint: disable=no-member

    return target
