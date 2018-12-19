"""
This module contains the object recognition algorithms and does all the data processing.
This is all the concrete math and machine intelligence.

This module contains different algorithms that can be used interchangeable.

Each algorithm inherits from the same baseclass (@GenericAlgorithm)


"""
from enum import Enum

from algorithms.generic_algorithm import GenericAlgorithm
from algorithms.object_fill import ObjectFillController
from algorithms.object_localizer import ObjectLocalizer
from algorithms.thresh_moment import ThreshMomentController
from algorithms.utilities import Vector, screen_location_to_relative_location
from algorithms.zone_avg import ZoneAvgController


class AlgorithmType(Enum):
    """
    Types of algorithms.
    """
    ZONE_AVG = 2
    OBJ_FILL = 3,
    THRESH_MOMENT = 4


def get_algorithm(algorithm_type: AlgorithmType, debug=False) -> ObjectLocalizer:
    """

    :param debug:
    :param algorithm_type:
    :return: the method of the algorithm
    """
    if algorithm_type is AlgorithmType.ZONE_AVG:
        return ZoneAvgController()
    if algorithm_type is AlgorithmType.OBJ_FILL:
        return ObjectFillController(debug=debug)
    if algorithm_type is AlgorithmType.THRESH_MOMENT:
        return ThreshMomentController(debug=debug)

    raise NotImplementedError()


def get_from_str(algorithm_name: str, debug=False) -> ObjectLocalizer:
    """
    Get an algorithm implementation based on the str name
    :param debug:
    :param algorithm_name: the str name of the algorithm
    :return: an instance of an algorithm
    """
    algorithm_type = next(a for a in AlgorithmType if a.name.lower() == algorithm_name.lower())

    return get_algorithm(algorithm_type, debug)


