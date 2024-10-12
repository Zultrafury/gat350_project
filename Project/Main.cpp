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
    Image img = Image(); img.Load("angy.png"); PostProcess::Posterize(img,8);
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);
    auto startnano = std::chrono::high_resolution_clock::now();

    while(true)
    {
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            startnano = nextnano;
            renderer.Draw();
            fbuff.Clear({ 0,0,0,255 });
            
            fbuff.DrawImage(200,50,img);
            //fbuff.DrawPoint(0,0,{255,255,255,255});

            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            SDL_RenderPresent(renderer.r);
        }
    }
    return 0;
}
