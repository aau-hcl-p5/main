"""
helper methods for the algorithm module
This contains classes and methods that can help with the action of algorithms

"""
from typing import Iterator, Union

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

        raise NotImplementedError

    def __truediv__(self, other):
        if _is_num(other):
            return Vector(self.x / other, self.y / other)
        if isinstance(other, Vector):
            return Vector(self.x / other.x, self.y / other.y)

        raise NotImplementedError

    def __mul__(self, other):
        if isinstance(other, Vector):
            return Vector(self.x * other.x, self.y * other.y)

        if _is_num(other):
            return Vector(self.x * other, self.y * other)

        raise NotImplementedError

    def __sub__(self, other):
        if isinstance(other, Vector):
            return Vector(self.x - other.x, self.y - other.y)
        if _is_num(other):
            return Vector(self.x - other, self.y - other)
        raise NotImplementedError

    def __eq__(self, other):
        if other is None:
            return False

        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return (self.x, self.y).__hash__()

    def __str__(self):
        return f"Vector({self.x},{self.y})"


# normally i would use is_instance(val, numbers.Number)
# but that doesn't work wit typing right now.
# Not sure why. but this DOES work.
def _is_num(val) -> bool:
    return isinstance(val, (float, int))
