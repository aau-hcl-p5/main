from algorithms import Vector
from communication.status import Status


class PrintCommunication:
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass

    def read(self):
        raise Exception("Print communication should not be used for calibration or other things where Read is required")

    def write_location(self, data: Vector) -> None:
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
