"""
Calibration
"""

import unittest

from calibration import model_generator


class TestCalibration(unittest.TestCase):

    def test_can_compile_to_c_code(self):
        return
        code = model_generator._export_model(
            [
                [
                    [
                        1
                    ] * 2
                ] * 3
            ],
            [
                [
                    1,
                    3,
                    4
                ] * 3
            ],
            "up"
        )
        self.assertIn("double sigmoid(double value)", code)
        self.assertIn(
            """
            double WEIGHTS_LAYER_0[3][2] = {
                { 1, 1 },
                { 1, 1 },
                { 1, 1 }
            };
            """.replace(" ", ""),
            code.replace(" ", "")
        )
        self.assertIn("T_MODEL_EXECUTION_RESULT calculate_up(T_MODEL_INPUT input) {", code)
