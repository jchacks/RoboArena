#pragma once

#include <ostream>
#include <iostream>

float rand_float(float low, float high);

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0){};
    Vec2(float x, float y) : x(x), y(y){};
    Vec2(float v) : x(v), y(v){};

    static Vec2 random(float low, float high);
    static Vec2 from_rads(float rads);

    Vec2 pow(float exponent);
    float sum();

    float len();
    Vec2 norm();

    void clip(Vec2 min, Vec2 max);
    void clip(float top, float left, float bottom, float right);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator-(const float &val) const;
    Vec2 operator*(const float &scalar) const;
    Vec2 operator/(const float &other) const;
    Vec2 &operator+=(const Vec2 &other);

    friend std::ostream &operator<<(std::ostream &strm, const Vec2 &v)
    {
        return strm << "V2(" << v.x << "," << v.y << ")";
    }
};

std::ostream &operator<<(std::ostream &strm, const Vec2 &v);

float clip(float clip, float min, float max);

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}
