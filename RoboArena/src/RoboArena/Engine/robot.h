#pragma once

#include "rapch.h"

#include <Python.h>
#include <glm/vec2.hpp>

#include "RoboArena/log.h"
#include "RoboArena/Engine/bullet.h"

static unsigned long NUMBER_ROBOTS = 0;
const float ROBOT_RADIUS = 24;

class Engine;
struct RobotParams
{
    glm::vec2 position;
    float base_rotation;
    float turret_rotation;
    float radar_rotation;
};

const float PI_2f32 = 2.0f * M_PI;

const float BASE_ROTATION_VELOCITY_RADS = 10 * M_PI / 180;
const float BASE_ROTATION_VELOCITY_DEC_RADS = 0.75 * M_PI / 180;
const float TURRET_ROTATION_VELOCITY_RADS = 20 * M_PI / 180;
const float RADAR_ROTATION_VELOCITY_RADS = 45 * M_PI / 180;

class Robot
{
public:
    float energy, speed, base_rotation, turret_rotation, radar_rotation, heat;
    int moving, base_turning, turret_turning, radar_turning;
    bool should_fire;
    float m_fire_power;
    glm::vec2 position;

    Robot()
        : energy(100.0f),
          speed(0.0f),
          base_rotation(0.0f),
          turret_rotation(0.0f),
          radar_rotation(0.0f),
          heat(0.0f),

          moving(0),
          base_turning(0),
          turret_turning(0),
          radar_turning(0),
          should_fire(false),
          m_fire_power(0.0f),
          position(glm::vec2(0.0f, 0.0f)),
          m_uid(NUMBER_ROBOTS += 1)
    {
        TRACE("Robot constructor {} {}", (long)this, m_uid);
    };

    ~Robot()
    {
        TRACE("Robot destructor {} {}", (long)this, m_uid);
    };

    unsigned long get_uid() { return m_uid; };
    inline float get_base_rotation_velocity()
    {
        return std::max(0.0f,
                        (BASE_ROTATION_VELOCITY_RADS - BASE_ROTATION_VELOCITY_DEC_RADS * std::abs(speed))) *
               (float)base_turning;
    };
    inline float get_turret_rotation_velocity() { return TURRET_ROTATION_VELOCITY_RADS * (float)turret_turning; };
    inline float get_radar_rotation_velocity() { return RADAR_ROTATION_VELOCITY_RADS * (float)radar_turning; };

    void set_firepower(float fire_power)
    {
        m_fire_power = fire_power;
    };

    void set_python_script(PyObject *scripted_robot)
    {
        INFO("Scripted Robot address {}", (long)scripted_robot);
        m_scripted_robot = scripted_robot;
    };

private:
    PyObject *m_scripted_robot = NULL;
    unsigned long m_uid;

private:
    void init(RobotParams &params);
    void step();
    inline float get_acceleration();
    inline glm::vec2 get_velocity();

    // Virtuals
    virtual void run();
    virtual void on_hit_robot();

    friend std::ostream &operator<<(std::ostream &strm, const Robot &r)
    {
        return strm << "Robot[uid=" << r.m_uid << ",energy=" << r.energy << ",pos=" << r.position[0] << "," << r.position[1] << ",direction=" << r.base_rotation << "]";
    }

    friend Engine;
};
