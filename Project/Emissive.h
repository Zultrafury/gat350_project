#pragma once
#include <SDL_pixels.h>

#include "Material.h"
#include "MathUtils.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "glm/gtc/random.hpp"

class Emissive : virtual public Material
{
public:
    float m_intensity = 1;
    Emissive(const clr& color_, float intensity) : Material{ color_ }, m_intensity{ intensity }{}
    
    bool Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const override
    {
        attenuation = clr{static_cast<Uint8>(255),
                        static_cast<Uint8>(255),
                        static_cast<Uint8>(255),
                        color.a};
        return true;
    }

    clr GetColor() override
    {
        clr col = clr{static_cast<Uint8>(255),
                        static_cast<Uint8>(255),
                        static_cast<Uint8>(255),
                        color.a};
        return col;
    }
};