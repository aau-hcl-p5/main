from algorithms import Result, Status
from .output_device import OutputDevice


class SoundDebugger(OutputDevice):
    def __init__(self):
        self._previous_status = None

    def write_data(self, data: Result) -> None:
        status = data.status
        if status == self._previous_status:
            return

        self._previous_status = status
        if status is Status.TARGET_FOUND:
            print("Target found sound!")
        elif status is Status.NO_TARGET_FOUND:
            print("Target missing")
        elif status is Status.DISCONNECT_REQ:
            print("bzzt disconnect")
        else:
            raise NotImplementedError("Status code not implemented!")
