from RoboArena.core import PyRobot
from RoboArena.ui.utils import Colors


class DoNothing(PyRobot):
    def __init__(self) -> None:
        super().__init__(base_color=Colors.R)

    def run(self):
        pass
