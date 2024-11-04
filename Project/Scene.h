#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "Emissive.h"
#include "SceneObject.h"
#include "Sphere.h"

class Scene
{
public:
    std::vector<SceneObject*> m_objects;
    
    void Trace(SceneObject*& object, const int i, const int j,
        Ray& ray, RaycastHit& rayhit, Ray& scatter,
        FrameBuffer& fbuff, clr& color, const clr& att,
        float maxDistance, int depth)
        {
        if (depth <= 0) { return; }
        for (auto& object2 : m_objects)
        {
            if (object->m_t < maxDistance)
            {
                if (object != object2 && object2->Hit(scatter,rayhit))
                {
                    clr color2 = object2->m_material->GetColor();
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
                    if (object->Hit(ray,rayhit))
                    {
                        clr color = object->m_material->color;
                        clr att;
                        fbuff.DrawPointNB(i,min((fbuff.m_height - j),fbuff.m_height-1),color);

                        for (int r = 0; r < samples; ++r)
                        {
                            if (object->m_material->Scatter(ray,rayhit,att,scatter))
                            {
                                Trace(object,i,j,ray,rayhit,scatter,fbuff,color,att,15.0f,1);
                            }
                        }
                    }
                }
            }
        }
    }
};
