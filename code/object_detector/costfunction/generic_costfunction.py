import numpy as np

from algorithms.utilities import Vector

#https://pythonmachinelearning.pro/using-neural-networks-for-regression-radial-basis-function-networks/

class GenericCostFunction:
    """
    The abstract implementation of the Cost Function
    """
    def compute_cost(predictions, data) -> cost
        raise NotImplementedError