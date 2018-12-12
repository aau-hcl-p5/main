from calibration.model_generator import generate_model, export_model
from calibration.read_calibration_data import read_calibration_data
from output_devices import NxtUsb
import matplotlib.pyplot as plt


def calibrate(usb_controller: NxtUsb):
    packages = read_calibration_data(usb_controller)
    while True:
        inp, expect_up, expect_down = zip(*(([p.position], [p.power_up], [p.power_down]) for p in packages))
        inp_up, expect_up_filtered = zip(*(x for x in zip(inp, expect_up) if 2 < x[1][0] < 30))
        inp_down, expect_down_filtered = zip(*(x for x in zip(inp, expect_down) if 2 < x[1][0] < 30))
        model_up = generate_model(inp_up, expect_up_filtered)
        model_down = generate_model(inp_down, expect_down_filtered)

        res_up = [model_up.predict([x]) for x in inp]
        res_down = [model_down.predict([x]) for x in inp]

        plt.plot([x[0] for x in inp_up], expect_up_filtered, 'bo', label="Expected up")
        plt.plot([x[0] for x in inp_down], expect_down_filtered, 'ro', label="Expected down")
        plt.plot([x[0] for x in inp], res_up, label="Result up")
        plt.plot([x[0] for x in inp], res_down, label="Result down")
        plt.legend()
        plt.show()

        print("Accept? (y/N)")
        if input() in ['y', 'Y']:
            export_model(model_up, "model_up")
            export_model(model_down, "model_down")
            break
