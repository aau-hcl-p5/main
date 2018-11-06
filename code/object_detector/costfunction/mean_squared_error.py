"The Implementation of the Mean Squared Error cost function"
import Vector

import numpy as np

from costfunction.generic_costfunction import GenericCostFunction
from algorithms.utilities import NumberType


class Mean_Squared_Error(GenericCostFunction):
    accumulated_error: NumberType

    """
    Returns the direction of the vector (whether each axis is positive or negative)
    :return: a value between 0 and 1 indicating the cost, deviation from the expected.
    """
    def compute_cost(data: np.ndarray[Vector], predictions: np.ndarray[Vector]) -> NumberType:
        samples_num = len(predictions)
    
        accumulated_error = 0.0
        for prediction, target in zip(predictions, data):
            accumulated_error += (prediction - target).length()**2

        # Calculating mean and dividing by 2
        cost = (1.0 / (2 * samples_num)) * accumulated_error
    
        return cost




