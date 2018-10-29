"""
The dataclass handling result data from an algorithm.
This should use the `datclasses` module, but that is 3.7 feature,
and as of today (15-10-2018) tensorflow doesn't work for 3.7

"""

from algorithms.utilities import Vector


class Result:
    """
    This dataclass is responsible for handle the result of a object detection.
    This says the location of the target as well as the timestamp
    """

    def __init__(self, vector: Vector, timestamp: int) -> None:
        """
        :param vector: x coordinate in relation to crosshair / laser
        :param timestamp: timestamp of finding
        """
        self._delta_vector = vector.as_int()
        self._timestamp = int(timestamp)

    def __str__(self):
        return f"[{self.timestamp}: {self.delta_x}, {self.delta_y}]"

    @property
    def location(self) -> Vector:
        """
        Returns the two coordinates as a tuple.
        This is a helper method for doing (self.delta_x, self.delta_y)
        :return: a two-tuple of the two coordinates
        """
        return self._delta_vector

    @property
    def timestamp(self):
        """
        :return: the UNIX timestamp of the time the camera took this picture
        """
        return self._timestamp
