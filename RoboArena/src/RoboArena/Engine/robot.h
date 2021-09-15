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

class Robot
{
public:
    float energy, speed, base_rotation, turret_rotation, radar_rotation, heat;
    int moving, base_turning, turret_turning, radar_turning;
    bool should_fire;
    float fire_power;
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
          fire_power(0.0f),
          position(glm::vec2(0.0f, 0.0f)),
          uid(NUMBER_ROBOTS += 1)
    {
        TRACE("Robot constructor {} {}", (long)this, uid);
    };

    ~Robot()
    {
        TRACE("Robot destructor {} {}", (long)this, uid);
    };

    void set_python_script(PyObject *scripted_robot)
    {
        INFO("Scripted Robot address {}", (long)scripted_robot);
        m_scripted_robot = scripted_robot;
    };

private:
    PyObject *m_scripted_robot = NULL;
    static const float RADIUS;
    unsigned long uid;

private:
    void init(RobotParams &params);
    void step();
    Bullet fire();
    inline float get_acceleration();
    inline glm::vec2 get_velocity();

    // Virtuals
    virtual void run();
    virtual void on_hit_robot();

    friend std::ostream &operator<<(std::ostream &strm, const Robot &r)
    {
        return strm << "Robot[uid=" << r.uid << ",energy=" << r.energy << ",pos=" << r.position[0] << "," << r.position[1] << ",direction=" << r.base_rotation << "]";
    }

    friend Engine;
};
