from typing import Callable

import cv2
import numpy as np
import os

from algorithms import Vector

RESULT_EXTENSION = 'result'
VIDEO_EXTENSION = 'mp4'


class Generator:
    """
    The controller that handles the image processing and communication with
    the NXT. This is the primary controller of the project
    """

    def __init__(self, algorithm: Callable[[np.ndarray], Vector], path: str, debug=True) -> None:
        """
        Initializes the controller
        :param algorithm: The algorithm to use for determining the center
        :param path: Path to a folder containing video files.
        """
        self._path = path
        self._algorithm = algorithm
        self._debug = debug

    def remove_results(self):
        for file in os.listdir(self._path):
            if file.endswith('.' + RESULT_EXTENSION):
                os.remove(os.path.join(self._path, file))

    def generate(self):
        files = set(os.listdir(self._path))
        videos = [x for x in files if x.endswith('.' + VIDEO_EXTENSION)
                  and x.replace(VIDEO_EXTENSION, RESULT_EXTENSION) not in files]

        print("Generating test data for:")
        for video in videos:
            self._generate_for_file(video)

    def _generate_for_file(self, file):
        print(" - ", file)
        video = cv2.VideoCapture(os.path.join(self._path, file))
        result_file_name = os.path.join(self._path, file.replace(VIDEO_EXTENSION, RESULT_EXTENSION))
        with open(result_file_name, 'w') as result_file:
            while video.isOpened():
                flag, frame = video.read()
                if frame is None:
                    video.release()
                    cv2.destroyAllWindows()
                    if self._debug:
                        if input() == 'x':
                            os.remove(result_file_name)
                    break
                frame = cv2.resize(frame, (640, 480))
                res = self._algorithm(frame)
                if res:
                    result_file.write(f"{int(res.x)} {int(res.y)}\n")
                else:
                    result_file.write("None\n")
                if self._debug:
                    self._draw_with_center(frame, res)
                    if cv2.waitKey(10) & 0xFF == ord('q'):
                        break

    @staticmethod
    def _draw_with_center(frame, res):
        if res:
            for x in range(frame.shape[1] - 1):
                frame[int(res.y), x] = [0xFF, 0, 0]
            for y in range(frame.shape[0] - 1):
                frame[y, int(res.x)] = [0xFF, 0, 0]
        cv2.imshow("Progress", frame)
