#include "Material.h"

Material::~Material() = default;

Material::Material(const clr& color_)
{
    color = color_;
}
bool Material::Scatter(const Ray& ray, RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const
{
    return false;
}
clr Material::GetColor()
{
    return color;
}
