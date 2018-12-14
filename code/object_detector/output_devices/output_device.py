from _ast import Tuple

from algorithms import Vector
from .status import Status


class OutputDevice:
    def __enter__(self):
        raise NotImplementedError()

    def __exit__(self, exc_type, exc_val, exc_tb):
        raise NotImplementedError()

    def write_location(self, data: Tuple[Vector, bool]) -> None:
        """
        Send a package of data which the NXT
        should react upon by moving the turret
        :param data: a tuple of the target and whether target is in center
        """
        raise NotImplementedError

    def write_status(self, status: Status) -> None:
        """
        Write the current status to the device
        :param status: the status to report
        """
        raise NotImplementedError

