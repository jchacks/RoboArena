#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utils.h>

class Robot
{
public:
    char moving;
    char turning;
    float speed;
    float target_speed;
    float energy;

    Vec2 position;
    float base_rads;
    float base_rads_speed;
    float turret_rads;
    float turret_rads_speed;

    Robot()
    {
        energy = 100;
        speed = 1;
        moving = 1;
        target_speed = 4;
        turning = 1;
        position = Vec2::random(0.0f, 10.0f);
        base_rads = rand_float(0.0f, 2.0f);
        turret_rads = base_rads;
    };

    Vec2 direction() const
    {
        return Vec2(cos(base_rads), sin(base_rads));
    }

    float acceleration() const
    {
        int sspeed = sgn<float>(speed);
        int starget = sgn<float>(target_speed);
        float co_speed = static_cast<float>(sspeed * starget);
        debug<float>(co_speed);
        // sspeed and starget are  1 ->  1
        // sspeed and starget are -1 -> -2
        // sspeed and starget are  0 -> 
        //      starget is 0 -> -2
        //      sspeed is  0 -> 1

        return std::max(0.0f, co_speed) - std::max(0.0f, 2 * co_speed) +
            static_cast<float>((1 - std::abs(sspeed)) + -2 * (1 - std::abs(starget)));
    }

    void init(){

    };

    void update()
    {
        speed += acceleration();

        speed = clip(speed, -8.0f, 8.0f);
        position += direction() * speed;
    };
};

std::ostream &operator<<(std::ostream &strm, const Robot &r)
{
    return strm << "Robot("
                << "energy=" << r.energy << ","
                << "position=" << r.position << ","
                << "direction=" << r.direction() << ","
                << "speed=" << r.speed << ")";
}

class Engine
{
public:
    std::vector<Robot> robots;
    Vec2 size;

    Engine(Vec2 size) : size(size) {}

    void collide_walls(Robot &robot)
    {
        robot.position.clip(Vec2(0.0f, 0.0f), size);
    }

    void update()
    {
        for (std::vector<Robot>::iterator it = robots.begin(); it != robots.end(); it++)
        {
            it->update();
            collide_walls(*it);
            std::cout << "Updated " << *it << std::endl;
        }
    }
};

int main()
{
    std::srand(std::time(nullptr));

    Engine engine = Engine(Vec2(200.0f, 100.0f));
    Robot r = Robot();
    engine.robots.push_back(r);
    int i = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    while (i >= 0)
    {
        engine.update();
        i -= 1;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Duration " << duration.count() << std::endl;

    return 0;
}