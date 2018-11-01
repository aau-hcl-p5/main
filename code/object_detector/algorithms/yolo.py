"""
Everything relating to the implementation of the YOLO (You Only Look Once) Algorithm.

source: http://machinethink.net/blog/object-detection-with-yolo/
"""
import numpy as np

from algorithms.utilities import Vector
from algorithms.generic_algorithm import GenericAlgorithm


class Yolo(GenericAlgorithm):
    """
    The implementation of the YOLO algorithm
    """

    def predict(self, data: np.ndarray) -> Vector:
        return Vector(2, 6)

    def import_model(self, model: str) -> None:
        raise NotImplementedError

    def export_model(self) -> str:
        return ""
