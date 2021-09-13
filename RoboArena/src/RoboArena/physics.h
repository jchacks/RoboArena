#include <glm/vec2.hpp>


struct Rect
{
    glm::vec2 origin, width, height;
};

struct Line
{
    glm::vec2 a, b;
};

struct Ray {
    glm::vec2 origin, direction;
};

glm::vec2 intersect(Ray ray, Rect rect);
