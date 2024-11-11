#include "Scene.h"

void Scene::Trace(SceneObject*& object, int i, int j,
           const Ray& ray, RaycastHit& rayhit, Ray& scatter,
           FrameBuffer& fbuff, clr& color, clr& att,
           float maxDistance, int samples, int depth)
    {
    if (depth <= 0) { return; }
    //sort(m_objects.begin(), m_objects.end(),ZSort);
    for (auto& object2 : m_objects)
    {
        if (glm::length(scatter.origin) - glm::length(ray.origin) < maxDistance)
        {
            if (object != object2 && object2->Hit(scatter,rayhit))
            {
                rayhit.BlendColor(object2->m_material);
                if (depth == 1)
                {
                    //fbuff.DrawPoint(i,fbuff.m_height - j,rayhit.mat->color);
                }
            }
            //else { return; }
            for (int r = 0; r < samples; ++r)
            {
                if (object->m_material->Scatter(ray,rayhit,att,scatter))
                {
                    Trace(object2,i,j,scatter,rayhit,scatter,fbuff,color,att,maxDistance,samples,depth-1);
                }
            }
        }
    }
}

void Scene::Render(FrameBuffer& fbuff, Camera& cam, Renderer& renderer, int samples, int depth)
{
    for (int i = 0; i < fbuff.m_width; ++i)
    {
        if (i%10 == 0)
        {
            cout << round((i/static_cast<float>(fbuff.m_width)*100)) << "% ";
        }
        for (int j = 0; j < fbuff.m_height; ++j)
        {
            for (auto& object : m_objects)
            {
                Ray ray = cam.GetRay({i,j});
                Ray scatter = Ray();
                RaycastHit rayhit = RaycastHit();
                clr color = object->m_material->color;
                if (object->Hit(ray,rayhit))
                {
                    rayhit.material = object->m_material;
                    //fbuff.DrawPoint(i,fbuff.m_height - j,color);
                    clr att;
                    for (int r = 0; r < samples; ++r)
                    {
                        if (object->m_material->Scatter(ray,rayhit,att,scatter))
                        {
                            Trace(object,i,j,ray,rayhit,scatter,fbuff,color,att,100.0f,samples,depth);
                        }
                    }
                    break;
                }
            }
            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            SDL_RenderPresent(renderer.r);
        }
    }
}

bool Scene::ZSort(SceneObject*& i1, SceneObject*& i2)
{
    //cout << i1.m_t << ", " << i2.m_t << '\n';
    return (i1->m_t > i2->m_t);
}
