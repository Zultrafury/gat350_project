﻿#pragma once
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
        //direction.x += (static_cast<float>(rand() % 100)/200) - 0.25f;
        //direction.y += (static_cast<float>(rand() % 100)/200) - 0.25f;
        //direction.z += (static_cast<float>(rand() % 100)/200) - 0.25f;

        scattered = Ray{ raycastHit.point, direction };
        attenuation = clr{static_cast<Uint8>(color.r / 2),
                        static_cast<Uint8>(color.g/2),
                        static_cast<Uint8>(color.b/2),
                        16};

        return true;
    }
};