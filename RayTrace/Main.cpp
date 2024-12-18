﻿#include <iostream>
#include <SDL.h>
#include <thread>

#include "FrameBuffer.h"
#include "Model.h"
#include "PostProcess.h"
#include "Renderer.h"
#include "stb_image.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Renderer renderer = Renderer();
    renderer.Initialize();
    renderer.CreateWindow(900,600);
    Camera cam = Camera(renderer);
    Image img = Image(); img.Load("angy.png");
    Image imga = Image(); imga.Load("viggrad.png");
    Image imgb = Image(); imgb.Load("colors.png");
    Model cube;
    while(true)
    {
        if (cube.Load("centeredtorus.obj")) { break; }
    }
    SetBlendMode(BlendMode::Alpha);
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);
    int mx; int my;
    
    auto startnano = std::chrono::high_resolution_clock::now();

    glm::mat4 pos = glm::mat4(  1,0,0,0,
                                0,1,0,0,
                                0,0,1,0,
                                0,0,1,1);
    //pos = glm::translate(pos,glm::vec3(0.0,-100.0,0.0));

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << cam.m_projection[i][j] << ", ";
        }
        cout << '\n';
    }
    
    while(true)
    {
        SDL_PumpEvents();
        Uint32 mc = SDL_GetMouseState(&mx,&my);

        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {

            startnano = nextnano;
            renderer.Draw();
            fbuff.Clear({ 0,0,0,255 });

            pos = glm::rotate(pos,0.01f,normalize(glm::vec3(0.5,1.0,0.0)));
            cube.Draw(fbuff,pos,cam);
            
            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            
            SDL_RenderPresent(renderer.r);
        }
    }
    return 0;
}
