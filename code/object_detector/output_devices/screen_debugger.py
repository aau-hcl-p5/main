"""
Everything regarding debugging the data to the screen.
So when doing some kind of object recognition and you want to draw on the screen,
these methods help.
"""
from typing import Callable

import cv2
import numpy as np

from algorithms.utilities import Vector


def render_debugscreen(
        location: Vector,
        frame: np.ndarray,
        size: int = 5,
) -> None:  # pragma: no cover
    """
    and then displays the output to a image renderer
    :param location: location to highlight
    :param frame: the current frame
    :param size: the size of the debugging point
    """

    if location:
        center = Vector(frame.shape[1], frame.shape[0]) // 2
        location = (location + center) * -1

        cv2.circle(frame, (int(center.x), int(center.y)), size, (0, 0, 255), -1)
        cv2.circle(frame, (int(location.x), int(location.y)), size, (255, 0, 0), -1)

    cv2.imshow('debug view', frame)  # pylint: disable=no-member

