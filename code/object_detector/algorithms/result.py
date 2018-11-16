"""
The dataclass handling result data from an algorithm.
This should use the `datclasses` module, but that is 3.7 feature,
and as of today (15-10-2018) tensorflow doesn't work for 3.7

"""

from algorithms.utilities import Vector
from enum import Enum


class Status(Enum):
    TARGET_FOUND = 0,
    NO_TARGET_FOUND = 1,
    DISCONNECT_REQ = 2


class Result:
    """
    This dataclass is responsible for handle the result of a object detection.
    This says the location of the target as well as the status code of the object
    """

    def __init__(self, vector: Vector, status: Status) -> None:
        """
        :param vector: x coordinate in relation to crosshair / laser
        :param status: status code of the result
        """
        self._delta_vector = vector.as_int()
        self._status = status

    def __str__(self):
        return f"[{self.status}: {self.location.x}, {self.location.y}]"

    @property
    def location(self) -> Vector:
        """
        Returns the two coordinates as a tuple.
        This is a helper method for doing (self.delta_x, self.delta_y)
        :return: a two-tuple of the two coordinates
        """
        return self._delta_vector

    @property
    def status(self):
        """
        :return: the UNIX timestamp of the time the camera took this picture
        """
        return self._status
