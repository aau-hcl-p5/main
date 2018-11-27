from algorithms import Result


class OutputDevice:
    def write_data(self, data: Result) -> None:
        raise NotImplementedError
