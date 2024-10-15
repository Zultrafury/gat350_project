#include <iostream>
#include <SDL.h>
#include <thread>

#include "FrameBuffer.h"
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
    Image img = Image(); img.Load("angy.png");
    Image imga = Image(); imga.Load("colors.png");
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);
    int mx = 0; int my = 0;
    
    auto startnano = std::chrono::high_resolution_clock::now();
    
    while(true)
    {
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            //SDL_GetMouseState(&mx,&my);

            startnano = nextnano;
            renderer.Draw();
            fbuff.Clear({ 0,0,0,255 });

            SetBlendMode(BlendMode::Normal);
            fbuff.DrawImage(200,50,img);
            SetBlendMode(BlendMode::Additive);
            fbuff.DrawImage(250,100,imga);
            //fbuff.DrawPoint(mx,my,{255,255,255,255});

            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            
            SDL_RenderPresent(renderer.r);
        }
    }
    return 0;
}
