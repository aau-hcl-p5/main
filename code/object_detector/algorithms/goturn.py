"""
Everything relating to the implementation of the GOTURN
(Generic Object Tracking Using Regression) algorithm.

source: https://www.learnopencv.com/goturn-deep-learning-based-object-tracking/
"""
import datetime

from algorithms.generic_algorithm import GenericAlgorithm
from algorithms.result import Result


class Goturn(GenericAlgorithm):
    """
    GOTURN implementation of object recognition.
    """

    def predict(self, data: str) -> Result:
        return Result(1, 5, datetime.datetime.now().timestamp())

    def import_model(self, model: str) -> None:
        raise NotImplementedError

    def export_model(self) -> str:
        return ""
