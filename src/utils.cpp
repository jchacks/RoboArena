#include <utils.h>

float rand_float(float low, float high)
{
    return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

Vec2 Vec2::random(float low, float high)
{
    return Vec2(rand_float(low, high), rand_float(low, high));
};

void Vec2::clip(Vec2 min, Vec2 max)
{
    // Inplace clip the Vec2
    x = std::min(std::max(x, min.x), max.x);
    y = std::min(std::max(y, min.y), max.y);
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
};

Vec2 Vec2::operator*(const float &scalar) const
{
    return Vec2(x * scalar, y * scalar);
};

Vec2 &Vec2::operator+=(const Vec2 &other)
{
    x = x + other.x;
    y = y + other.y;
    return *this;
};

std::ostream &operator<<(std::ostream &strm, const Vec2 &v)
{
    return strm << "(" << v.x << "," << v.y << ")";
}

float clip(float clip, float min, float max)
{
    return std::max(min, std::min(max, clip));
}