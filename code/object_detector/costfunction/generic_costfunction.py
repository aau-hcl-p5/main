"""
The Abstract implementation of the cost-function
"""

import Vector

from algorithms.utilities import NumberType


class GenericCostFunction():
    """
    The abstract function for calculation the cost,
    the deviation from the expected result
    """
    def compute_cost(predictions: Vector, data: Vector) -> NumberType:
        raise NotImplementedError

