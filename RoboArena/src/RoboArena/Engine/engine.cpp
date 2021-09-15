#include "rapch.h"
#include "engine.h"

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/optimum_pow.hpp>
#include <glm/gtx/component_wise.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include <glm/gtc/random.hpp>

#include "RoboArena/core.h"
#include "RoboArena/log.h"
#include "RoboArena/Engine/physics.h"

void Engine::add_robot(const Robot &robot)
{
    TRACE("Adding robot.");
    m_robots.push_back(std::move(robot));
};

Robot &Engine::get_robot(int index)
{
    auto it_robot = m_robots.begin();
    std::advance(it_robot, index);
    return *it_robot;
};

Robot &Engine::make_robot()
{
    return m_robots.emplace_back();
};

std::list<Robot> &Engine::get_robots()
{
    return m_robots;
};

std::list<Bullet> &Engine::get_bullets()
{
    return m_bullets;
};

glm::vec2 Engine::get_size()
{
    return m_size;
};

float Engine::bullet_damage(Bullet &bullet)
{
    float power = bullet.power;
    return 4.0f * power + ((power >= 1) * 2.0f * (power - 1.0f));
}

inline float rand_angle()
{
    glm::vec2 tmp = glm::circularRand(1);
    return glm::atan(tmp.x, tmp.y);
};

void Engine::init()
{
    m_steps = 0;
    m_bullets.clear();
    for (auto it_robot = m_robots.begin(); it_robot != m_robots.end(); ++it_robot)
    {
        RobotParams params{
            glm::linearRand(glm::vec2(0.0f, 0.0f), m_size),
            rand_angle(),
            rand_angle(),
            rand_angle(),
        };
        it_robot->init(params);
    }
}

bool Engine::is_finished()
{
    int alive = 0;
    for (auto it_robot = m_robots.begin(); it_robot != m_robots.end(); ++it_robot)
        alive += (it_robot->energy > 0);
    return alive <= 1;
};

inline bool Engine::check_bullet_collisions(Bullet &bullet)
{
    // Test outofbounds
    if (test_circle_oob(bullet.position, 3, m_size))
    {
        return true;
    }
    // Test robot collisions
    for (auto it_robot = m_robots.begin(); it_robot != m_robots.end();)
    {
        Robot &robot = (*it_robot);
        if (test_circle_to_circle(robot.position, ROBOT_RADIUS, bullet.position, 3))
        {
            TRACE("Bullet {} power:{} dmg:{}\n\thit {} \n\tfrom {}",
                  bullet,
                  bullet.power,
                  bullet_damage(bullet),
                  robot.get_uid(),
                  bullet.owner->get_uid());
            robot.energy -= bullet_damage(bullet);
            bullet.owner->energy += 3 * bullet.power;
            return true;
        }
        it_robot++;
    }
    return false;
}

void Engine::step()
{
    TRACE("Iterating Bullets. {}", m_bullets.size());
    // Bullets
    for (auto it_bullet = m_bullets.begin(); it_bullet != m_bullets.end();)
    {
        Bullet &bullet = *it_bullet;
        if (check_bullet_collisions(bullet))
        {
            WARN("Deleting bullet {}", (long)&(*it_bullet));
            it_bullet = m_bullets.erase(it_bullet);
        }
        else
        {
            // If the bullet still exists step it
            bullet.position += bullet.velocity;
            it_bullet++;
        }
    }

    TRACE("Iterating Robots for collisions.");
    // Robots
    for (auto it_robot = m_robots.begin(); it_robot != m_robots.end(); ++it_robot)
    {
        Robot &robot = (*it_robot);
        for (auto it_other = m_robots.begin(); it_other != m_robots.end(); ++it_other)
        {
            Robot &other = (*it_other);
            if (robot.get_uid() == other.get_uid())
                continue;
            else if (test_circle_to_circle(robot.position, ROBOT_RADIUS, other.position, ROBOT_RADIUS))
            {
                robot.energy -= 0.6f;
                other.energy -= 0.6f;
                robot.speed = 0.0f;
                other.speed = 0.0f;

                glm::vec2 collisionNormal = robot.position - other.position;
                // This handles the case when length == 0 internally
                collisionNormal = glm::normalize(collisionNormal);

                robot.position += collisionNormal;
                other.position -= collisionNormal;

                robot.on_hit_robot();
                other.on_hit_robot();
            }
        }
    }

    TRACE("Iterating Robots for steps.");
    for (auto it_robot = m_robots.begin(); it_robot != m_robots.end(); ++it_robot)
    {
        Robot &robot = (*it_robot);
        robot.energy = glm::clamp(robot.energy, 0.0f, 100.0f);
        if (robot.energy > 0)
        {
            robot.heat = std::max(0.0f, robot.heat - 0.1f);
            // Collide walls
            if (test_circle_oob(robot.position, ROBOT_RADIUS, m_size))
            {
                TRACE("Robot {} collided with wall.", (*it_robot));
                robot.speed = 0.0f;
                robot.energy -= std::max(std::abs(robot.speed) * 0.5f - 1.0f, 0.0f);
                robot.position = glm::clamp(robot.position, glm::vec2(ROBOT_RADIUS), m_size - ROBOT_RADIUS);
            }

            robot.run();
            robot.step();

            if (robot.should_fire & robot.heat <= 0)
            {
                float fire_power = std::min(std::max(robot.m_fire_power, BULLET_MIN_POWER), BULLET_MAX_POWER);
                robot.should_fire = false;
                robot.heat = 1.0f + fire_power / 5.0f;
                robot.energy -= fire_power;
                TRACE("robot.energy {}, {}", robot.energy, fire_power);

                glm::vec2 turret_direction = glm::rotate(glm::vec2(1.0f, 0.0), robot.turret_rotation);
                glm::vec2 position = robot.position + turret_direction * 30.0f;
                glm::vec2 velocity = turret_direction * (20.0f - (3.0f * fire_power));
                m_bullets.emplace_back(&robot, position, velocity, fire_power);
            }
        }
    }
    m_steps += 1;
};
