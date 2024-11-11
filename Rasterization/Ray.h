#pragma once
#include <glm/vec3.hpp>

class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 direction;

    Ray()
    {
        origin = glm::vec3{0};
        direction = glm::vec3{0};
    }
    Ray(const glm::vec3& origin_, const glm::vec3& direction_)
    {
        origin = origin_; direction = direction_;
    }

    float Length() const
    {
        return direction.length() - origin.length();
    }

    Uint8 ColLength() const
    {
        return min(255,static_cast<int>(round(direction.length()*direction.length()*20)));
    }
};