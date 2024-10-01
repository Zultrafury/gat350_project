#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

class Renderer
{
public:
    static bool Initialize()
    {
        // initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cerr << "Error initializing SDL: " << SDL_GetError() << endl;
            return true;
        }
        return false;
    }

    static bool CreateWindow()
    {
        // create window
        // returns pointer to window if successful or nullptr if failed
        SDL_Window* window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        
        if (window == nullptr)
        {
            cerr << "Error creating SDL window: " << SDL_GetError() << endl;
            SDL_Quit();
            return true;
        }

        // create renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

        while (true)
        {
            // clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            // show screen
            SDL_RenderPresent(renderer);
        }

        return false;
    }
};
