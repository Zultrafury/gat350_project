#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <vector>

#include "Camera.h"
#include "FrameBuffer.h"
#include "SceneObject.h"

class Scene
{
public:
    std::vector<SceneObject*> m_objects;
    
    void Trace(SceneObject*& object, int i, int j,
               const Ray& ray, RaycastHit& rayhit, Ray& scatter,
               FrameBuffer& fbuff, clr& color, clr& att,
               float maxDistance, int samples, int depth);
    
    void Render(FrameBuffer& fbuff, Camera& cam, Renderer& renderer, int samples, int depth);

    static bool ZSort(SceneObject*& i1, SceneObject*& i2);
};
