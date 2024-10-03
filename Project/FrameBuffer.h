#pragma once
#include <SDL.h>
#include <vector>
#include "Renderer.h"

using clr = SDL_Color;

class FrameBuffer
{
public:
    FrameBuffer(Renderer& renderer, int width, int height)
    {
        m_width = width; m_height = height;
        m_buffer.resize((unsigned long long)height * width);
        m_pitch = 4 * width;
        m_texture = SDL_CreateTexture(renderer.r,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING,width,height);
    }

    void Update()
    {
        SDL_UpdateTexture(m_texture,NULL,&m_buffer,m_pitch);
    }
    void Clear(const clr& color)
    {
        std::fill(m_buffer.begin(), m_buffer.end(), color);
    }

    void CopyFrameBuffer(Renderer& renderer)
    {
        SDL_RenderCopy(renderer.r, m_texture, nullptr, nullptr);
    }

    void DrawPoint(int x, int y, const clr& color)
    {
        m_buffer.at(x + y * m_width) = color;
    }

public:
    int m_width{ 0 };
    int m_height{ 0 };
    int m_pitch{ 0 };

    SDL_Texture* m_texture{ nullptr };
    std::vector<clr> m_buffer;
};