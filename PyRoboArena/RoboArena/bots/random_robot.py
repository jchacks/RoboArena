import random

from RoboArena.core import PyRobot
from RoboArena.ui.utils import Colors


class RandomRobot(PyRobot):
    def __init__(self) -> None:
        super().__init__(base_color=Colors.B)

    def run(self):
        self.moving = 1
        self.base_turning = 1
        try:
            self.move_forward(random.randint(50, 500))
            self.turn_left(random.randint(0, 360))
            if random.randint(0, 1):
                self.fire(random.randint(1, 3))
        except Exception:
            pass
