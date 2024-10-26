#include <iostream>
#include <SDL.h>
#include <thread>

#include "FrameBuffer.h"
#include "KeyInput.h"
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
    Image img = Image(); img.Load("bg.jpg"); PostProcess::Posterize(img,16); PostProcess::Brightness(img,-100);
    Model obj1;
    while(true)
    {
        if (obj1.Load("centeredtorus.obj")) { break; }
    }
    Model obj2; obj2.SetColor({0,255,0,0});
    while(true)
    {
        if (obj2.Load("cube.obj")) { break; }
    }
    Model obj3; obj3.SetColor({255,128,0,128});
    while(true)
    {
        if (obj3.Load("ham.obj")) { break; }
    }
    SetBlendMode(BlendMode::Alpha);
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);
    KeyInput key = KeyInput();
    int mx; int my;
    
    auto startnano = std::chrono::high_resolution_clock::now();

    glm::mat4 pos1 = glm::mat4(  1,0,0,0,
                                0,1,0,0,
                                0,0,1,0,
                                0,0,0,2);
    glm::mat4 pos2 = glm::mat4(  1,0,0,0,
                                0,2,0,0,
                                0,0,1,0,
                                2,0,0,2);
    glm::mat4 pos3 = glm::mat4(  0.1,0,0,0,
                                0,-0.1,0,0,
                                0,0,0.1,0,
                                -2,0.25,0,2);
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
        key.Update();

        auto nextnano = std::chrono::high_resolution_clock::now();
        auto nanointerval = std::chrono::duration_cast<std::chrono::nanoseconds>(nextnano-startnano).count();
        if (nanointerval > (1000000000/60))
        {
            //time
            startnano = nextnano;

            //input
            if (key.GetKey("left"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{-0.02,0,0});
            }
            if (key.GetKey("right"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0.02,0,0});
            }
            if (key.GetKey("up"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0,0.02,0});
            }
            if (key.GetKey("down"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0,-0.02,0});
            }
            if (key.GetKey("c"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0,0,0.02});
            }
            if (key.GetKey("v"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0,0,-0.02});
            }
            if (key.GetKey("w"))
            {
                cam.m_position = glm::rotate(cam.m_position,0.02f, glm::normalize(glm::vec3(1.0,0,0.0)));
            }
            if (key.GetKey("s"))
            {
                cam.m_position = glm::rotate(cam.m_position,-0.02f, glm::normalize(glm::vec3(1.0,0,0.0)));
            }
            if (key.GetKey("a"))
            {
                cam.m_position = glm::rotate(cam.m_position,0.02f, glm::normalize(glm::vec3(0,1.0,0.0)));
            }
            if (key.GetKey("d"))
            {
                cam.m_position = glm::rotate(cam.m_position,-0.02f, glm::normalize(glm::vec3(0,1.0,0.0)));
            }
            
            //draw
            SetBlendMode(BlendMode::Alpha);
            renderer.Draw();
            fbuff.Clear({ 0,0,0,255 });

            fbuff.DrawImage(0,-70,img);

            //pos = glm::rotate(pos,0.01f,normalize(glm::vec3(0.5,1.0,0.0)));
            obj1.Draw(fbuff,pos1,cam);
            SetBlendMode(BlendMode::Normal);
            obj2.Draw(fbuff,pos2,cam);
            SetBlendMode(BlendMode::Additive);
            obj3.Draw(fbuff,pos3,cam);
            
            fbuff.Update();
            fbuff.CopyFrameBuffer(renderer);
            
            SDL_RenderPresent(renderer.r);
        }
    }
    return 0;
}
