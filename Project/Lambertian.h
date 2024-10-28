#pragma once
#include <SDL_pixels.h>

#include "Material.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "glm/gtc/random.hpp"

using clr = SDL_Color;

class Lambertian : virtual public Material
{
public:
    Lambertian(const clr& color_) : Material{ color_ } {}
    
    bool Scatter(const Ray& ray, const RaycastHit& raycastHit, clr& attenuation, Ray& scattered) const override
    {
        glm::vec3 direction = raycastHit.normal + glm::sphericalRand(1.0f);

        scattered = Ray{ raycastHit.point, direction };
        attenuation = color;

        return true;
    }
};