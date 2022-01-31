# distutils: language = c++

cimport cython
from cython.operator cimport dereference as deref, preincrement as inc

from .wrapper cimport Bullet, Robot, ROBOT_RADIUS, Engine as CEngine, vec2, Log

from libcpp.list cimport list as c_list
from libc.math cimport sin, cos, pi
from cpython.ref cimport PyObject
from dataclasses import dataclass

from random import uniform
import numpy as np

ctypedef Bullet* BulletPtr
ctypedef Robot* RobotPtr
ctypedef c_list[Bullet] BulletList
ctypedef c_list[Bullet]* BulletListPtr
ctypedef c_list[Bullet].iterator BulletListIter

Log.Init()

# Replace with RobotParams
@dataclass
class InitalState:
    position: Tuple[float, float] = None
    energy: float = None
    base_rotation: float = None
    turret_rotation: float = None
    radar_rotation: float = None


cdef class PyRobot:
    cdef Robot* c_robot

    cdef setup(self, c_robot: RobotPtr):
        self.c_robot:Robot = c_robot
        print("Setup python script")
        self.c_robot.set_python_script(<PyObject*>self)

    def __init__(self, base_color, turret_color=None, radar_color=None):
        self.base_color = base_color
        self.turret_color = turret_color if turret_color is not None else base_color
        self.radar_color = radar_color if radar_color is not None else base_color

    def init(self):
        return InitalState()

    # Writeable props
    @property
    def should_fire(self):
        return self.c_robot.should_fire
    @should_fire.setter
    def should_fire(self, should_fire):
        self.c_robot.should_fire = should_fire

    @property
    def fire_power(self):
        return self.c_robot.m_fire_power
    @fire_power.setter
    def fire_power(self, fire_power):
        self.c_robot.m_fire_power = fire_power

    @property
    def moving(self):
        return self.c_robot.moving
    @moving.setter
    def moving(self, moving):
        self.c_robot.moving = moving

    @property
    def base_turning(self):
        return self.c_robot.base_turning
    @base_turning.setter
    def base_turning(self, base_turning):
        self.c_robot.base_turning = base_turning

    @property
    def turret_turning(self):
        return self.c_robot.turret_turning
    @turret_turning.setter
    def turret_turning(self, turret_turning):
        self.c_robot.turret_turning = turret_turning

    @property
    def radar_turning(self):
        return self.c_robot.radar_turning
    @radar_turning.setter
    def radar_turning(self, radar_turning):
        self.c_robot.radar_turning = radar_turning

    # Readonly props
    @property
    def position(self):
        return np.array([self.c_robot.position.x, self.c_robot.position.y], np.float32)

    @property
    def speed(self):
        return self.c_robot.speed

    @property
    def base_rotation_velocity(self):
        return self.c_robot.get_base_rotation_velocity()

    @property
    def turret_rotation_velocity(self):
        return self.c_robot.get_turret_rotation_velocity()

    @property
    def radar_rotation_velocity(self):
        return self.c_robot.get_radar_rotation_velocity()

    @property
    def base_rotation(self):
        return self.c_robot.base_rotation

    @property
    def turret_rotation(self):
        return self.c_robot.turret_rotation

    @property
    def turret_direction(self):
        return np.array(
            [cos(self.c_robot.turret_rotation),
            sin(self.c_robot.turret_rotation)],
            np.float32
        )

    @property
    def radar_rotation(self):
        return self.c_robot.radar_rotation

    @property
    def energy(self):
        return self.c_robot.energy

    @property
    def energy_pctg(self):
        return self.c_robot.energy/100

    @property
    def heat(self):
        return self.c_robot.heat

    @property
    def heat_pctg(self):
        return self.c_robot.heat/(1+3/5)

    def fire(self, float fire_power):
        self.c_robot.set_firepower(fire_power)
        self.c_robot.should_fire:bint = True

    def run(self):
        print("Error PyRobot.run is not implemented.")

    cpdef on_hit_wall(self):
        pass

    cpdef on_hit_robot(self,):
        pass

    cpdef on_bullet_hit(self):
        pass

    cpdef on_hit_by_bullet(self):
        pass

    def __repr__(self):
        return f"{self.__class__.__name__}(energy={self.energy}, position={self.position},speed={self.speed}"\
            f",base_rotation={self.base_rotation})"


cdef class Engine:
    cdef CEngine c_engine
    cdef public list robots

    def __cinit__(self, list robots, tuple size=(600,400), rate=-1 ):
        self.c_engine : CEngine = CEngine(size[0], size[1])
        self.robots = robots
        for robot in self.robots:
            _robot:PyRobot = <PyRobot>robot
            _robot.setup(&self.c_engine.make_robot())

    def get_bullets(self):
        r = []
        blist : BulletList = ((<CEngine>self.c_engine).get_bullets())
        for c_bullet in blist:
            r.append((c_bullet.position.x, c_bullet.position.y))
        return r

    @property
    def bullets(self):
        return self.get_bullets()

    @property
    def size(self):
        s = self.c_engine.get_size()
        return (s.x, s.y)

    cpdef void init(self):
        self.c_engine.init()
        for robot in self.robots:
            _robot:PyRobot = <PyRobot>robot
            # Call the init on the pyrobo
            state = _robot.init()
            position = state.position or (uniform(0,1) * self.size[0], uniform(0,1) * self.size[1])
            _robot.c_robot.position = vec2(position[0],position[1])
            _robot.c_robot.base_rotation = state.base_rotation or uniform(0,1) * pi * 2.0
            _robot.c_robot.turret_rotation = state.turret_rotation or uniform(0,1) * pi * 2.0
            _robot.c_robot.radar_rotation = state.radar_rotation or _robot.c_robot.turret_rotation
            _robot.c_robot.energy = state.energy or 100.0


    def step(self):
        self.c_engine.step()

    def is_finished(self):
        return self.c_engine.is_finished()
