#pragma once
#include "rapch.h"

#include <Python.h>
#include <glm/vec2.hpp>

#include "RoboArena/log.h"

#include "bullet.h"
#include "robot.h"

class Engine
{
public:
    Engine(){};
    Engine(float width, float height) : m_size(width, height) {};

    void add_robot(Robot &robot);
    Robot& get_robot(int index);

    void add_bullet(Bullet *bullet);
    void step();
    void run(); // Is this needed?

private:
    glm::vec2 m_size;
    std::list<Robot> robots;
    std::set<Bullet *> bullets;
    void collide_bullets();
    bool test_circle_oob(const glm::vec2 &c, const float r) const;
};
