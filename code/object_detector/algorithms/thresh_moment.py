"""
This algorithm is a manually created one.
It will:
    1. Use an HSV representation with a red threshold
    2. Get moment (weighted average of object area) based on threshold
"""
from typing import Optional

import numpy as np
from cv2 import contourArea, COLOR_BGR2HSV, cvtColor, inRange, \
    findContours, COLOR_GRAY2BGR, drawContours, \
    moments, circle, imshow, CHAIN_APPROX_SIMPLE, RETR_TREE

from .vector import Vector


class ThreshMomentController:  # pylint: disable=too-few-public-methods
    """
    This algorithm is a manually created one.
    It will:
        1. Use an HSV representation with a red threshold
        2. Get moment (weighted average of object area) based on threshold
    """

    def __init__(self, debug: bool = False) -> None:
        self.debug = debug

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """
        # Convert image to HSV
        hsv_frame = cvtColor(frame, COLOR_BGR2HSV)
        # Get mask from red threshold
        mask = (
                inRange(hsv_frame, (0, 150, 50), (10, 255, 255)) |
                inRange(hsv_frame, (170, 150, 50), (180, 255, 255))
        )

        _, contours, _ = findContours(mask, RETR_TREE, CHAIN_APPROX_SIMPLE)
        contours = [contour for contour in contours if contourArea(contour) > 20]

        if contours:
            debug_frame = cvtColor(mask, COLOR_GRAY2BGR)
            biggest_contour = max(contours, key=contourArea)

            moment = moments(biggest_contour)
            cx = int(moment["m10"] / moment["m00"])
            cy = int(moment["m01"] / moment["m00"])

            if self.debug:
                drawContours(debug_frame, contours, -1, 255, 3)
                circle(debug_frame, (cx, cy), 7, (0, 0, 255), -1)

                imshow("thresh", debug_frame)
            return Vector(cx, cy)
        if self.debug:
            imshow("thresh", mask)
        return None
