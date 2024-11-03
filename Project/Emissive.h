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
        attenuation = clr{static_cast<Uint8>(color.r * m_intensity),
                        static_cast<Uint8>(color.g * m_intensity),
                        static_cast<Uint8>(color.b * m_intensity),
                        static_cast<Uint8>(128)};
        return false;
    }
};