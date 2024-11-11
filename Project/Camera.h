#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Ray.h"
#include "Renderer.h"

class Camera
{
public:
    glm::mat4 m_projection;
    int m_width{ 0 };
    int m_height{ 0 };
    glm::mat4 m_position = glm::mat4( 1,0,0,0,
                                0,1,0,0,
                                0,0,0,1,
                                0,0,1,0);

    float m_fov{ 60 }; // fov in degrees
    float m_aspectratio{ 1 }; // screen width / screen height
 
    glm::vec3 m_eye{ 0 };
 
    // camera axis
    glm::vec3 m_forward{ 0 };
    glm::vec3 m_right{ 0 };
    glm::vec3 m_up{ 0 };
 
    // view plane origin and horizontal and vertical direction vectors
    glm::vec3 m_lowerLeft{ 0 };
    glm::vec3 m_horizontal{ 0 };
    glm::vec3 m_vertical{ 0 };
    
    Camera(int w, int h);

    explicit Camera(Renderer& ren);
    
    glm::vec4 ViewToProjection(const glm::vec3& position);

    glm::vec4 ModelToView(const glm::vec4& model);

    glm::ivec2 ViewToScreen(const glm::vec3& position);

    glm::vec3 ScreenToView(const glm::ivec2& position);

    glm::vec3 CamPos() const;

    void SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

    Ray GetRay(const glm::vec2& point) const;

    void CalculateViewPlane();
};
