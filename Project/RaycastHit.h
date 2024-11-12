#pragma once
#include <memory>
#include <glm/vec3.hpp>
class Material;
using mat_t = std::shared_ptr<Material>;

class RaycastHit
{
public:
    glm::vec3 normal;
    glm::vec3 point;
    mat_t material;

    RaycastHit();
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_);
    RaycastHit(const glm::vec3& normal_, const glm::vec3& point_, mat_t& mat_);
    void BlendColor(const mat_t& material2) const;
};
