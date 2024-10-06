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
        m_buffer.resize(height * width);
        Clear({ 0,0,0,255 });
        m_pitch = 4 * width;
        m_texture = SDL_CreateTexture(renderer.r,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING,width,height);
    }

    void Update()
    {
        
        SDL_UpdateTexture(m_texture,NULL,m_buffer.data(),m_pitch);
    }
    void Clear(const clr& color)
    {
        std::fill(m_buffer.begin(), m_buffer.end()-1, color);
    }

    void CopyFrameBuffer(Renderer& renderer)
    {
        SDL_RenderCopy(renderer.r, m_texture, NULL, NULL);
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