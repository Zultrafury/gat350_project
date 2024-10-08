#include <iostream>
#include <SDL.h>
#include <thread>

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
    auto startnano = std::chrono::high_resolution_clock::now();

    while(true)
    {
        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/1))
        {
            startnano = nextnano;
            renderer.Draw();
            fbuff.Clear({ 0,0,0,255 });
            SDL_Color color = { 255,0,255,255 };
        
            for (int i = 0; i < 3; i++)
            {
                int x = rand()%renderer.width;
                int y = rand()%renderer.height;
                int r = rand()%25+1;
                int x1 = rand()%renderer.width;
                int y1 = rand()%renderer.height;
                int x2 = rand()%renderer.width;
                int y2 = rand()%renderer.height;
                int _x1 = rand()%renderer.width;
                int _y1 = rand()%renderer.height;
                int _x2 = rand()%renderer.width;
                int _y2 = rand()%renderer.height;
                int _x3 = rand()%renderer.width;
                int _y3 = rand()%renderer.height;
                //cout << x << ", " << y << endl;
                //fbuff.DrawLine(60,40,80,0,{ 255,0,0,255 });
                //fbuff.DrawLine(0,0,20,40,{ 0,255,0,255 });
                //fbuff.DrawLine(80,80,60,40,{ 0,0,255,255 });
                //fbuff.DrawLine(0,80,20,40,{ 255,0,255,255 });
                fbuff.DrawCircle(x,y,r,{ 255,0,0,255 });
                //fbuff.DrawPoint(_x1,_y1,{ 255,0,0,255 });
                //fbuff.DrawPoint(_x1,_y1,{ 0,0,255,255 });
                fbuff.DrawLine(x1,y1,x2,y2,color);
                fbuff.DrawTriangle(_x1,_y1,_x2,_y2,_x3,_y3,{ 0,0,255,255 });
            }

            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            SDL_RenderPresent(renderer.r);
        }
    }
    return 0;
}
