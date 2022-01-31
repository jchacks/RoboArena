from typing import Tuple, List
import numpy as np
from dataclasses import dataclass

@dataclass
class InitalState:
    position: Tuple[float, float]
    energy: float
    base_rotation: float
    turret_rotation: float
    radar_rotation: float

class PyRobot:

    should_fire: bool
    fire_power: float
    moving: int
    base_turning: int
    turret_turning: int
    radar_turning: int

    position: np.ndarray
    speed: float
    base_rotation: float
    turret_rotation: float
    turret_direction: np.ndarray
    radar_rotation: float
    energy: float
    energy_pctg: float
    heat: float
    heat_pctg: float
    def __init__(self, base_color: Tuple[int, int, int], turret_color=None, radar_color=None): ...
    def fire(self, fire_power: float): ...
    def run(self):
        """Run method called once per game tick"""
        ...
    def on_hit_wall(self):
        """Called when robot hits a wall"""
        ...
    def on_hit_robot(self):
        """Called when robot hits another robot"""
        ...
    def on_bullet_hit(self):
        """Called when a robot fired by this robot hits antoher robot"""
        ...
    def on_hit_by_bullet(self):
        """Called when a bullet hits the robot"""
        ...

class Engine:

    size: Tuple[int, int]
    bullets: List[Tuple[float, float]]
    def __init__(self, robots: List[PyRobot], size: Tuple[int, int] = (600, 400), rate: float = -1) -> None: ...
    def init(self):
        """Call to init all the robots, remove bullets etc."""
        ...
    def init_robot(self, robot: PyRobot) -> dict:
        """Overwrite to pass attrs directly to a dict for cattrs"""
        ...
    def get_bullets(self) -> List[Tuple[float, float]]: ...
    def step(self) -> None:
        """Move the state forward 1 tick"""
        ...
    def is_finished(self) -> bool:
        """Is the Engine in a finished state, 1 or less robot alive"""
        ...
