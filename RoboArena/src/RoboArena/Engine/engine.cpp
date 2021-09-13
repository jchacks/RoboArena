#include "rapch.h"
#include "engine.h"

#include <glm/gtx/optimum_pow.hpp>

#include "RoboArena/core.h"
#include "RoboArena/log.h"

// https://stackoverflow.com/questions/55302321/calling-a-python-class-method-from-c-if-given-an-initialised-class-as-pyobjec
// Not sure that this should be here and if this module is not called in
// PyObject *stop_name = PyUnicode_InternFromString("stop");

bool test_circle_to_circle(const glm::vec2 &c1, float r1, const glm::vec2 &c2, float r2)
{
    return glm::distance(c1, c2) <= (r1 + r2);
};

bool Engine::test_circle_oob(const glm::vec2 &c, const float r) const
{
    return !((r < c.x) & (c.x < m_size.x - r) & (r < c.y) & (c.y < m_size.y - r));
};

void Engine::add_robot(Robot& robot)
{
    robots.push_back(robot);
};

Robot& Engine::get_robot(int index)
{
    auto it_robot = robots.begin();
    std::advance(it_robot, index);
    return *it_robot;
};

void Engine::collide_bullets()
{
    std::set<Bullet *>::iterator it_bullet = bullets.begin();
    while (it_bullet != bullets.end())
    {
        // Test outofbounds
        if (test_circle_oob((*it_bullet)->position, 3))
        {
            TRACE("Bullet hit wall");
            delete *it_bullet;
            bullets.erase(it_bullet);
            it_bullet++;
            continue;
        }

        // Test robot collisions
        std::list<Robot>::iterator it_robot = robots.begin();
        while (it_robot != robots.end())
        {
            if (test_circle_to_circle(it_robot->position, Robot::RADIUS, (*it_bullet)->position, 3))
            {
                TRACE("Bullet hit tank");
                float power = (*it_bullet)->power;
                it_robot->energy -= 4.0f * +((power >= 1) * 2.0f * (power - 1.0f));
                bullets.erase(it_bullet);
                break;
            }
        }

        it_bullet++;
    }
};

void Engine::step()
{
    collide_bullets();
    for (auto it = bullets.begin(); it != bullets.end(); ++it)
        (*it)->step();

    for (auto it_robot = robots.begin(); it_robot != robots.end(); ++it_robot)
    {
        it_robot->step();
        if (test_circle_oob(it_robot->position, Robot::RADIUS))
        {
            TRACE("Robot collided with wall.");
            it_robot->position = glm::clamp(it_robot->position, glm::vec2(0.0,0.0), m_size);
        }
    }
};
