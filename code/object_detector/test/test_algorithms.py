"""
Test everything regarding the implementation of the GOTURN algorithm
This doesn't do a whole learning run, which takes time,
but rather tests subsets of the process in smaller simplistic cases
"""
import unittest

from algorithms import get_algorithm, AlgorithmType, Vector
from webcam import VideoController, CaptureDeviceType


class TestZoneAvgAlgorithm(unittest.TestCase):

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The test frame is actually empty so it shouldn't return anything
        TODO create positive test as well
        """
        controller = get_algorithm(AlgorithmType.ZONE_AVG)
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        """
        controller = get_algorithm(AlgorithmType.ZONE_AVG)
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output, on_target = controller.locate_center(frame)
        goal = Vector(928, 306)
        self.assertEqual(output.as_int(), goal, f"{output.as_int()} (output) != {goal}")


class TestObjectFillAlgorithm(unittest.TestCase):

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is empty so this should return None
        """
        controller = get_algorithm(AlgorithmType.OBJ_FILL)
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        """
        controller = get_algorithm(AlgorithmType.OBJ_FILL)
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output, on_target = controller.locate_center(frame)
        goal = Vector(911, 254)
        self.assertEqual(output.as_int(), goal, msg=f"{output.as_int()} (output) != {goal}")


class ThreshMomentAlgorithm(unittest.TestCase):
    """
    Testing of returned values of the Thresh Moment algoritm
    """

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is empty so this should return None
        """
        controller = get_algorithm(AlgorithmType.THRESH_MOMENT)
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.locate_center(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        """
        controller = get_algorithm(AlgorithmType.THRESH_MOMENT)
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output, on_target = controller.locate_center(frame)
        goal = Vector(912, 257)
        self.assertEqual(output.as_int(), goal, msg=f"{output.as_int()} (output) != {goal}")
