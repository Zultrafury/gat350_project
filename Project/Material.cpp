#include "Material.h"
#include "RaycastHit.h"

Material::~Material() = default;

Material::Material(const clr& color_)
{
    color = color_;
}
bool Material::Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const
{
    return false;
}
clr Material::GetColor()
{
    return color;
}
