#include "Color.h"

clr(*blend_func)(clr src, clr dest);

enum class BlendMode
{
    Normal, Alpha,
    Additive, Multiply
};

inline clr ColorBlend(clr src, clr dest)
{
    return blend_func(src,dest);
}

inline clr NormalBlend(clr src, clr dest)
{
    return src;
}

inline clr AlphaBlend(clr src, clr dest)
{
    uint8_t alpha = src.a;
    uint8_t inv_alpha = 255 - alpha; // 1(255) - alpha

    clr color;
    color.r = ((src.r * alpha) + (dest.r * inv_alpha)) >> 8;
    color.g = ((src.g * alpha) + (dest.g * inv_alpha)) >> 8;
    color.b = ((src.b * alpha) + (dest.b * inv_alpha)) >> 8;
    color.a = src.a;

    return color;
}

inline clr AdditiveBlend(clr src, clr dest)
{
    clr color;
    color.r = std::min(src.r + dest.r,255);
    color.g = std::min(src.g + dest.g,255);
    color.b = std::min(src.b + dest.b,255);
    color.a = src.a;

    return color;
}

inline clr MultiplyBlend(clr src, clr dest)
{
    clr color;
    color.r = std::min(src.r * dest.r >> 8,255);
    color.g = std::min(src.g * dest.g >> 8,255);
    color.b = std::min(src.b * dest.b >> 8,255);
    color.a = src.a;

    return color;
}

inline void SetBlendMode(BlendMode mode)
{
    switch (mode)
    {
    case BlendMode::Normal:
        blend_func = NormalBlend;
        break;
    case BlendMode::Alpha:
        blend_func = AlphaBlend;
        break;
    case BlendMode::Additive:
        blend_func = AdditiveBlend;
        break;
    case BlendMode::Multiply:
        blend_func = MultiplyBlend;
        break;
    }
}