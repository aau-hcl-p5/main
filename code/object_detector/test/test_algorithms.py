"""
Test everything regarding the implementation of the GOTURN algorithm
This doesn't do a whole learning run, which takes time,
but rather tests subsets of the process in smaller simplistic cases
"""
import unittest

from algorithms import ZoneAvgController, ObjectFillController, Vector, ThreshMomentController
from webcam import VideoController, CaptureDeviceType


class TestZoneAvgAlgorithm(unittest.TestCase):
    """
    Testing of the Zone Avg algorithm
    """

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The test frame is actually empty so it shouldn't return anything
        TODO create positive test as well
        """
        controller = ZoneAvgController()
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        #TODO verify that the location actually is correct.
        """
        controller = ZoneAvgController()
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output = controller.locate_center(frame)
        goal = Vector(928, 306)
        self.assertEqual(output.as_int(), goal, f"{output.as_int()} (output) != {goal}")


class TestObjectFillAlgorithm(unittest.TestCase):
    """
    Testing of the Object Fill algorithm
    """

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is empty so this should return None
        """
        controller = ObjectFillController(debug=False)
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        #TODO verify that the location actually is correct.
        """
        controller = ObjectFillController(debug=True)
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output = controller.locate_center(frame)
        goal = Vector(911, 254)
        self.assertEqual(output.as_int(), goal, msg=f"{output.as_int()} (output) != {goal}")


class ThreshMomentAlgorithm(unittest.TestCase):
    """
    Testing of the Thresh Moment algorithm
    """

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is empty so this should return None
        """
        controller = ThreshMomentController()
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        """
        controller = ThreshMomentController()
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output = controller.locate_center(frame)
        goal = Vector(912, 257)
        self.assertEqual(output.as_int(), goal, msg=f"{output.as_int()} (output) != {goal}")
