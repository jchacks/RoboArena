# distutils: language = c++

cimport cython
from cython.operator cimport dereference as deref, preincrement as inc

from wrapper cimport Bullet, Robot, ROBOT_RADIUS, Engine as CEngine, vec2, Log

from libc.math cimport sin, cos, pi
from cpython.ref cimport PyObject

from random import uniform
import numpy as np

ctypedef Bullet* BulletPtr
ctypedef Robot* RobotPtr

Log.Init()

cdef class PyBullet:
    """
    Needed for rendering bullets.
    Maybe swap to a list of tuples...
    """
    cdef Bullet c_bullet

    @property
    def position(self):
        return self.c_bullet.position.x, self.c_bullet.position.y

    @property
    def velocity(self):
        return self.c_bullet.velocity.x, self.c_bullet.velocity.y

    @staticmethod
    cdef PyBullet from_c(Bullet c_bullet):
        bullet:PyBullet = PyBullet()
        bullet.c_bullet = c_bullet
        return bullet

    def __repr__(self):
        return f"Bullet({self.position})"


cdef class PyRobot:
    cdef Robot c_robot

    def __cinit__(self):
        self.c_robot = Robot()
        self.c_robot.set_python_script(<PyObject*>self)

    def __init__(self, base_color, turret_color=None, radar_color=None):
        self.base_color = base_color
        self.turret_color = turret_color if turret_color is not None else base_color
        self.radar_color = radar_color if radar_color is not None else base_color

    cpdef void _init(self, tuple size, dict params):
        p = params.pop('position', (uniform(0,1) * size[0], uniform(0,1) * size[1]))
        self.c_robot.position = vec2(p[0],p[1])
        self.c_robot.base_rotation = params.pop('base_rotation', uniform(0,1) * pi * 2.0)
        self.c_robot.turret_rotation = params.pop('turret_rotation', uniform(0,1) * pi * 2.0)
        self.c_robot.radar_rotation = params.pop('radar_rotation', self.c_robot.turret_rotation)
        self.c_robot.energy = params.pop('energy', 100.0)
        self.init()

    cpdef void init(self):
        pass

    def hello(self):
        print("Hello")

    def stop(self):
        self.moving = 0
        self.base_turning = 0
        self.turret_turning = 0

    # Writeable props
    @property
    def should_fire(self):
        return self.c_robot.should_fire
    @should_fire.setter
    def should_fire(self, should_fire):
        self.c_robot.should_fire = should_fire

    @property
    def fire_power(self):
        return self.c_robot.fire_power
    @fire_power.setter
    def fire_power(self, fire_power):
        self.c_robot.fire_power = fire_power

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
        self.c_robot.fire_power: float = fire_power
        self.c_robot.should_fire:bint = True

    def run(self):
        print("THIS IS THE CALL THAT IM NOT LOOKING FOR")

    cpdef on_hit_wall(self):
        pass

    cpdef on_hit_robot(self, robot):
        pass

    cpdef on_bullet_hit(self, robot):
        pass

    cpdef on_hit_by_bullet(self, bullet):
        pass

    def __repr__(self):
        return f"{self.__class__.__name__}(energy={self.energy}, position={self.position},speed={self.speed}"\
            f",acceleration={self.acceleration},base_rotation={self.base_rotation})"


cdef class Engine:
    cdef CEngine c_engine
    cdef public list robots

    def __init__(self, list robots, tuple size=(600,400), rate=-1 ):
        self.c_engine : CEngine = CEngine(size[0], size[1])
        self.robots = robots
        for robot in self.robots:
            self.c_engine.add_robot(<Robot>((<PyRobot>robot).c_robot))

    @property
    def bullets(self):
        bullet_list: c_list[Bullet] = self.c_engine.get_bullets()
        return [PyBullet.from_c(bullet) for bullet in bullet_list]

    @property
    def size(self):
        s = self.c_engine.get_size()
        return (s.x, s.y)

    def init(self):
        self.c_engine.init()
        for py_robot in self.robots:
            # Call the init on the pyrobo
            params = self.init_robot(py_robot)
            py_robot._init(self.size, params)

    cpdef dict init_robot(self, robot):
        """Init a robot attrs directly or return a dict for cattrs"""
        return {}

    def step(self):
        print("CENGINE Step")
        self.c_engine.step()

    def is_finished(self):
        self.c_engine.is_finished()
