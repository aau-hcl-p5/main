"""
This module contains the object recognition algorithms and does all the data processing.
This is all the concrete math and machine intelligence.

This module contains different algorithms that can be used interchangeable.

Each algorithm inherits from the same baseclass (@GenericAlgorithm)


"""
from enum import Enum
from typing import Callable, Optional

import numpy as np

from algorithms.generic_algorithm import GenericAlgorithm
from algorithms.goturn import Goturn
from algorithms.yolo import Yolo
from algorithms.zone_avg import ZoneAvgController
from algorithms.object_fill import ObjectFillController
from algorithms.result import Result, Status
from algorithms.utilities import Vector, screen_location_to_relative_location


class AlgorithmType(Enum):
    """
    Types of algorithms.
    """
    GOTURN = 0
    YOLO = 1
    ZONE_AVG = 2
    OBJ_FILL = 3


def get_algorithm(algorithm_type: AlgorithmType) -> Callable[[np.ndarray], Optional[Vector]]:
    """

    :param algorithm_type:
    :return: the method of the algorithm
    """
    if algorithm_type is AlgorithmType.GOTURN:
        return Goturn().predict
    if algorithm_type is AlgorithmType.YOLO:
        return Yolo().predict
    if algorithm_type is AlgorithmType.ZONE_AVG:
        return ZoneAvgController().locate_center
    if algorithm_type is AlgorithmType.OBJ_FILL:
        return ObjectFillController().locate_center

    raise NotImplementedError()


def get_from_str(algorithm_name: str) -> Callable[[np.ndarray], Optional[Vector]]:
    """
    Get an algorithm implementation based on the str name
    :param algorithm_name: the str name of the algorithm
    :return: an instance of an algorithm
    """
    algorithm_type = next(a for a in AlgorithmType if a.name.lower() == algorithm_name.lower())

    return get_algorithm(algorithm_type)


