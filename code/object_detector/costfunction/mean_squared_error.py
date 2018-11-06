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

        data_length = len(data)
        predictions_length = len(predictions)

        if data_length != predictions_length:
            raise Exception('Prediction set and Data set must be of same length')
        if predictions_length == 0:
            raise Exception('Length of Prediction set must not be zero')

        accumulated_error = 0.0
        for prediction, target in zip(predictions, data):
            accumulated_error += (prediction - target).length()**2

        # Calculating mean and dividing by 2
        cost = (1.0 / (2 * predictions_length)) * accumulated_error

        return cost
