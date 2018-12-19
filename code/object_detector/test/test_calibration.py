"""
Calibration
"""

import unittest

from calibration import model_generator


class TestCalibration(unittest.TestCase):

    def test_can_compile_to_c_code(self):
        code = model_generator._export_model(
            [
                [
                    [
                        1
                    ]
                ],
                [
                    [
                        1
                    ]
                ]
            ],
            [
                [
                    1,
                ] * 3
            ],
            ([1], [1]),
            ([2], [2]),
            "up"
        )

        self.assertIn("double sigmoid(double value)", code)
        self.assertIn(
            """
static double WEIGHTS_LAYER_0[1][1] = {
    { 1 }
};
static double WEIGHTS_LAYER_1[1][1] = {
    { 1 }
};
static double BIAS_LAYER_0[3] = {
    1, 1, 1
};
            """.replace(" ", ""),
            code.replace(" ", "")
        )
        self.assertIn("result.output_0 = ((intermediate_result_2[0] + 2 ) / 4) * 0 + 2", code)
        self.assertIn("T_MODEL_EXECUTION_RESULT calculate_up(T_MODEL_INPUT input) {", code)
