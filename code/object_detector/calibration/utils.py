class Package:
    """
    The class that conforms to the data sent by the NXT.
    This has the same signature, but the data might need to change form.
    """
    def __init__(
            self,
            position: int,
            axis: bool,
            power_up: int,
            power_down: int
    ):
        self.position = position
        self.axis = axis
        self.power_up = power_up
        self.power_down = power_down

    def __str__(self):
        return f"{{position:{self.position}, axis:{self.axis}, power_up:{self.power_up}, power_down:{self.power_down}}}"

    def is_x(self):
        return self.axis

    def is_y(self):
        return not self.axis
