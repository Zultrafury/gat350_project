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
};