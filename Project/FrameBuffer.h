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
        if (x > 0 && x < m_width && y > 0 && y < m_height)
        {
            m_buffer.at(x + y * m_width) = color;
        }
    }
    
    void DrawLine(int x1, int y1, int x2, int y2, const clr& color)
    {
        if (x2 < x1) {
            swap(x1,x2);
            swap(y1,y2);
        }
        
        int m_new = 2 * (y2 - y1); 
        int slope_error_new = m_new - (x2 - x1);
        float slope = static_cast<float>(y2 - y1) / static_cast<float>(x2 - x1);
    
        if (slope > 1)
        {
            if (y2 < y1) {
                swap(x1,x2);
                swap(y1,y2);
            }
            m_new = 2 * (x2 - x1); 
            slope_error_new = m_new - (y2 - y1);
            
            for (int x = x1, y = y1; y <= y2; y++) { 
                DrawPoint(x,y,color);
            
                slope_error_new += m_new;
            
                if (slope_error_new >= 0) { 
                    x++; 
                    slope_error_new -= 2 * (y2 - y1); 
                } 
            }
        }
        else if (slope < -1)
        {
            if (y2 < y1) {
                swap(x1,x2);
                swap(y1,y2);
            }
            m_new = 2 * (x1 - x2); 
            slope_error_new = m_new - (y2 - y1);
            
            for (int x = x1, y = y1; y <= y2; y++) { 
                DrawPoint(x,y,color);
            
                slope_error_new += m_new;
            
                if (slope_error_new >= 0) { 
                    x--; 
                    slope_error_new -= 2 * (y2 - y1); 
                } 
            }
        }
        else
        {
            if (x1 == x2)
            {
                if (y1 > y2)
                {
                    swap(y1,y2);
                }
                for (int x = x1, y = y1; y <= y2; y++) { 
                    DrawPoint(x,y,color);
                }
            }
            else if (y1 > y2)
            {
                m_new = 2 * (y1 - y2); 
                for (int x = x1, y = y1; x <= x2; x++) { 
                    DrawPoint(x,y,color);
            
                    slope_error_new += m_new;
            
                    if (slope_error_new >= 0) { 
                        y--; 
                        slope_error_new -= 2 * (x2 - x1); 
                    } 
                }
            }
            else
            {
                for (int x = x1, y = y1; x <= x2; x++) { 
                    DrawPoint(x,y,color);
            
                    slope_error_new += m_new;
            
                    if (slope_error_new >= 0) { 
                        y++; 
                        slope_error_new -= 2 * (x2 - x1); 
                    } 
                }
            }
        }
    }

    void DrawCircle(int xc, int yc, int radius, const clr& color)
    {
        int x = 0, y = radius;
        int d = 3 - 2 * radius;

        DrawPoint(xc+x, yc+y, color);
        DrawPoint(xc-x, yc+y, color);
        DrawPoint(xc+x, yc-y, color);
        DrawPoint(xc-x, yc-y, color);
        DrawPoint(xc+y, yc+x, color);
        DrawPoint(xc-y, yc+x, color);
        DrawPoint(xc+y, yc-x, color);
        DrawPoint(xc-y, yc-x, color);
        
        while (y >= x){
      
            // check for decision parameter
            // and correspondingly 
            // update d, y
            if (d > 0) {
                y--; 
                d = d + 4 * (x - y) + 10;
            }
            else
                d = d + 4 * x + 6;

            // Increment x after updating decision parameter
            x++;
        
            // Draw the circle using the new coordinates
            DrawPoint(xc+x, yc+y, color);
            DrawPoint(xc-x, yc+y, color);
            DrawPoint(xc+x, yc-y, color);
            DrawPoint(xc-x, yc-y, color);
            DrawPoint(xc+y, yc+x, color);
            DrawPoint(xc-y, yc+x, color);
            DrawPoint(xc+y, yc-x, color);
            DrawPoint(xc-y, yc-x, color);
        }
    }

    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const clr& color)
    {
        DrawLine(x1,y1,x2,y2,color);
        DrawLine(x2,y2,x3,y3,color);
        DrawLine(x1,y1,x3,y3,color);
    }

public:
    int m_width{ 0 };
    int m_height{ 0 };
    int m_pitch{ 0 };

    SDL_Texture* m_texture{ nullptr };
    std::vector<clr> m_buffer;
};