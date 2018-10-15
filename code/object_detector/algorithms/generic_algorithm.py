from algorithms.result import Result


class GenericAlgorithm:

    def run(self, data: str) -> Result:
        """
        this method runs through the algorithm on supplied data.
        :return: the result of the search
        """
        raise NotImplementedError
