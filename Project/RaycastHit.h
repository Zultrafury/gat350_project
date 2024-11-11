#pragma once
#include <glm/vec3.hpp>
#include "Material.h"

class RaycastHit
{
public:
    glm::vec3 normal;
    glm::vec3 point;
    shared_ptr<Material> mat;

    RaycastHit()
    {
        normal = glm::vec3{0};
        point = glm::vec3{0};
    }
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_)
    {
        normal = normal_; point = point_;
    }
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_, const shared_ptr<Material>& mat_) : RaycastHit(normal_, point_)
    {
        mat = mat_;
    }
};
