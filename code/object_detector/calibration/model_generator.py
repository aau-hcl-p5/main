import os
from typing import List

from sklearn.neural_network import MLPRegressor


def generate_model(inp: List[float], expect: List[float]):
    model = MLPRegressor(solver="lbfgs", activation="approx_sigmoid", hidden_layer_sizes=(30, 30), verbose=True)
    model.fit(inp, expect)
    return model


def export_model(model, name):
    weights = model.coefs_
    biases = model.intercepts_

    with open(name + ".c", "w") as model:
        # Includes
        model.write("#include <stdint.h>\n\n")
        model.write("#include <math.h>\n\n")

        # Typedefs
        model.write("typedef struct {\n")
        for x in range(len(weights[0])):
            model.write(f"    double input_{x};\n")
        model.write("} T_MODEL_INPUT;\n\n")
        model.write("typedef struct {\n")
        for x in range(len(weights[-1][0])):
            model.write(f"    double output_{x};\n")
        model.write("} T_MODEL_EXECUTION_RESULT;\n\n")

        # Sigmoid
        model.write("""
double sigmoid(double value)
    {
        double x = value >= 0 ? value : value * -1;
        double x2 = x * x;
        double e = 1.0f + x + x2 * 0.555f + x2 * x2 * 0.143f;
        return 1.0f / (1.0f + (value > 0 ? 1.0f / e : e));
    }
""")
        # Weights
        for index, weight_layer in enumerate(weights):
            model.write(
                f"double WEIGHTS_LAYER_{index}[{len(weight_layer)}][{len(weight_layer[0])}] = {{\n    {(',' + os.linesep + '    ').join('{ ' + ', '.join(str(weight) for weight in weights) + ' }' for weights in weight_layer)}\n}};\n")

        # Biases
        for index, bias_layer in enumerate(biases):
            model.write(
                f"double BIAS_LAYER_{index}[{len(bias_layer)}] = {{\n    {', '.join(str(x) for x in bias_layer)}\n}};\n")

        # Model execution function
        model.write(f"T_MODEL_EXECUTION_RESULT calculate_{name}(T_MODEL_INPUT input) {{\n")
        model.write(
            f"    double intermediate_result_0[] = {{ {', '.join(f'input.input_{x}' for x in range(len(weights[0])))} }};\n")
        for index, weight_layer in enumerate(weights):
            model.write(f"    double intermediate_result_{index + 1}[{len(weight_layer[0])}];\n")
            model.write(f"    for (int i = 0; i < {len(weight_layer[0])}; i++) {{\n")
            model.write("        double sum = 0;\n")
            model.write(f"        for (int j = 0; j < {len(weight_layer)}; j++) {{\n")
            model.write(f"            sum += WEIGHTS_LAYER_{index}[j][i] * intermediate_result_{index}[j];\n")
            model.write("        }\n")
            model.write(
                f"        intermediate_result_{index + 1}[i] = {'sigmoid' if index != len(weights) - 1 else ''}(sum + BIAS_LAYER_{index}[i]);\n")
            model.write("    }\n")
        model.write("    T_MODEL_EXECUTION_RESULT result;\n")
        for x in range(len(weights[-1][0])):
            model.write(f"    result.output_{x} = intermediate_result_{len(weights)}[{x}];\n")
        model.write("    return result;\n")
        model.write("}\n")
