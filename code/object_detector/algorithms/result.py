"""
The dataclass handling result data from an algorithm.
This should use the `datclasses` module, but that is 3.7 feature,
and as of today (15-10-2018) tensorflow doesn't work for 3.7

"""
from typing import Tuple


class Result:
    """
    This dataclass is responsible for handle the result of a object detection.
    This says the location of the target as well as the timestamp
    """

    def __init__(self, delta_x: int, delta_y: int, timestamp: float) -> None:
        """
        :param delta_x: x coordinate in relation to crosshair / laser
        :param delta_y: y coordinate in relation to crooshair / laser
        :param timestamp: timestamp of finding
        """
        self._delta_x = delta_x
        self._delta_y = delta_y
        self._timestamp = timestamp

    def __str__(self):
        return f"[{self.timestamp}: {self.delta_x}, {self.delta_y}]"

    @property
    def delta_x(self) -> int:
        """
        :return: The X coordinate of the result, relative to the location of the crosshair / laser
        """
        return self._delta_x

    @property
    def delta_y(self) -> int:
        """
        :return: The Y coordinate of the result, relative to the location of the crosshair / laser
        """
        return self._delta_y

    @property
    def coordinates(self) -> Tuple[int, int]:
        """
        Returns the two coordinates as a tuple.
        This is a helper method for doing (self.delta_x, self.delta_y)
        :return: a two-tuple of the two coordinates
        """
        return self.delta_x, self.delta_y

    @property
    def timestamp(self):
        """
        :return: the UNIX timestamp of the time the camera took this picture
        """
        return self._timestamp
