#include <glm/glm.hpp>

inline bool test_circle_to_circle(const glm::vec2 &c1, float r1, const glm::vec2 &c2, float r2)
{
    return glm::distance(c1, c2) <= (r1 + r2);
};

inline bool test_circle_oob(const glm::vec2 &c, const float r, const glm::vec2 &size)
{
    return !((r < c.x) & (c.x < size.x - r) & (r < c.y) & (c.y < size.y - r));
};

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
