#pragma once
#include <Python.h>

#include "RoboArena/vec2.h"
#include "RoboArena/log.h"

#include "bullet.h"
#include "robot.h"

class Engine
{
public:
    Engine(){};
    Engine(Vec2 size) : size(size){};

    Engine(float height, float width)
    {
        size = Vec2(width, height);
    };

    void add_robot(Robot &robot);
    Robot& get_robot(int index);

    void add_bullet(Bullet *bullet);
    void step();
    void run(); // Is this needed?

private:
    Vec2 size;
    std::list<Robot> robots;
    std::set<Bullet *> bullets;
    void collide_bullets();
    bool test_circle_oob(const Vec2 &c, const float r) const;
};
