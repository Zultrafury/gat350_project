#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MathUtils.h"
#include "Ray.h"

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

    float m_fov{ 45 }; // fov in degrees
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
    
    Camera(int w, int h) {
        m_width = w;
        m_height  = h;
        m_aspectratio = static_cast<float>(w)/static_cast<float>(h);
        m_projection = glm::perspective(glm::radians(90.0f), m_aspectratio, 0.1f, 100.0f);
    }

    explicit Camera(Renderer& ren) : Camera(ren.width,ren.height) {}
    
    glm::vec4 ViewToProjection(const glm::vec3& position)
    {
        return m_projection * glm::vec4{position, 1};
    }

    glm::vec4 ModelToView(const glm::vec4& model)
    {
        return model/m_position;
    }

    glm::ivec2 ViewToScreen(const glm::vec3& position)
    {
        glm::vec4 clip = ViewToProjection(position);
        glm::vec3 ndc = clip / clip.w;

        float x = (ndc.x + 1) * (m_width * 0.5f);
        float y = (1 - ndc.y) * (m_height * 0.5f);

        return glm::ivec2(x,y);
    }

    glm::vec3 ScreenToView(const glm::ivec2& position)
    {
        float x = static_cast<float>(position.x) / (m_width * 0.5f) - 1;
        float y = -(static_cast<float>(position.y) / (m_height * 0.5f) - 1);
        glm::vec4 clip = ViewToProjection({x,y,0.1});
        return clip / clip.w;
    }

    glm::vec3 CamPos()
    {
        glm::vec3 pos = m_position * glm::vec4{1};
        return pos;
    }

    void SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
    {
        m_eye = eye;

        // create camera axis
        m_forward = glm::normalize(target - eye);
        m_right = glm::normalize(Cross(up, m_forward));
        m_up = Cross(m_forward, m_right);

        CalculateViewPlane();
    }

    Ray GetRay(const glm::vec2& point) const
    {
        Ray ray;

        ray.origin = m_eye;
        ray.direction = (m_lowerLeft + (m_horizontal * (point.x/m_width)) + (m_vertical * (point.y/m_height)));

        return ray;
    }

    void CalculateViewPlane()
    {
        float theta = glm::radians(m_fov);

        // tan = o / a

        float halfHeight = glm::tan(theta * 0.5f);
        float height = halfHeight * 2;
        float width = height * m_aspectratio;

        m_horizontal = m_right * width;
        m_vertical = m_up * height;

        m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) + m_forward;
    }
};
