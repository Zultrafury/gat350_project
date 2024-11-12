#include "RaycastHit.h"

#include "Material.h"
#include "Color.h"
#include "Emissive.h"
#include "Lambertian.h"

RaycastHit::RaycastHit()
{
    normal = glm::vec3{0};
    point = glm::vec3{0};
}

RaycastHit::RaycastHit(const glm::vec3& normal_, const glm::vec3& point_)
{
    normal = normal_; point = point_;
}

RaycastHit::RaycastHit(const glm::vec3& normal_, const glm::vec3& point_, mat_t& mat_) : RaycastHit(normal_, point_)
{
    material = mat_;
} 

void RaycastHit::BlendColor(const mat_t& material2) const
{
    if (dynamic_cast<Lambertian*>(material.get()))
    {
        if (dynamic_cast<Lambertian*>(material2.get()))
        {
            material->color = MultiplyBlend(material2->color,material->color);
        }
        else if (dynamic_cast<Emissive*>(material2.get()))
        {
            material->color = AdditiveBlend(material2->color,material->color);
        }
    }
}
