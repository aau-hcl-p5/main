"""
Everything regarding debugging the data to the screen.
So when doing some kind of object recognition and you want to draw on the screen,
these methods help.
"""
from typing import Callable, Tuple, Optional

import cv2
import numpy as np

from algorithms.utilities import Vector


def render_debugscreen(
        data: Optional[Tuple[Vector, bool]],
        frame: np.ndarray,
        size: int = 5,
) -> None:  # pragma: no cover
    """
    and then displays the output to a image renderer
    :param data: location and whether we are on target
    :param frame: the current frame
    :param size: the size of the debugging point
    """

    if data:
        location, on_target = data
        center = Vector(frame.shape[1], frame.shape[0]) // 2
        location = (location*-1 + center)

        cv2.circle(frame, (int(center.x), int(center.y)), size, (0, 255, 255), -1)
        cv2.circle(
            frame,
            (int(location.x), int(location.y)),
            size,
            (
                255,
                0,
                255
            ),
            -1
        )

    cv2.imshow('debug view', frame)  # pylint: disable=no-member

