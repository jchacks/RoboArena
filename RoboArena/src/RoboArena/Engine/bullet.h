#pragma once

#include "RoboArena/vec2.h"
#include "RoboArena/log.h"

const float BULLET_MAX_POWER = 3.0;
const float BULLET_MIN_POWER = 0.1;

class Bullet
{
public:
    class Robot *owner;
    Vec2 position;
    Vec2 velocity;
    float power;

    Bullet()
        : owner(NULL),
          position(Vec2(0.0, 0.0)),
          velocity(Vec2(0.0, 0.0)),
          power(0)
    {
        TRACE("Bullet default constructor {}", (long)this);
    };
    Bullet(Robot *owner, Vec2 position, Vec2 velocity, float power)
        : owner(owner),
          position(position),
          velocity(velocity)
    {
        this->power = clip(power, BULLET_MIN_POWER, BULLET_MAX_POWER);
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

    bool operator>(const Bullet &other) const;
    bool operator<(const Bullet &other) const;

private:
    friend std::ostream &operator<<(std::ostream &strm, const Bullet &b)
    {
        return strm << "Bullet[owner=" << b.owner << ",pos=" << b.position << ",pow=" << b.power << "]";
    }
};
