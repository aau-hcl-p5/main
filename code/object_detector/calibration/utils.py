import dataclasses


@dataclasses.dataclass
class Package:
    """
    The class that conforms to the data sent by the NXT.
    This has the same signature, but the data might need to change form.
    """
    position: int
    axis: bool
    power_up: int
    power_down: int

    def is_x(self):
        return self.axis

    def is_y(self):
        return not self.axis
