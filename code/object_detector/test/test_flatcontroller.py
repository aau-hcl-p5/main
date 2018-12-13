"""

"""
import io
import sys

import unittest

import algorithms
import webcam
from flat_controller import FlatController
from output_devices import Printer


class TestFlatController(unittest.TestCase):
    def test_status_see_target(self):
        with io.StringIO() as capturedOutput:
            alg = algorithms.get_algorithm(algorithms.AlgorithmType.ZONE_AVG)
            sys.stdout = capturedOutput  # and redirect stdout.
            with Printer() as output_device:
                FlatController(alg.locate_center,
                               output_device,
                               webcam.VideoController(webcam.CaptureDeviceType.TEST_POSITIVE),
                               )._iteration()
            sys.stdout = sys.__stdout__
            self.assertEqual(
                capturedOutput.getvalue(),
                "Writing location b'\\x00\\x00\\x9d\\x03'\n"
            )

    def test_status_cannot_see_target(self):
        with io.StringIO() as capturedOutput:
            alg = algorithms.get_algorithm(algorithms.AlgorithmType.ZONE_AVG)
            sys.stdout = capturedOutput  # and redirect stdout.
            with Printer() as output_device:
                FlatController(alg.locate_center,
                               output_device,
                               webcam.VideoController(webcam.CaptureDeviceType.FILES),
                               )._iteration()
            sys.stdout = sys.__stdout__
            self.assertEqual(
                capturedOutput.getvalue(),
                "Writing status b'\\x01\\x00'\n"
            )
