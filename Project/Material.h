#pragma once
#include <SDL_pixels.h>

#include "Ray.h"
class RaycastHit;


using clr = SDL_Color;

class Material
{
public:
    virtual ~Material();
    clr color;
    
    Material(const clr& color_);
    
    virtual bool Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const;
    virtual clr GetColor();
};
