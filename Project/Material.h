#pragma once
#include <SDL_pixels.h>

#include "Ray.h"
#include "RaycastHit.h"

using clr = SDL_Color;

class Material
{
public:
    virtual ~Material() = default;
    clr color;
    Material(const clr& color_)
    {
        color = color_;
    }
    virtual bool Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const
    {
        return false;
    }
};