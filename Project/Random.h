#pragma once
#include <cstdlib>
#include <glm/vec3.hpp>

inline glm::vec3 random(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::vec3{
        fmod(rand(),v2.x) + v1.x,
        fmod(rand(),v2.y) + v1.y,
        fmod(rand(),v2.z) + v1.z,
    };
}
