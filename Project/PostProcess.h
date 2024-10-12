#pragma once
#include <algorithm>
#include <SDL_pixels.h>

#include "Image.h"

using clr = SDL_Color;

namespace PostProcess
{
    void Invert(Image& image)
    {
        for (auto& i : image.m_buffer)
        {
            i.r = 255 - i.r;
            i.g = 255 - i.g;
            i.b = 255 - i.b;
        }
    }
    
    void Monochrome(Image& image)
    {
        for (auto& i : image.m_buffer)
        {
            const Uint8 avg = (i.r * i.g * i.b)/(255*255);
            i = {avg,avg,avg,i.a};
        }
    }
    
    void ColorBalance(Image& image, int ro, int go, int bo)
    {
        for (auto& i : image.m_buffer)
        {
            i.r = min(max(static_cast<int>(i.r) + ro,0),255);
            i.g = min(max(static_cast<int>(i.g) + go,0),255);
            i.b = min(max(static_cast<int>(i.b) + bo,0),255);
        }
    }

    void Brightness(Image& image, int brightness)
    {
        for (auto& i : image.m_buffer)
        {
            i.r = min(max(static_cast<int>(i.r) + brightness,0),255);
            i.g = min(max(static_cast<int>(i.g) + brightness,0),255);
            i.b = min(max(static_cast<int>(i.b) + brightness,0),255);
        }
    }

    void Noise(Image& image, int intensity)
    {
        for (auto& i : image.m_buffer)
        {
            int offset = (rand() % ((intensity * 2) + 1)) - intensity;
            i.r = min(max(static_cast<int>(i.r) + offset,0),255);
            offset = (rand() % ((intensity * 2) + 1)) - intensity;
            i.g = min(max(static_cast<int>(i.g) + offset,0),255);
            offset = (rand() % ((intensity * 2) + 1)) - intensity;
            i.b = min(max(static_cast<int>(i.b) + offset,0),255);
        }
    }

    void Threshold(Image& image, int threshold)
    {
        Monochrome(image);
        for (auto& i : image.m_buffer)
        {
            if (i.r > threshold)
            {
                i = {255,255,255,i.a};
            }
            else
            {
                i = {0,0,0,i.a};
            }
        }
    }

    void Posterize(Image& image, int levels)
    {
        int level = 255/levels;
        for (auto& i : image.m_buffer)
        {
            i.r = min(max((static_cast<int>(i.r) / level) * level,0),255);
            i.g = min(max((static_cast<int>(i.g) / level) * level,0),255);
            i.b = min(max((static_cast<int>(i.b) / level) * level,0),255);
        }
    }
}