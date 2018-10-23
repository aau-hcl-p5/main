"""
The entry file of the object detection module.
This project is intended to contain half of the F.L.A.T project
The project is explained in detail in the report at
https://github.com/aau-hcl-p5/main
This program is intended to analyze input from a webcam,
and then find a ball or balloon in the picture,
and then send the relative location, compared to a given crosshair,
to the other device in the system, being the NXT;
which will handle movement of motors etc.


"""
import argparse

import algorithms
from algorithms.generic_algorithm import GenericAlgorithm
import webcam


class FlatController:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self,
                 algorithm: GenericAlgorithm,
                 capture_type: webcam.CaptureDeviceType = webcam.CaptureDeviceType.CAMERA) -> None:
        """
        Initializes the controller
        :param algorithm: The algorithm to use for image processing
        :param capture_type: What type the capturing device should be.
        """
        self.video_controller = webcam.VideoController(capture_type)
        self._algorithm = algorithm

    def start(self) -> None:
        """
        Start a separate thread for running the 'run' method,
        and continuously run this.
        """
        pass

    def stop(self) -> None:
        """
        stop the thread running the FLAT object recognition
        """
        pass

    def _run(self):
        pass

    def _get_next_location(self):
        return self._algorithm.predict(self.video_controller.get_current_frame())


# check if this file is run directly.
if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='goturn',
        type=str, metavar='[name]',
        help="Choose which algorithm to run ['goturn', 'yolo']. default='goturn'")

    ARGS = PARSER.parse_args()

    FlatController(algorithms.get_from_str(ARGS.alg_name)).start()
