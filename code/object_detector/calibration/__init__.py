import matplotlib.pyplot as plt
from sklearn import preprocessing

from calibration.model_generator import generate_model, save_model
from calibration.read_calibration_data import read_calibration_data
from output_devices import NxtUsb


def normalize(data):
    # optionally uncomment this line and use this instead. might create better results with
    # SGD in some cases.
    # scaler = preprocessing.StandardScaler()
    scaler = preprocessing.MinMaxScaler()
    output = scaler.fit_transform(data)
    output = [[x[0] * 4 - 2] for x in output]
    return output, (scaler.data_min_, scaler.data_max_)


def get_plotting_points(data):
    output = []
    for x in data:
        if len(output) and x[0] > output[-1][0]:
            break
        output.append(x)
    return output


def calibrate(usb_controller: NxtUsb):
    if usb_controller:
        print("generate new data? (y/N)")
    if usb_controller and input() in ["y", "Y"]:
        packages = read_calibration_data(usb_controller)
        plot_points, expect_up, expect_down = zip(
            *(([p.position], [p.power_up], [p.power_down]) for p in packages))
        inp_up, expect_up_filtered = zip(
            *(x for x in zip(plot_points, expect_up) if 7 < x[1][0] < 30))
        inp_down, expect_down_filtered = zip(
            *(x for x in zip(plot_points, expect_down) if 7 < x[1][0] < 30))
        with open("up.dat", "w") as file:
            file.write(str(inp_up))
            file.write("\n\n")
            file.write(str(expect_up_filtered))
            file.write("\n\n")

        with open("down.dat", "w") as file:
            file.write(str(inp_down))
            file.write("\n\n")
            file.write(str(expect_down_filtered))
    else:
        with open("up.dat", "r") as file:
            content = file.read().split("\n\n")
            inp_down = eval(content[0])
            expect_down_filtered = eval(content[1])

        with open("down.dat", "r") as file:
            content = file.read().split("\n\n")
            inp_up = eval(content[0])
            expect_up_filtered = eval(content[1])

    while True:
        inp_down, inp_down_min_max = normalize(inp_down)
        inp_up, inp_up_min_max = normalize(inp_up)
        expect_up_filtered, expect_up_filtered_min_max = normalize(expect_up_filtered)
        expect_down_filtered, expect_down_filtered_min_max = normalize(expect_down_filtered)

        plot_points = get_plotting_points(inp_up)

        model_up = generate_model(inp_up, expect_up_filtered)
        model_down = generate_model(inp_down, expect_down_filtered)

        res_up = [model_up.predict([x]) for x in plot_points]
        res_down = [model_down.predict([x]) for x in plot_points]

        plt.plot([x[0] for x in inp_up], expect_up_filtered, 'bo', label="Expected up")
        plt.plot([x[0] for x in inp_down], expect_down_filtered, 'ro', label="Expected down")
        plt.plot([x[0] for x in plot_points], res_up, label="Result up")
        plt.plot([x[0] for x in plot_points], res_down, label="Result down")
        plt.legend()
        plt.show()
        print("Accept? (y/N)")
        if input() in ['y', 'Y']:
            save_model(model_up, inp_up_min_max, expect_up_filtered_min_max, "model_up")
            save_model(model_down, inp_down_min_max, expect_down_filtered_min_max, "model_down")
            break
