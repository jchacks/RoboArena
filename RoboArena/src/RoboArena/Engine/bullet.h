#pragma once

#include <glm/glm.hpp>
#include "uuid.h"

#include "RoboArena/log.h"

const float BULLET_MAX_POWER = 3.0;
const float BULLET_MIN_POWER = 0.1;

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
        uuids::uuid const m_id = uuids::uuid_system_generator{}();
        TRACE("Bullet default constructor {}", (long)this);
    };
    Bullet(Robot *owner, glm::vec2 position, glm::vec2 velocity, float power)
        : owner(owner),
          position(position),
          velocity(velocity)
    {
        this->power = glm::clamp(power, BULLET_MIN_POWER, BULLET_MAX_POWER);
        TRACE("Bullet constructor {}", (long)this);
    };

    ~Bullet()
    {
        TRACE("Bullet destructor {}", (long)this);
    };

    void step()
    {
        position += velocity;
    };

    bool operator<(const Bullet &other) const;

private:
    uuid const m_id;

private:
    friend std::ostream &operator<<(std::ostream &strm, const Bullet &b)
    {
        return strm << "Bullet[owner=" << b.owner << ",pos=" << b.position[0] << "," << b.position[1] << ",pow=" << b.power << "]";
    }
};
