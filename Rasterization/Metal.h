#pragma once
#include <SDL_pixels.h>

#include "Material.h"
#include "MathUtils.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "glm/gtc/random.hpp"

using clr = SDL_Color;

class Metal : virtual public Material
{
public:
    float m_fuzz = 0;
    Metal(const clr& color_, float fuzz) : Material{ color_ }, m_fuzz{ fuzz }{}
    
    bool Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const override
    {
        glm::vec3 reflected = Reflect(raycastHit.point,raycastHit.normal);

        // set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
        // a mirror has a fuzz value of 0 and a diffused metal surface a higher value
        scattered = Ray{ raycastHit.point, reflected + (glm::sphericalRand(1.0f) * m_fuzz) };
        attenuation = clr{static_cast<Uint8>(color.r),
                        static_cast<Uint8>(color.g),
                        static_cast<Uint8>(color.b),
                        16};

        // check that reflected ray is going away from surface normal (dot product > 0)
        return glm::dot(raycastHit.normal, scattered.direction) > 0;
    }
};