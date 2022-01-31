import random
import math
from RoboArena.core import PyRobot
from RoboArena.ui.utils import Colors


class RandomRobot(PyRobot):
    def __init__(self) -> None:
        super().__init__(base_color=Colors.B)
        self._commands = None
        self._move = None
        self._turn = None

    def ahead(self, distance: int):
        print("NEW AHEAD")
        self.moving = 1
        left_to_move = distance
        while left_to_move > 0:
            left_to_move -= self.speed
            yield False
        while True:
            self.moving = 0
            yield True

    def turnRight(self, angle):
        if angle < 0:
            self.base_turning = -1
            angle *= -1
        else:
            self.base_turning = 1
        left_to_turn = angle
        while left_to_turn > 0:
            left_to_turn -= abs(self.base_rotation_velocity)
            yield False
        while True:
            self.base_turning = 0
            yield True

    def waitFor(self, *commands):
        while True:
            yield not all([next(command) for command in commands if command])

    def sleep(self, ticks):
        while ticks > 0:
            ticks -= 1
            yield ticks

    def run(self):
        if not self._commands:
            self._commands = self.commands()
        else:
            try:
                next(self._commands)
            except StopIteration:
                self._commands = None

    def commands(self):
        wait = self.waitFor(
            self.ahead(random.randint(50, 100)), self.turnRight(random.randint(-180, 180) / (2 * math.pi))
        )
        while next(wait):
            if random.randint(0, 1):
                self.fire(random.randint(1, 3))

            yield
        print("Sleeping")
        yield from self.sleep(30)
