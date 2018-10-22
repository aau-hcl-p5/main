"""
Everything controlling the video input devices.
This outputs the data needed for the algorithms.
This either connects to a webcam or a filestream
The controller interfacing with the physical device of the webcam.
This need to serve one frame at a time.
"""
from enum import Enum
from typing import Union

import cv2 # pylint: disable=import-error
import numpy as np

class CaptureDeviceType(Enum):
    """
    The types of capture devices (either webcam or video stream)
    """
    CAMERA = 0
    FILES = 1


class VideoController:
    """
    The controller of a given input video stream.
    This abstracts away whether we connect with a webcam or a video file
    """

    def __init__(self, camera_type: CaptureDeviceType) -> None:
        if camera_type is CaptureDeviceType.CAMERA:
            input_device: Union[str, int] = 0  # pylint: disable=no-member
        elif camera_type is CaptureDeviceType.FILES:
            input_device = 'webcam/testing_videos/fall_video.mp4'
        else:
            raise NotImplementedError

        self.capture_device = cv2.VideoCapture(input_device)  # pylint: disable=no-member

    def get_current_frame(self) -> np.ndarray:
        """
        Gets the current frame of the capture device.
        This doesn't utilize queuing, but will simply pop the current frame
        :return: A representation of the current picture
        """

        _, frame = self.capture_device.read()
        return frame

    def __del__(self):
        self.capture_device.release()
