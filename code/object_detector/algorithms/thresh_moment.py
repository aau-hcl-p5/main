"""
This algorithm is a manually created one.
It will:
    1. Use an HSV representation with a red threshold
    2. Get moment based on threshold
"""
from typing import Optional
from algorithms.utilities import Vector
from cv2 import contourArea, COLOR_BGR2HSV, cvtColor, inRange, threshold, findContours, COLOR_GRAY2BGR, drawContours, \
    moments, circle, imshow, CHAIN_APPROX_SIMPLE, RETR_TREE
import numpy as np


class ThreshMomentController:  # pylint: disable=too-few-public-methods
    """
This algorithm is a manually created one.
It will:
    1. Do a rough run over of the image to find the first occurrence of grouped red.
    2. Use a filling algorithm to "fill" the object.
    3. Use the average x and y coordinates of the outline to determine the center of the object
    4. Use the old center coordinates to search for the object in the next frame, and the goto 2.
    """

    def __init__(self, debug: bool = False) -> None:
        self.debug = debug

    def locate_center(self, frame: np.ndarray) -> Optional[Vector]:
        """
        :param frame: The image to search in
        :return: The center of the object (Can be null).
        """
        hsv_frame = cvtColor(frame, COLOR_BGR2HSV)
        mask = inRange(hsv_frame, (0, 150, 50), (10, 255, 255)) \
             | inRange(hsv_frame, (170, 150, 50), (180, 255, 255))

        ret, thresh = threshold(mask, 40, 255, 0)
        _, contours, _ = findContours(thresh, RETR_TREE, CHAIN_APPROX_SIMPLE)
        contours = [contour for contour in contours if contourArea(contour) > 20]

        if len(contours) != 0:
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
