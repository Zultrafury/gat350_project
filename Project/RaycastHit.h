#pragma once
#include <memory>
#include "Material.h"

using mat_t = std::shared_ptr<Material>;

class RaycastHit
{
public:
    glm::vec3 normal;
    glm::vec3 point;
    mat_t material;

    RaycastHit();
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_);
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_, const mat_t& mat_);
    inline void BlendColor(const mat_t& material2) const;
};
