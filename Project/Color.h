#pragma once
#include <algorithm>
#include <SDL_pixels.h>

using clr = SDL_Color;

enum class BlendMode
{
    Normal, Alpha,
    Additive, Multiply
};

clr ColorBlend(clr src, clr dest);

clr NormalBlend(clr src, clr dest);

clr AlphaBlend(clr src, clr dest);

clr AdditiveBlend(clr src, clr dest);

clr MultiplyBlend(clr src, clr dest);

void SetBlendMode(BlendMode mode);