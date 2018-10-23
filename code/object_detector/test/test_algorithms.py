"""
Test everything regarding the implementation of the GOTURN algorithm
This doesn't do a whole learning run, which takes time,
but rather tests subsets of the process in smaller simplistic cases
"""
import unittest

import numpy as np

from algorithms import Goturn, ZoneAvgController, ObjectFillController, Vector
from webcam import VideoController, CaptureDeviceType


class TestGoturnAlgorithms(unittest.TestCase):
    """
    Test everything regarding the implementation of the GOTURN algorithm
    This doesn't do a whole learning run, which takes time,
    but rather tests subsets of the process in smaller simplistic cases
    """

    def setUp(self):
        self.test_string = "fisk"

    def test_instantiate_clean_goturn(self):
        """
        Test whether it is possible to instantiate the Goturn controller
        """
        self.assertEqual(Goturn().export_model(), "")

    def test_predict_with_goturn(self):
        """
        Test we can predict where the target is,
        based on supplied test data and a pre created model

        :return:
        """
        self.assertEqual(
            (1, 5),
            Goturn().predict(self.test_string).coordinates,
            msg="The returned coordinates did not match the expected output"
        )


class TestZoneAvgAlgorithm(unittest.TestCase):

    def test_detect_negative(self):
        """
        Test that the algorithm finds the correct location on the image.
        The test frame is actually empty so it shouldn't return anything
        TODO create positive test as well
        """
        controller = ZoneAvgController()
        frame = VideoController(CaptureDeviceType.FILES).get_current_frame()
        output = controller.zone_avg(frame)
        self.assertIsNone(output)

    def test_detect_positive(self):
        """
        Test that the algorithm finds the correct location on the image.
        The initial frame is not empty so this should return a location.
        #TODO verify that the location actually is correct.
        """
        controller = ZoneAvgController()
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output = controller.zone_avg(frame)
        print("zone detect", output)
        self.assertEqual(output.as_int(), Vector(306, 928))


class TestObjectFillAlgorithm(unittest.TestCase):

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
        controller = ObjectFillController(debug=False)
        frame = VideoController(CaptureDeviceType.TEST_POSITIVE).get_current_frame()
        output = controller.locate_center(frame)
        print("object fill", output)
        self.assertTrue(output.as_int(), Vector(912, 254))
