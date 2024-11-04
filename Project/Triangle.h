#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <memory>
#include <glm/gtx/intersect.hpp>

#include "SceneObject.h"
#include "MathUtils.h"

class Triangle : public SceneObject
{
public:
    glm::vec3 m_v1{ 0, 0, 0 };
    glm::vec3 m_v2{ 0, 0, 0 };
    glm::vec3 m_v3{ 0, 0, 0 };
    glm::vec2 m_bary{ 0, 0 };
    glm::vec3 m_normal{ 0, 0, 0 };
    float m_t = 0;
    float m_z = 0;
    
    Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const std::shared_ptr<Material>& material) : SceneObject(material)
    {
        m_v1 = v1; m_v2 = v2; m_v3 = v3;
        glm::vec3 edge1 = m_v2 - m_v1;
        glm::vec3 edge2 = m_v3 - m_v1;
        m_normal = Cross(edge2,edge1);
    }

    bool operator==(Triangle const& t2) const
    {
        return m_v1 == t2.m_v1 && m_v2 == t2.m_v2 && m_v3 == t2.m_v3 && m_normal == t2.m_normal;
    }

    bool Hit(Ray& ray, RaycastHit& rayhit) override
    {
        if (!glm::intersectRayTriangle(ray.origin, ray.direction, m_v1,m_v2,m_v3, m_bary, m_t))
        {
            return false;
        }

        glm::vec3 edge1 = m_v2 - m_v1;
        glm::vec3 edge2 = m_v3 - m_v1;
        m_t = dot(edge2, Cross(m_v1 - ray.origin,edge1)) * 1 / dot(Cross(ray.direction,edge2),edge1);

        m_normal = Cross(edge2,edge1);

        rayhit.normal = m_normal; rayhit.point = ray.origin + ray.direction * m_t;

        m_z = length(rayhit.point);

        if (m_bary.x < 0 || m_bary.x > 1)
        {
            return false;
        }
        if (m_bary.y < 0 or m_bary.x + m_bary.y > 1)
        {
            return false;
        }
        /*
        // set edges of the triangle
        glm::vec3 edge1 = m_v2 - m_v1;
        glm::vec3 edge2 = m_v3 - m_v1;

        // calculate perpendicular vector, determine how aligned the ray is with the triangle plane
        glm::vec3 pvec = Cross(ray.direction,edge2);
        float determinant = dot(pvec,edge1);

        // if determinant is less than 0 then ray is hitting back of triangle
        // if determinant is 0 then ray is parallel to triangle surface
        if (determinant < 0 || approximately(determinant,0))
        {
            return false;
        }

        // inverse determinant
        float invDet = 1 / determinant;

        // create direction vector from the triangle first vertex to the ray origin
        glm::vec3 tvec = m_v1 - ray.origin;
        // Calculate u parameter for barycentric coordinates
        float u = dot(tvec, pvec) * invDet;
        // Check if u is outside the bounds of the triangle, no intersection
        if (u < 0 || u > 1)
        {
            return false;
        }
        
        // Calculate qvec, a vector perpendicular to both tvec and edge1, used to find the v parameter
        glm::vec3 qvec = Cross(tvec,edge1);
        // Calculate v parameter for barycentric coordinates
        float v = dot(qvec, ray.direction) * invDet;
        // Check if v is outside the bounds or if u + v exceeds 1, no intersection
        if (v < 0 or u + v > 1)
        {
            return false;
        }

        // Calculate intersection distance and check range
        m_t = dot(edge2, qvec) * invDet;

        m_normal = glm::normalize(Cross(edge1,edge2));
        m_bary = {u,v};
        */

        return true;
    }
};
