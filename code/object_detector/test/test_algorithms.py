import unittest

from algorithms import YoloController, GoturnController


class TestAlgorithms(unittest.TestCase):
    def setUp(self):
        self.test_string = "fisk"

    def test_instantiate_goturn(self):
        GoturnController()


    def test_instantiate_yolo(self):
        YoloController()

    @unittest.skip("because this isn't implemented yet")
    def test_run_goturn(self):
        YoloController().run(self.test_string)

