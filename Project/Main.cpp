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
        
        for (int i = 0; i < 1; i++)
        {
            int x = rand()%renderer.width;
            int y = rand()%renderer.height;
            //fbuff.DrawPoint(x, y, { 255,255,255,255 });
            SDL_SetRenderDrawColor(renderer.r, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer.r,x,y);
            cout << x << ", " << y << endl;
        }

        fbuff.Update();
        fbuff.CopyFrameBuffer(renderer);

        SDL_RenderPresent(renderer.r);
    }
    return 0;
}
