"""
Everything relating to the implementation of the GOTURN
(Generic Object Tracking Using Regression) algorithm.

source: https://www.learnopencv.com/goturn-deep-learning-based-object-tracking/
"""
import numpy as np

from algorithms.utilities import Vector
from algorithms.generic_algorithm import GenericAlgorithm


class Goturn(GenericAlgorithm):
    """
    GOTURN implementation of object recognition.
    """

    def predict(self, data: np.ndarray) -> Vector:
        return Vector(1, 5)

    def import_model(self, model: str) -> None:
        raise NotImplementedError

    def export_model(self) -> str:
        return ""
