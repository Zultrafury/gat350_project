#include <iostream>
#include <SDL.h>

#include "FrameBuffer.h"
#include "Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Renderer renderer = Renderer();
    renderer.Initialize();
    renderer.CreateWindow(900,600);
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);

    while(true)
    {
        renderer.Draw();
        fbuff.Clear({ 0,0,0,255 });
        
        for (int i = 0; i < 1000; i++)
        {
            int x = rand()%renderer.width;
            int y = rand()%renderer.height;
            //cout << x << ", " << y << endl;
            fbuff.DrawPoint(x,y,{ 255,0,255,255 });
        }

        fbuff.Update();
        fbuff.CopyFrameBuffer(renderer);
        SDL_RenderPresent(renderer.r);
    }
    return 0;
}
