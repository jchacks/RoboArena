#pragma once
#include "rapch.h"

#include <glm/vec2.hpp>

#include "RoboArena/log.h"

#include "bullet.h"
#include "robot.h"

class Engine
{
public:
    Engine(){};
    Engine(float width, float height) : m_size(width, height){};

    void init();

    void add_robot(const Robot &robot);
    Robot &get_robot(int index);
    Robot &make_robot();

    std::list<Robot> &get_robots();
    std::list<Bullet> &get_bullets();
    glm::vec2 get_size();

    void add_bullet(Bullet bullet);
    void step();
    void run(); // Is this needed?
    bool is_finished();

    virtual float bullet_damage(Bullet &bullet);
    ;

private:
    unsigned long m_steps = 0;
    glm::vec2 m_size;
    std::list<Robot> m_robots;
    std::list<Bullet> m_bullets;
    inline bool check_bullet_collisions(Bullet &);
};
