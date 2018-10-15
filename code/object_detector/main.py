import argparse

from algorithms import YoloController, GoturnController, AlgorithmNotFound
from algorithms.generic_algorithm import GenericAlgorithm
from webcam import WebcamController


class FlatController:
    def __init__(self, algorithm: GenericAlgorithm):
        self.algorithm = algorithm
        self.webcam = WebcamController()

    def start_thread(self):
        pass

    def run(self):
        pass

    def get_next_location(self):
        self.algorithm.run(self.webcam.get_current_frame())
        pass


# check if this file is run directly.
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run the object detection part of the F.L.A.T system')

    parser.add_argument('-a', '--algorithm', dest='alg_name', default='goturn',
                        type=str, metavar='[name]',
                        help="Choose which algorithm to run ['goturn', 'yolo']. default='goturn'")

    args = parser.parse_args()
    if args.alg_name == 'goturn':
        FlatController(GoturnController()).run()
    elif args.alg_name == 'yolo':
        FlatController(YoloController()).run()
    else:
        raise AlgorithmNotFound()
