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
        location, on_target = data
        print("Writing location", bytes([
            Status.ON_TARGET.value if on_target else Status.TARGET_FOUND.value,
            0,
            int(location.x) & 0xFF,
            int(location.y) & 0xFF
        ]))

    def write_status(self, status: Status):
        value = status.value
        if type(value) is tuple:
            value = value[0]
        print("Writing status", bytes([
            int(value) & 0xFF,
            0
        ]))
