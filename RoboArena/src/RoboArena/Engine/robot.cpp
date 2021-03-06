#include "robot.h"

#include "glm/gtx/rotate_vector.hpp"

// https://stackoverflow.com/questions/55302321/calling-a-python-class-method-from-c-if-given-an-initialised-class-as-pyobjec
// Not sure that this should be here and if this module is not called in
PyObject *run_name = PyUnicode_InternFromString("run");
PyObject *on_hit_robot_name = PyUnicode_InternFromString("on_hit_robot");

void Robot::init(RobotParams &params)
{
    position = params.position;
    base_rotation = params.base_rotation;
    turret_rotation = params.turret_rotation;
    radar_rotation = params.radar_rotation;
    energy = 100.0f;
    TRACE("Initialised robot, [({},{}),{},{},{}].", position.x, position.y, base_rotation, turret_rotation, radar_rotation);
};


void Robot::step()
{
    speed = glm::clamp(speed + get_acceleration(), -8.0f, 8.0f);
    auto velocity = glm::rotate(glm::vec2(speed, 0.0f), base_rotation);
    position = position + velocity;
    float base_rotation_velocity = get_base_rotation_velocity();
    base_rotation = std::remainderf(base_rotation + base_rotation_velocity, PI_2f32);
    float turret_rotation_velocity = get_turret_rotation_velocity() + base_rotation_velocity;
    turret_rotation = std::remainderf(turret_rotation + turret_rotation_velocity, PI_2f32);
    float radar_rotation_velocity = get_radar_rotation_velocity() + turret_rotation_velocity;
    radar_rotation = std::remainderf(radar_rotation + radar_rotation_velocity, PI_2f32);
};

inline float Robot::get_acceleration()
{
    if (speed > 0.0f)
    {
        if (moving > 0)
            return 1.0f;
        else
            return -2.0f;
    }
    else if (speed < 0.0f)
    {
        if (moving < 0)
            return -1.0f;
        else
            return 2.0f;
    }
    else if (std::abs(moving) > 0)
        return 1.0f;
    else
        return 0.0f;
};

//External scripted Python

void Robot::on_hit_robot()
{
    if (m_scripted_robot)
    {
        INFO("Found scripted robot @ {}\nRunning Python 'on_hit_robot' method brb...", (long)m_scripted_robot);
        PyObject_CallMethodObjArgs(m_scripted_robot, on_hit_robot_name, NULL);
    }
};

void Robot::run()
{
    if (m_scripted_robot)
    {
        INFO("Found scripted robot @ {}\nRunning Python 'run' method brb...", (long)m_scripted_robot);
        PyObject_CallMethodObjArgs(m_scripted_robot, run_name, NULL);
    }
};
