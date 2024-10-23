#pragma once
#include <iostream>
#include <SDL_pixels.h>
#include <string>
#include <vector>
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
using clr = SDL_Color;


class Image
{
public:
    Image() = default;
    ~Image() = default;
    
    bool Load(const std::string& filename)
    {
        // load image getting the width and height (pass 4 for the last parameter to create RGBA image)
        int channels;
        bool iok = stbi_info(filename.c_str(),&m_width, &m_height,nullptr);
        if (!iok)
        {
            std::cerr << "Error querying image: " << filename << std::endl;
            return false;
        }
        uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 4);
        if (data == nullptr)
        {
            std::cerr << "Error loading image: " << filename << std::endl;
            return false;
        }

        // resize the image buffer to the number of pixels in the image
        m_buffer.resize(m_width * m_height);

        // copy the image data into the buffer, !!takes in number of bytes to copy!! 
        std::memcpy(m_buffer.data(),data,m_width * m_height * 4); // https://en.cppreference.com/w/cpp/string/byte/memcpy

        // free the image data
        stbi_image_free(data);

        std::cerr << "Image successfully loaded: " << filename << std::endl;
        return true;
    }

public:
    int m_width{ 0 };
    int m_height{ 0 };

    std::vector<clr> m_buffer;
};
