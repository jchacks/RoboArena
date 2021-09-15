# distutils: language = c++

cimport cython
from libcpp.list cimport list as c_list
from cpython.ref cimport PyObject

cdef extern from "RoboArena/log.h":
    cdef cppclass Log:
        @staticmethod
        void Init()


cdef extern from "RoboArena/Engine/bullet.h":
    cdef cppclass Bullet:
        vec2 position
        vec2 velocity

cdef extern from "RoboArena/Engine/robot.h":
    cdef struct RobotParams:
        vec2 position
        float base_rotation, turret_rotation, radar_rotation

    cdef cppclass Robot:
        bint should_fire
        int moving, base_turning, turret_turning, radar_turning
        vec2 position
        float energy, speed, heat, base_rotation, turret_rotation, radar_rotation, m_fire_power
        Robot()
        void set_python_script(PyObject*)
        void set_firepower(float)

cdef extern from "RoboArena/Engine/engine.h":
    cdef cppclass Engine:
        Engine()
        Engine(float, float)
        void init()
        void add_robot(Robot)
        void add_bullet(Bullet)
        Robot& make_robot()
        vec2 get_size()
        c_list[Bullet]& get_bullets()
        c_list[Robot]& get_robots()

        bint is_finished()
        void step()
        void collide_bullets()

    cdef float ROBOT_RADIUS
    cdef float PI_2f32

cdef extern from "glm/vec2.hpp" namespace "glm":
    cdef cppclass vec2:
        float x, y
        vec2()
        vec2(float,float)
