"""
The testing regarding the initializing the webcam and or video stream.
This also tests the output of a video stream, however it is not possible to test webcam in a unit test
"""
import cv2
import unittest

import webcam


class TestVideoDevice(unittest.TestCase):
    """
    The testing regarding the initializing the webcam and or video stream.
    This also tests the output of a video stream, however it is not possible to test webcam in a unit test
    """

    def tearDown(self):
        if webcam.capture_device is not None:
            webcam.capture_device.release()
            webcam.capture_device = None

    def test_raise_error_if_not_initialized(self):
        """
        If the camera is not initialized, it should raise
        an error when trying to capture the next frame
        """
        with self.assertRaises(webcam.CaptureDeviceNotSetError):
            webcam.get_current_frame()

    def test_can_initialize_files_and_get_frame(self):
        """
        Test that the get_current_frame actually works, and returns a frame
        """
        webcam.initialize_capture_device(webcam.CaptureDeviceType.FILES)
        # simply test that it returns something. it's hard to actually test what it returns
        self.assertIsNotNone(webcam.get_current_frame())

    def test_is_released_if_re_assigned(self):

        webcam.initialize_capture_device(webcam.CaptureDeviceType.FILES)
        old_cap = webcam.capture_device
        webcam.initialize_capture_device(webcam.CaptureDeviceType.FILES)
        status, _ = old_cap.read()
        self.assertFalse(status)
        self.assertNotEqual(old_cap, webcam.capture_device)

