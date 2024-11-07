#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>

#include "MathUtils.h"
#include "SceneObject.h"


class Plane : virtual public SceneObject
{
public:
    glm::vec3 m_normal;
    glm::vec3 m_center;
    
    Plane(const glm::vec3& center, const glm::vec3& normal, const std::shared_ptr<Material>& material) : SceneObject(material) {
        m_center = center;
        m_normal = normal;
    }
 
    bool Hit(Ray& ray, RaycastHit& rayhit) override
    {
        float intersect;
        glm::intersectRayPlane(ray.origin, ray.direction, m_center, m_normal, intersect);
        rayhit.normal = m_normal; rayhit.point = ray.origin + ray.direction * intersect;
        if (rayhit.point.z > 5.51 || rayhit.point.x > 3 || rayhit.point.y > 2 || rayhit.point.x < -3 || rayhit.point.y < -1.51)
        {
            return false;
        }
        // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane so it never hits plane
        // the dot product is 0 if the two vectors are perpendicular (90 degrees)
        float denominator = dot(ray.direction, m_normal);
        if (approximately(denominator, 0))
        {
            return false; // ray direction and plane parallel, no intersection
        }
 
        // get t (distance) along ray direction to hit point
        float t = glm::dot((m_center - ray.origin),m_normal) / denominator;
        m_t = t;
        if (t < 0)
        {
            return false; // plane behind ray's origin, no intersection
        }
        return true;
    }
};
