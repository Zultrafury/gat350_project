#pragma once
#define FLT_EPSILON      1.192092896e-07F 
#include <cmath>

inline bool approximately(float value1, float value2)
{
    // check if the difference between the values is less than epsilon
    return (abs(value2 - value1) < FLT_EPSILON);
}

inline glm::vec3 Cross(const glm::vec3& v1, const glm::vec3& v2)
{
    glm::vec3 result;
 
    result.x = v1.y * v2.z - v2.y * v1.z;
    result.y = v1.z * v2.x - v2.z * v1.x;
    result.z = v1.x * v2.y - v2.x * v1.y;
 
    return result;
}
