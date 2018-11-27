import math
from typing import Union

NumberType = Union[int, float]


# normally i would use is_instance(val, numbers.Number)
# but that doesn't work wit typing right now.
# Not sure why. but this DOES work.
def _is_num(val) -> bool:
    return isinstance(val, (float, int))


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
        return f"Vector({self.x}, {self.y})"

    def __repr__(self):
        return f"Vector({self.x}, {self.y})"

    def length(self):
        return math.sqrt(self.x ** 2 + self.y ** 2)
