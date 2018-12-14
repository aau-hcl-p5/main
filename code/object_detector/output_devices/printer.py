from typing import Tuple

from algorithms import Vector
from .output_device import OutputDevice
from .status import Status


class Printer(OutputDevice):
    def __enter__(self):
        return self

    def __exit__(self, *args):
        pass

    def write_location(self, data: Tuple[Vector, bool]) -> None:
        print("Writing location", bytes([
            0,
            0,
            int(data.x) & 0xFF,
            int(data.y) & 0xFF
        ]))

    def write_status(self, status: Status):
        value = status.value
        if type(value) is tuple:
            value = value[0]
        print("Writing status", bytes([
            int(value) & 0xFF,
            0
        ]))
