#include "Material.h"

using clr = SDL_Color;

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
