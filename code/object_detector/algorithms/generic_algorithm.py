"""
The abstract implementation of object detection algorithms.
This exposes a lot of helper methods and generic variables,
that are usable for implementation of specific algorithms
"""
from algorithms.result import Result


class GenericAlgorithm:
    """
    The abstract implementation of object detection algorithms.
    This exposes a lot of helper methods and generic variables,
    that are usable for implementation of specific algorithms
    """

    def predict(self, data: str) -> Result:
        """
        this method runs through the algorithm on supplied data.
        :return: the result of the search
        """
        raise NotImplementedError

    def export_model(self) -> str:
        """
        Export the classification model. (all hidden layers)
        This can be used to either visualize it in a given tool, or save it for later use

        :return: a serialized string representation of the model
        """
        raise NotImplementedError

    def import_model(self, model: str) -> None:
        """
        import the classification model. (all hidden layers)
        This need to be serialized with the principles of this class.

        :param model: a serialized string representation of the model
        """
        raise NotImplementedError
