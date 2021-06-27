#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

float rand_float(float low, float high)
{
    return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

struct Vec2
{
    float x;
    float y;
    Vec2() : x(0.0f), y(0.0f){};
    Vec2(float x, float y) : x(x), y(y){};
    static Vec2 random(float low, float high)
    {
        return Vec2(rand_float(low, high), rand_float(low, high));
    };

    Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    };

    Vec2 operator*(const float &scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    };

    Vec2 &operator+=(const Vec2 &other)
    {
        x = x + other.x;
        y = y + other.y;
        return *this;
    };
};

std::ostream &operator<<(std::ostream &strm, const Vec2 &v)
{
    return strm << "Vec2(" << v.x << "," << v.y << ")";
}

class Robot
{
public:
    char moving;
    char turning;
    float speed;
    float energy;

    Vec2 position;
    float base_rads;
    Robot()
    {
        energy = 100;
        speed = 1;
        moving = 1;
        turning = 0;
        position = Vec2::random(0.0f, 10.0f);
        base_rads = 1.0f;
    };

    Vec2 direction() const
    {
        return Vec2(cos(base_rads), sin(base_rads));
    }

    float acceleration() const
    {
        int sspeed = sgn<float>(speed);
        int smove = sgn<float>(moving);
        // 1 if same direction 0 if moving or speed is zero, -1 if opposite
        switch (sspeed * smove)
        {
        case 1:
            return 1.0f;
        case -1:
            return -2.0f;
        case 0:
            return 1.0f * smove;
        default:
            return 0;
        }
    }

    void init(){

    };

    void update()
    {
        speed += acceleration();
        speed = std::max(-8.0f, std::min(8.0f, speed));
        position += direction() * speed;
    };
};

std::ostream &operator<<(std::ostream &strm, const Robot &r)
{
    return strm << "Robot("
                << r.position << ","
                << r.direction() << ","
                << r.speed << ")";
}

class Engine
{
public:
    std::vector<Robot> robots;

    void update()
    {
        for (std::vector<Robot>::iterator it = robots.begin(); it != robots.end(); it++)
        {
            it->update();
            std::cout << "Updated " << *it << std::endl;
        }
    }
};

int main()
{
    std::srand(std::time(nullptr));

    Engine engine = Engine();
    Robot r = Robot();
    engine.robots.push_back(r);
    int i = 100;
    auto start = std::chrono::high_resolution_clock::now();
    while (i >= 0)
    {
        engine.update();
        i -= 1;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return 0;
}