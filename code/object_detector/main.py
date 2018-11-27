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

# check if this file is run directly.
import algorithms
import webcam
from communication import NxtUsb, DeviceNotFound, SoundDebugger, ScreenDebugger
from flat_controller import FlatController

if __name__ == "__main__":
    PARSER = argparse.ArgumentParser(
        description='Run the object detection part of the F.L.A.T system'
    )

    PARSER.add_argument(
        '-a', '--algorithm',
        dest='alg_name', default='obj_fill',
        type=str, metavar='[name]',
        help="Choose which algorithm to run "
             f"[{', '.join(a.name for a in algorithms.AlgorithmType)}]. default='obj_fill'"
    )

    PARSER.add_argument(
        '-d', '--debug',
        action='store_const', const=True,
        help="Whether to run in debug mode. whether to show video feed"
    )

    ARGS = PARSER.parse_args()

    video_controller = webcam.VideoController(webcam.CaptureDeviceType.CAMERA)
    output_devices = []
    try:
        output_devices.append(NxtUsb())
    except DeviceNotFound:
        print("USB Device not found. running without.")
    if ARGS.debug:
        output_devices.append(ScreenDebugger(video_controller))
        output_devices.append(SoundDebugger())
    cont = FlatController(
        algorithms.get_from_str(ARGS.alg_name),
        video_controller,
        output_devices
    )
    cont.run()
