import io
import os
from typing import List

from sklearn.neural_network import MLPRegressor


def indent(amount=1):
    return amount * 4 * " "


def generate_model(inp: List[float], expect: List[float]) -> MLPRegressor:
    """

    :param inp: the input of the model
    :param expect: the expected output
    :return: A trained model
    """
    model = MLPRegressor(solver="lbfgs", activation="approx_sigmoid", hidden_layer_sizes=(30, 30),
                         verbose=True)
    model.fit(inp, expect)
    return model


def save_model(model: MLPRegressor, name: str) -> None:
    """
    This method takes a method and serializes into C-code, which can then be compiled
    to be used on the NXT device.

    :param model: The model to export
    :param name: the name of the file to write to
    """
    weights = model.coefs_
    biases = model.intercepts_
    with open(name + ".c", "w") as file:
        file.write(_export_model(weights, biases, name))


def _export_model(weights: List[List[List[float]]], biases: List[List[float]], name: str) -> str:

    output = io.StringIO()
    # Includes
    output.write("#include <stdint.h>\n\n")
    output.write("#include <math.h>\n\n")

    # Typedefs
    output.write("typedef struct {\n")
    for x in range(len(weights[0])):
        output.write(f"    double input_{x};\n")
    output.write("} T_MODEL_INPUT;\n\n")
    output.write("typedef struct {\n")
    for x in range(len(weights[-1][0])):
        output.write(f"    double output_{x};\n")
    output.write("} T_MODEL_EXECUTION_RESULT;\n\n")

    # Sigmoid
    output.write(
        """
        static double sigmoid(double value)
        {
            double x = value >= 0 ? value : value * -1;
            double x2 = x * x;
            double e = 1.0f + x + x2 * 0.555f + x2 * x2 * 0.143f;
            return 1.0f / (1.0f + (value > 0 ? 1.0f / e : e));
        }
        """
    )
    # Weights
    for idx, weight_layer in enumerate(weights):
        stringified_array = (',' + os.linesep + '    ').join(
            '{ ' + ', '.join(str(weight) for weight in weights) + ' }' for weights in
            weight_layer
        )

        output.write(
            f"static double WEIGHTS_LAYER_{idx}[{len(weight_layer)}]"
            f"[{len(weight_layer[0])}] = {{\n    {stringified_array}\n}};\n")

    # Biases
    for idx, bias_layer in enumerate(biases):
        stringified_array = ', '.join(str(x) for x in bias_layer)
        output.write(
            f"static double BIAS_LAYER_{idx}[{len(bias_layer)}] = "
            f"{{\n    {stringified_array}\n}};\n")

    # Model execution function
    output.write(f"T_MODEL_EXECUTION_RESULT calculate_{name}(T_MODEL_INPUT input) {{\n")
    output.write(
        "    double intermediate_result_0[] = "
        "f{{ {', '.join(f'input.input_{x}' for x in range(len(weights[0])))} }};\n")
    for idx, weight_layer in enumerate(weights):
        function_name = 'sigmoid' if idx != len(weights) - 1 else ''

        output.write(
            4 * " " + f"double intermediate_result_{idx + 1}[{len(weight_layer[0])}];\n")
        output.write(indent() + f"for (int i = 0; i < {len(weight_layer[0])}; i++) {{\n")
        output.write(indent() + "double sum = 0;\n")
        output.write(indent(2) + f"for (int j = 0; j < {len(weight_layer)}; j++) {{\n")
        output.write(
            indent(3) +
            f"sum += WEIGHTS_LAYER_{idx}[j][i] * intermediate_result_{idx}[j];\n"
        )
        output.write(indent(2) + "}\n")
        output.write(
            indent(2) +
            f"intermediate_result_{idx + 1}[i] = {function_name}(sum + BIAS_LAYER_{idx}[i]);\n"
        )
        output.write(indent(2) + "}\n")
    output.write(indent() + "T_MODEL_EXECUTION_RESULT result;\n")
    for x in range(len(weights[-1][0])):
        output.write(
            indent() + f"result.output_{x} = intermediate_result_{len(weights)}[{x}];\n")
    output.write(indent() + "return result;\n")
    output.write("}\n")

    return output.getvalue()
