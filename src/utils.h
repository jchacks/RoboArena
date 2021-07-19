#ifndef UTILS_H
#define UTILS_H

#include <ostream>
#include <iostream>

void rand_seed();
float rand_float(float low, float high);

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0){};
    Vec2(float x, float y) : x(x), y(y){};

    static Vec2 random(float low, float high);
    void clip(Vec2 min, Vec2 max);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator*(const float &scalar) const;
    Vec2 &operator+=(const Vec2 &other);
};

std::ostream &operator<<(std::ostream &strm, const Vec2 &v);

float clip(float clip, float min, float max);

template <typename T>
void debug(T val)
{
    std::cout << "DEBUG: " << val << std::endl;
}

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

#endif