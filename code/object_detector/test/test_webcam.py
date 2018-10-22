"""
The testing regarding the initializing the webcam and or video stream.
This also tests the output of a video stream,
however it is not possible to test webcam in a unit test
"""
import unittest

import webcam


class TestVideoDevice(unittest.TestCase):
    """
    The testing regarding the initializing the webcam and or video stream.
    This also tests the output of a video stream,
    however it is not possible to test webcam in a unit test
    """

    def test_can_initialize_files_and_get_frame(self):
        """
        Test that the get_current_frame actually works, and returns a frame
        """
        video_controller = webcam.VideoController(webcam.CaptureDeviceType.FILES)
        # simply test that it returns something. it's hard to actually test what it returns
        self.assertIsNotNone(video_controller.get_current_frame())
