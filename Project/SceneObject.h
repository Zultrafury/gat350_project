#pragma once
#include "Material.h"
#include "Ray.h"

class SceneObject
{
public:
    virtual ~SceneObject() = default;
    SceneObject(const std::shared_ptr<Material>& material)
    {
        m_material = material;
    }
    std::shared_ptr<Material> m_material = nullptr;
    virtual bool Hit(Ray& ray, RaycastHit& rayhit)
    {
        return false;
    }
};
