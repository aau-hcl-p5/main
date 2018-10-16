"""
Everything relating to the implementation of the YOLO (You Only Look Once) Algorithm.

source: http://machinethink.net/blog/object-detection-with-yolo/
"""
import datetime

from algorithms.generic_algorithm import GenericAlgorithm
from algorithms.result import Result


class Yolo(GenericAlgorithm):
    """
    The implementation of the YOLO algorithm
    """

    def predict(self, data: str) -> Result:
        return Result(2, 6, datetime.datetime.now().timestamp())

    def import_model(self, model: str) -> None:
        raise NotImplementedError

    def export_model(self) -> str:
        return ""
