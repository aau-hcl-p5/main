"""
Everything controlling the video input devices.
This outputs the data needed for the algorithms.
This either connects to a webcam or a filestream
The controller interfacing with the physical device of the webcam.
This need to serve one frame at a time.
"""
from enum import Enum

import cv2

import numpy as np

# Is of type returned by cv2.VideoCapture
# however cv2 doesn't utilize typing yet. those fuckers.
capture_device = None


class CaptureDeviceNotSetError(Exception):
    """
    The Exception to raise when the initialize_webcam_type hasn't been run.
    """

    def __init__(self):
        super().__init__("Cannot get frame without setting the _capture_device")


class CaptureDeviceType(Enum):
    """
    The types of capture devices (either webcam or video stream)
    """
    CAMERA = 0
    FILES = 1


def initialize_capture_device(camera_type: CaptureDeviceType) -> None:
    """
    Set the type of input device, depending on whether we are running against a dataset or a live video feed.
    it automatically releases existing capture devices if existing
    :param camera_type: The type of input device
    """
    global capture_device
    if capture_device is not None:
        capture_device.release()
    if camera_type is CaptureDeviceType.CAMERA:
        capture_device = cv2.VideoCapture(0)  # pylint: disable=no-member
    elif camera_type is CaptureDeviceType.FILES:
        capture_device = cv2.VideoCapture('webcam/testing_videos/fall_video.mp4')  # pylint: disable=no-member
    else:
        raise NotImplementedError


def get_current_frame() -> np.ndarray:
    """
    Gets the current frame of the capture device.
    This doesn't utilize queuing, but will simply pop the current frame
    :return: A representation of the current picture
    """
    if capture_device is None:
        raise CaptureDeviceNotSetError()

    _, frame = capture_device.read()
    return frame
