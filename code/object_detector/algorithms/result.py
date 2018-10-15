from dataclasses import dataclass


class Result:
    """
    This class is responsible for handle the result of a object detection.
    This says the location of the target as well as the timestamp
    """
    def __init__(self, x: int, y: int, ts: int) -> None:
        """
        :param x: x coordinate in relation to crosshair / laser
        :param y: y coordinate in relation to crooshair / laser
        :param ts: timestamp of finding
        """
        self.x = x
        self.y = y
        self.ts = ts

