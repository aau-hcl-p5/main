import dataclasses


@dataclasses.dataclass
class Package:
    """
    The class that conforms to the data sent by the NXT.
    This has the same signature, but the data might need to change form.
    """
    position: int
    axis: bool
    power: int
    positive_direction: bool

    def is_x(self):
        return self.axis

    def is_y(self):
        return not self.axis
