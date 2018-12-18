"""
The entry file of the object detection module.
This project is intended to contain half of the F.L.A.T project
The project is explained in detail in the report at
https://github.com/aau-hcl-p5/main
This program is intended to analyze input from a webcam,
and then find a ball or balloon in the picture,
and then send the relative location, compared to a given crosshair,
to the other device in the system, being the NXT;
which will handle movement of motors etc.


"""
import argparse

import algorithms
import webcam
from calibration import calibrate
from flat_controller import FlatController
from output_devices import NxtUsb, Printer

# check if this file is run directly.
if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='thresh_moment',
        type=str, metavar='[name]',
        help="Choose which algorithm to run "
             f"[{', '.join(a.name for a in algorithms.AlgorithmType)}]. default='thresh_moment'")

    PARSER.add_argument(
        '-n', '--no-usb',
        dest='no_usb', default=False,
        type=bool, metavar='[no_usb]',
        help="Whether to disable USB connection with the NXT. default=False")

    ARGS = PARSER.parse_args()

    with Printer() if ARGS.no_usb else NxtUsb() as output_device:
        cont = FlatController(algorithms.get_from_str(ARGS.alg_name, debug=True).locate_center,
                              output_device,
                              webcam.VideoController(webcam.CaptureDeviceType.FILES),
                              calibration_algorithm=calibrate,
                              debug=True)
        cont.run()
