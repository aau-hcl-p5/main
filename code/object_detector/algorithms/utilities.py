"""
helper methods for the algorithm module
This contains classes and methods that can help with the action of algorithms

"""
from typing import Union, Optional

import numpy as np

COMMUNICATION_OUT_RANGE = 255  # 2**8

NumberType = Union[int, float]


class Vector:
    """
    A 2D vector with helper methods.
    This is too remove the usage of np.ndarray with 2 indexes,
    or a tuple, which both lacks the operators that
    this customisable-ness adds
    """

    def __init__(self, x: NumberType, y: NumberType) -> None:
        self.y = y
        self.x = x

    def as_int(self) -> 'Vector':
        """
        Returns the same vector, but where each scalar is converted into an int
        :return:
        """
        return Vector(int(self.x), int(self.y))

    def dir(self) -> 'Vector':
        """
        Returns the direction of the vector (whether each axis is positive or negative)
        :return: a vector with -1 or 1 on each axis.
        """
        return Vector(
            1 if self.x >= 0 else -1,
            1 if self.y >= 0 else -1,
        )

    def __add__(self, other):
        if isinstance(other, Vector):
            return Vector(self.x + other.x, self.y + other.y)
        if _is_num(other):
            return Vector(self.x + other, self.y + other)
        raise NotImplementedError

    def __floordiv__(self, other):
        if _is_num(other):
            return Vector(self.x // other, self.y // other)
        if isinstance(other, Vector):
            return Vector(self.x // other.x, self.y // other.y)

        raise NotImplementedError  # pragma: no cover

    def __truediv__(self, other):
        if _is_num(other):
            return Vector(self.x / other, self.y / other)
        if isinstance(other, Vector):
            return Vector(self.x / other.x, self.y / other.y)

        raise NotImplementedError  # pragma: no cover

    def __pow__(self, power, modulo=None):
        if _is_num(power):
            return Vector(self.x ** power, self.y ** power)
        if isinstance(power, Vector):
            return Vector(self.x ** power.x, self.y ** power.y)

        raise NotImplementedError  # pragma: no cover

    def __mul__(self, other):
        if isinstance(other, Vector):
            return Vector(self.x * other.x, self.y * other.y)

        if _is_num(other):
            return Vector(self.x * other, self.y * other)

        raise NotImplementedError  # pragma: no cover

    def __sub__(self, other):
        if isinstance(other, Vector):
            return Vector(self.x - other.x, self.y - other.y)
        if _is_num(other):
            return Vector(self.x - other, self.y - other)
        raise NotImplementedError  # pragma: no cover

    def __eq__(self, other):
        if other is None:
            return False
        if not isinstance(other, Vector):
            return False
        return self.x == other.x and self.y == other.y

    def __neg__(self):
        return Vector(- self.x, - self.y)

    def __hash__(self):
        return (self.x, self.y).__hash__()

    def __str__(self):
        return f"Vector({self.x},{self.y})"


# normally i would use is_instance(val, numbers.Number)
# but that doesn't work wit typing right now.
# Not sure why. but this DOES work.
def _is_num(val) -> bool:
    return isinstance(val, (float, int))


def screen_location_to_relative_location(frame: np.ndarray, position: Optional[Vector]) -> Optional[Vector]:
    """
    This transforms the location on the screen to a value between -127, 127
    and does this with scaling in the sense of:
    f(x) = (x/480)^2 * 255
    where 480 is the input range, and 255 is the output range.
    :param frame: the image that the position is on.
    :param position: The position on the frame
    :return: The output vector in range on x -y  [-127,127]
    """
    if position is None:
        return None

    half_size = Vector(frame.shape[1], frame.shape[0]) // 2

    val = (half_size - position) / half_size

    # dir is used because val.x * val.x will not keep the direction (negative or positive).
    return val ** 2 * - val.dir() * (COMMUNICATION_OUT_RANGE // 2)

