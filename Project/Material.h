#pragma once
#include <SDL_pixels.h>

using clr = SDL_Color;

class Material
{
public:
    clr color;
    Material(const clr& color_)
    {
        color = color_;
    }
};