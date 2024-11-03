#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

class Renderer
{
public:
    SDL_Renderer* r;
    SDL_Window* w;
    int width;
    int height;
    
    bool Initialize()
    {
        r = nullptr;
        // initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cerr << "Error initializing SDL: " << SDL_GetError() << endl;
            return true;
        }
        return false;
    }

    bool CreateWindow(int _w, int _h)
    {
        // create window
        // returns pointer to window if successful or nullptr if failed
        width = _w; height = _h;
        w = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _w, _h, SDL_WINDOW_MOUSE_FOCUS | SDL_RENDERER_ACCELERATED);
        
        if (w == nullptr)
        {
            cerr << "Error creating SDL window: " << SDL_GetError() << endl;
            SDL_Quit();
            return true;
        }

        // create renderer
        r = SDL_CreateRenderer(w, -1, 0);

        return false;
    }

    void Draw()
    {
        // clear screen
        SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
        SDL_RenderClear(r);
    }

    void PostDraw()
    {
        // show screen
        SDL_RenderPresent(r);
    }
};
