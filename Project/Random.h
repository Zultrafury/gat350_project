#pragma once
#include <cstdlib>
#include <glm/vec3.hpp>

inline glm::vec3 random(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::vec3{
        (fmod(rand(),v2.x*100) + v1.x*100) / 100,
        (fmod(rand(),v2.y*100) + v1.y*100) / 100,
        (fmod(rand(),v2.z*100) + v1.z*100) / 100,
    };
}
