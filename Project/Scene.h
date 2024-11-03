#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>

#include "Emissive.h"
#include "SceneObject.h"
#include "Sphere.h"


class Scene
{
public:
    std::vector<SceneObject*> m_objects;
    
    void Trace(SceneObject* object, const int i, const int j,
        const Ray& ray, RaycastHit& rayhit, Ray& scatter,
        FrameBuffer& fbuff, clr& color, const clr& att,
        float maxDistance, int depth)
        {
        if (depth <= 0) { return; }
        Sphere* sph = dynamic_cast<Sphere*>(object);
        Plane* plane = dynamic_cast<Plane*>(object);
        if (sph != nullptr)
        {
            glm::intersectRaySphere(scatter.origin, scatter.direction, sph->m_center, sph->m_radius, rayhit.point, rayhit.normal);
        }
        if (plane != nullptr)
        {
            float intersect;
            glm::intersectRayPlane(scatter.origin, scatter.direction, plane->m_center, plane->m_normal, intersect);
            rayhit.normal = plane->m_normal; rayhit.point = scatter.origin + scatter.direction * intersect;
        }
        for (auto& object2 : m_objects)
        {
            if (glm::length(rayhit.point - scatter.direction) < maxDistance)
            {
                if (object != object2 && object2->Hit(scatter))
                {
                    clr color2 = object2->m_material->color;
                    if (dynamic_cast<Emissive*>(object2->m_material.get()))
                    {
                        clr att2;
                        object2->m_material->Scatter(ray,rayhit,att2,scatter);
                        color = AlphaBlend(att2,color2);
                    }
                    else
                    {
                        color = AlphaBlend(att,color2);
                    }
                    fbuff.DrawPoint(i,fbuff.m_height - j,color);
                }
                Trace(object2,i,j,scatter,rayhit,scatter,fbuff,color,att,maxDistance,depth-1);
            }
        }
    }
    
    void Render(FrameBuffer& fbuff, Camera& cam, int samples)
    {
        for (int i = 0; i < fbuff.m_width; ++i)
        {
            for (int j = 0; j < fbuff.m_height; ++j)
            {
                for (auto& object : m_objects)
                {
                    Ray ray = cam.GetRay({i,j});
                    Ray scatter = Ray();
                    RaycastHit rayhit = RaycastHit();
                    Sphere* sph = dynamic_cast<Sphere*>(object);
                    Plane* plane = dynamic_cast<Plane*>(object);
                    if (sph != nullptr)
                    {
                        glm::intersectRaySphere(ray.origin, ray.direction, sph->m_center, sph->m_radius, rayhit.point, rayhit.normal);
                    }
                    if (plane != nullptr)
                    {
                        float intersect;
                        glm::intersectRayPlane(ray.origin, ray.direction, plane->m_center, plane->m_normal, intersect);
                        rayhit.normal = plane->m_normal; rayhit.point = ray.origin + ray.direction * intersect;
                    }
                    if (object->Hit(ray))
                    {
                        clr color = object->m_material->color;
                        clr att;
                        fbuff.DrawPoint(i,fbuff.m_height - j,color);

                        for (int r = 0; r < samples; ++r)
                        {
                            if (object->m_material->Scatter(ray,rayhit,att,scatter))
                            {
                                Trace(object,i,j,ray,rayhit,scatter,fbuff,color,att,25.0f,1);
                            }
                        }
                    }
                }
            }
        }
    }
};
