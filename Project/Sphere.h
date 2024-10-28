#pragma once
#include <memory>
#include <glm/vec3.hpp>

#include "SceneObject.h"

class Sphere : virtual public SceneObject
{
public:
    float m_radius;
    glm::vec3 m_center;

    Sphere(const glm::vec3& center, const float& radius, const std::shared_ptr<Material>& material) : SceneObject(material) {
        m_center = center;
        m_radius = radius;
    }
    
    bool Hit(const Ray& ray) override
    {
        // Vector from the ray origin to the center of the sphere
        glm::vec3 oc = ray.origin - m_center;
 
        // Coefficients for the quadratic equation
        // a = dot(ray direction, ray direction), which is the square of the length of the ray direction
        float a = glm::dot(ray.direction, ray.direction);
 
        // b = 2 * dot(ray direction, oc), where oc is the vector from the ray origin to the sphere center
        float b = 2 * glm::dot(ray.direction, oc);
 
        // c = dot(oc, oc) - radius^2, which accounts for the distance from the origin to the center minus the radius of the sphere
        float c = glm::dot(oc, oc) - (m_radius * m_radius);
 
        // Discriminant of the quadratic equation: b^2 - 4ac
        // This tells us how many real solutions (hits) exist:
        // If discriminant < 0, no real solutions (no intersection)
        // If discriminant = 0, one solution (the ray grazes the sphere)
        // If discriminant > 0, two solutions (the ray hits the sphere twice)
        float discriminant = (b * b) - (4 * a * c);

        return discriminant > 0;
    }
};
