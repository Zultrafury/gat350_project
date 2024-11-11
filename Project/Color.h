#pragma once
#include <algorithm>
#include <SDL_pixels.h>

using clr = SDL_Color;

enum class BlendMode;

inline clr ColorBlend(clr src, clr dest);

inline clr NormalBlend(clr src, clr dest);

inline clr AlphaBlend(clr src, clr dest);

inline clr AdditiveBlend(clr src, clr dest);

inline clr MultiplyBlend(clr src, clr dest);

inline void SetBlendMode(BlendMode mode);