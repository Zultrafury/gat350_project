#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::mat4 m_projection;
    int m_width{ 0 };
    int m_height{ 0 };
    
    Camera(int w, int h) {
        m_width = w;
        m_height  = h;
        m_projection = glm::perspective(glm::radians(60.0f), static_cast<float>(m_width)/static_cast<float>(m_height), 0.1f, 100.0f);
    }
    
    glm::vec4 ViewToProjection(const glm::vec3& position)
    {
        return m_projection * glm::vec4{position, 1};
    }

    glm::vec4 ModelToView(const glm::vec4& model)
    {
        return model/m_projection;
    }

    glm::ivec2 ViewToScreen(const glm::vec3& position)
    {
        glm::vec4 clip = ViewToProjection(position);
        glm::vec3 ndc = clip / clip.w;

        float x = (ndc.x + 1) * (m_width * 0.5f);
        float y = (1 - ndc.y) * (m_height * 0.5f);

        return glm::ivec2(x,y);
    }
};
