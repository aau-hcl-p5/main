"""
This module contains the object recognition algorithms and does all the data processing.
This is all the concrete math and machine intelligence.

This module contains different algorithms that can be used interchangeable.

Each algorithm inherits from the same baseclass (@GenericAlgorithm)


"""
from algorithms.generic_algorithm import GenericAlgorithm
from algorithms.goturn import Goturn
from algorithms.yolo import Yolo
from algorithms.zone_avg import ZoneAvgController


def get_from_str(alg_name: str) -> GenericAlgorithm:
    """
    Get an algorithm implementation based on the str name
    :param alg_name: the str name of the algorithm
    :return: an instance of an algorithm
    """
    if alg_name == 'goturn':
        return Goturn()
    if alg_name == 'yolo':
        return Yolo()

    raise AlgorithmNotFound()


class AlgorithmNotFound(Exception):
    """
    Exception to throw when the uses the '-a' argument wrongly, and the input is wrong.
    """
    pass
