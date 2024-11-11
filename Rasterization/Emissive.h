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
        attenuation = clr{static_cast<Uint8>(color.r),
                        static_cast<Uint8>(color.g),
                        static_cast<Uint8>(color.b),
                        static_cast<Uint8>(255 * m_intensity)};
        return false;
    }

    clr GetColor() override
    {
        clr col = color;
        col.a = static_cast<Uint8>(min(static_cast<int>(static_cast<float>(color.a) * m_intensity),255));
        return col;
    }
};