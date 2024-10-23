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

    void Alpha(Image& image, int alpha)
    {
        for (auto& i : image.m_buffer)
        {
            i.a = alpha;
        }
    }

    void BoxBlur(Image& image)
    {
        {
            // create source buffer to read from, buffer will be written to
            std::vector<clr> source = image.m_buffer;

            // kernal values
            int16_t k[3][3] =
                {
                { 1, 1, 1 },
                { 1, 1, 1 },
                { 1, 1, 1 }
                };

            // process buffer pixels
            for (int i = 0; i < source.size(); i++)
            {
                // get pixel x, y
                int x = i%image.m_width;
                int y = i/image.m_width;

                // check bounds (x and y must be one pixel away from buffer edges)
                if (x < 1 || x + 1 >= image.m_width || y < 1 || y + 1 >= image.m_height) continue;

                // color values from kernel operation
                int r = 0;
                int g = 0;
                int b = 0;

                // process kernel pixels
                for (int iy = 0; iy < 3; iy++)
                {
                    for (int ix = 0; ix < 3; ix++)
                    {
                        // get pixel in kernel
                        const clr& pixel = source[(x + ix - 1) + (y + iy - 1) * image.m_width];
                        // get kernel weight
                        int weight = k[iy][ix];

                        // accumulate color values of kernel pixels
                        r += pixel.r * weight;
                        g += pixel.g * weight;
                        b += pixel.b * weight;
                    }
                }

                // set buffer color, set values from average of kernel color values
                clr& color = image.m_buffer[x + y * image.m_width];
                color.r = static_cast<uint8_t>(r / 9);
                color.g = static_cast<uint8_t>(g / 9);
                color.b = static_cast<uint8_t>(b / 9);
            }
        }
    }

    void GaussianBlur(Image& image)
    {
        {
            // create source buffer to read from, buffer will be written to
            std::vector<clr> source = image.m_buffer;

            // kernal values
            int16_t k[3][3] =
                {
                { 1, 2, 1 },
                { 2, 4, 2 },
                { 1, 2, 1 }
                };

            // process buffer pixels
            for (int i = 0; i < source.size(); i++)
            {
                // get pixel x, y
                int x = i%image.m_width;
                int y = i/image.m_width;

                // check bounds (x and y must be one pixel away from buffer edges)
                if (x < 1 || x + 1 >= image.m_width || y < 1 || y + 1 >= image.m_height) continue;

                // color values from kernel operation
                int r = 0;
                int g = 0;
                int b = 0;

                // process kernel pixels
                for (int iy = 0; iy < 3; iy++)
                {
                    for (int ix = 0; ix < 3; ix++)
                    {
                        // get pixel in kernel
                        const clr& pixel = source[(x + ix - 1) + (y + iy - 1) * image.m_width];
                        // get kernel weight
                        int weight = k[iy][ix];

                        // accumulate color values of kernel pixels
                        r += pixel.r * weight;
                        g += pixel.g * weight;
                        b += pixel.b * weight;
                    }
                }

                // set buffer color, set values from average of kernel color values
                clr& color = image.m_buffer[x + y * image.m_width];
                color.r = static_cast<uint8_t>(r / 16);
                color.g = static_cast<uint8_t>(g / 16);
                color.b = static_cast<uint8_t>(b / 16);
            }
        }
    }

    void Sharpen(Image& image)
    {
        {
            // create source buffer to read from, buffer will be written to
            std::vector<clr> source = image.m_buffer;

            // kernal values
            int16_t k[3][3] =
                {
                { 0, -1, 0 },
                { -1, 5, -1 },
                { 0, -1, 0 }
                };

            // process buffer pixels
            for (int i = 0; i < source.size(); i++)
            {
                // get pixel x, y
                int x = i%image.m_width;
                int y = i/image.m_width;

                // check bounds (x and y must be one pixel away from buffer edges)
                if (x < 1 || x + 1 >= image.m_width || y < 1 || y + 1 >= image.m_height) continue;

                // color values from kernel operation
                int r = 0;
                int g = 0;
                int b = 0;

                // process kernel pixels
                for (int iy = 0; iy < 3; iy++)
                {
                    for (int ix = 0; ix < 3; ix++)
                    {
                        // get pixel in kernel
                        const clr& pixel = source[(x + ix - 1) + (y + iy - 1) * image.m_width];
                        // get kernel weight
                        int weight = k[iy][ix];

                        // accumulate color values of kernel pixels
                        r += pixel.r * weight;
                        g += pixel.g * weight;
                        b += pixel.b * weight;
                    }
                }

                // set buffer color, set values from average of kernel color values
                clr& color = image.m_buffer[x + y * image.m_width];
                color.r = static_cast<uint8_t>(min(max(r, 0), 255));
                color.g = static_cast<uint8_t>(min(max(g, 0), 255));
                color.b = static_cast<uint8_t>(min(max(b, 0), 255));
            }
        }
    }

    void EdgeDetection(Image& image, int threshold)
    {
        {
            // create source buffer to read from, buffer will be written to
            std::vector<clr> source = image.m_buffer;

            // kernal values
            int16_t kh[3][3] =
            {
                {  1, 0, -1 },
                {  2, 0, -2 },
                {  1, 0, -1 },
            };

            int16_t kv[3][3] =
            {
                { -1, -2, -1 },
                {  0,  0,  0 },
                {  1,  2,  1 },
            };

            // process buffer pixels
            for (int i = 0; i < source.size(); i++)
            {
                // get pixel x, y
                int x = i%image.m_width;
                int y = i/image.m_width;

                // check bounds (x and y must be one pixel away from buffer edges)
                if (x < 1 || x + 1 >= image.m_width || y < 1 || y + 1 >= image.m_height) continue;

                // color values from kernel operation
                int h = 0;
                int v = 0;

                // process kernel pixels
                for (int iy = 0; iy < 3; iy++)
                {
                    for (int ix = 0; ix < 3; ix++)
                    {
                        // get pixel in kernel
                        const clr& pixel = source[(x + ix - 1) + (y + iy - 1) * image.m_width];
                        // get kernel weight
                        h += pixel.r * kh[iy][ix];
                        v += pixel.r * kv[iy][ix];
                        h += pixel.g * kh[iy][ix];
                        v += pixel.g * kv[iy][ix];
                        h += pixel.b * kh[iy][ix];
                        v += pixel.b * kv[iy][ix];
                    }
                }

                // set buffer color, set values from average of kernel color values
                uint16_t m = static_cast<uint16_t>(sqrt((h * h) + (v * v)));
                m = (m > threshold) ? m : 0;

                uint8_t c = (m < 0) ? 0 : ((m > 255) ? 255 : m);

                clr& color = image.m_buffer[i];
                color.r = c;
                color.g = c;
                color.b = c;
            }
        }
    }

    void Emboss(Image& image)
    {
        {
            // create source buffer to read from, buffer will be written to
            Monochrome(image);
            std::vector<clr> source = image.m_buffer;

            // kernal values
            int16_t k[3][3] =
                {
                { -2, -1, 0 },
                { -1, 0, 1 },
                {  0, 1, 2 }
                };

            // process buffer pixels
            for (int i = 0; i < source.size(); i++)
            {
                // get pixel x, y
                int x = i%image.m_width;
                int y = i/image.m_width;

                // check bounds (x and y must be one pixel away from buffer edges)
                if (x < 1 || x + 1 >= image.m_width || y < 1 || y + 1 >= image.m_height) continue;

                // color values from kernel operation
                int r = 0;
                int g = 0;
                int b = 0;

                // process kernel pixels
                for (int iy = 0; iy < 3; iy++)
                {
                    for (int ix = 0; ix < 3; ix++)
                    {
                        // get pixel in kernel
                        const clr& pixel = source[(x + ix - 1) + (y + iy - 1) * image.m_width];
                        // get kernel weight
                        int weight = k[iy][ix];

                        // accumulate color values of kernel pixels
                        r += pixel.r * weight;
                        g += pixel.g * weight;
                        b += pixel.b * weight;
                    }
                }

                // set buffer color, set values from average of kernel color values
                clr& color = image.m_buffer[x + y * image.m_width];
                color.r = static_cast<uint8_t>(min(max(r+128, 0), 255));
                color.g = static_cast<uint8_t>(min(max(g+128, 0), 255));
                color.b = static_cast<uint8_t>(min(max(b+128, 0), 255));
            }
        }
    }
}