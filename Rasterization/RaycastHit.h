#pragma once
#include <glm/vec3.hpp>

class RaycastHit
{
public:
    glm::vec3 normal;
    glm::vec3 point;

    RaycastHit()
    {
        normal = glm::vec3{0};
        point = glm::vec3{0};
    }
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_)
    {
        normal = normal_; point = point_;
    }
};
