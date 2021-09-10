#pragma once

#include <Python.h>

#include "RoboArena/vec2.h"
#include "RoboArena/log.h"
#include "RoboArena/Engine/bullet.h"

static unsigned long NUMBER_ROBOTS = 0;

class Robot
{
public:
    PyObject *scripted_robot = NULL;

    static const float RADIUS;

    unsigned long uid;
    float energy;
    float speed;
    Vec2 position;
    float base_rotation;
    float turret_rotation;
    float radar_rotation;
    float heat;

    int moving;
    int base_turning;
    int turret_turning;
    int radar_turning;
    bool should_fire;
    float fire_power;

    Robot()
        : uid(NUMBER_ROBOTS += 1),
          energy(100.0),
          speed(0.0),
          position(Vec2(0.0, 0.0)),
          base_rotation(0.0),
          turret_rotation(0.0),
          radar_rotation(0.0),
          heat(0.0),

          moving(0),
          base_turning(0),
          turret_turning(0),
          radar_turning(0),
          should_fire(false),
          fire_power(0.0)
    {
        TRACE("Robot constructor {}", (long)this);
    };

    Robot(const Robot& robot) {
        TRACE("Robot copy constructor {}", (long)this);
    };

    ~Robot()
    {
        TRACE("Robot destructor {}", (long)this);
    };

    void step();
    float get_acceleration();
    Vec2 get_velocity();
    Bullet *fire();

    friend std::ostream &operator<<(std::ostream &strm, const Robot &r)
    {
        return strm << "Robot[uid=" << r.uid << ",energy=" << r.energy << ",pos=" << r.position << ",direction=" << r.base_rotation << "]";
    }
};
