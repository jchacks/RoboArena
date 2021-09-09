#include "vec2.h"


struct Rect
{
    Vec2 origin, width, height;
};

struct Line
{
    Vec2 a, b;
};

struct Ray {
    Vec2 origin, direction;
};

Vec2 intersect(Ray ray, Rect rect);

