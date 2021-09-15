#pragma once

#include "glm/vec2.hpp"
#include "RoboArena/log.h"

const float BULLET_MAX_POWER = 3.0f;
const float BULLET_MIN_POWER = 0.1f;

class Bullet
{
public:
    class Robot *owner;
    glm::vec2 position;
    glm::vec2 velocity;
    float power;

    Bullet()
        : owner(NULL),
          position(glm::vec2(0.0, 0.0)),
          velocity(glm::vec2(0.0, 0.0)),
          power(0)
    {
        TRACE("Bullet default constructor {}", (long)this);
    };
    Bullet(Robot *owner, glm::vec2 position, glm::vec2 velocity, float power)
        : owner(owner),
          position(position),
          velocity(velocity),
          power(power)
    {
        TRACE("Bullet constructor {}", (long)this);
    };

    Bullet(const Bullet &other)
        : owner(other.owner),
          position(other.position),
          velocity(other.velocity),
          power(other.power)
    {
        TRACE("Copied Bullet");
    };

    ~Bullet() { TRACE("Bullet destructor {}", (long)this); };

    // Getters
    friend std::ostream &operator<<(std::ostream &strm, const Bullet &b)
    {
        return strm << "Bullet[owner=" << b.owner << ",pos=" << b.position[0] << "," << b.position[1] << ",pow=" << b.power << "]";
    }
};
