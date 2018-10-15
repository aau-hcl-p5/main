"""
Everything controlling the webcam.
This outputs the data needed for the algorithms
The controller interfacing with the physical device of the webcam.
This need to serve one frame at a time.
"""

CAMERA = None


def get_current_frame() -> str:
    """
    Gets the current frame of the webcam.
    This doesn't utilize queuing, but will simply pop the current frame
    TODO: change type so it actually utilizes something tensorflow can handle
    :return: A representation of the current picture
    """
    raise NotImplementedError


def connect_camera() -> None:
    """
    Opens connection to the webcam and turns it on
    """


def disconnect_camera() -> None:
    """
    Disconnects the webcamera and freeing up the device for others to use
    """
