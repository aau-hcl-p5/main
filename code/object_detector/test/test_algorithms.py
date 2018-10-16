"""
Test everything regarding the implementation of the GOTURN algorithm
This doesn't do a whole learning run, which takes time,
but rather tests subsets of the process in smaller simplistic cases
"""
import unittest

from algorithms import Goturn


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
