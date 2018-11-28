"""
This module contains the object recognition algorithms and does all the data processing.
This is all the concrete math and machine intelligence.

This module contains different algorithms that can be used interchangeable.

Each algorithm inherits from the same baseclass (@GenericAlgorithm)


"""
from enum import Enum
from typing import Callable, Optional

import numpy as np

from .zone_avg import ZoneAvgController
from .object_fill import ObjectFillController
from .result import Result, Status
from .vector import Vector

class AlgorithmType(Enum):
    """
    Types of algorithms.
    """
    ZONE_AVG = 2
    OBJ_FILL = 3
    THRESH_MOMENT = 4


def get_algorithm(algorithm_type: AlgorithmType) -> Callable[[np.ndarray], Optional[Vector]]:
    """

    :param algorithm_type:
    :return: the method of the algorithm
    """
    if algorithm_type is AlgorithmType.ZONE_AVG:
        return ZoneAvgController().locate_center
    if algorithm_type is AlgorithmType.OBJ_FILL:
        return ObjectFillController().locate_center
    if algorithm_type is AlgorithmType.THRESH_MOMENT:
        return ThreshMomentController(True).locate_center

    raise NotImplementedError()


def get_from_str(algorithm_name: str) -> Callable[[np.ndarray], Optional[Vector]]:
    """
    Get an algorithm implementation based on the str name
    :param algorithm_name: the str name of the algorithm
    :return: an instance of an algorithm
    """
    algorithm_type = next(a for a in AlgorithmType if a.name.lower() == algorithm_name.lower())

    return get_algorithm(algorithm_type)
