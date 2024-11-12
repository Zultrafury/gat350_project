#include <iostream>
#include <SDL.h>
#include <thread>

#include "FrameBuffer.h"
#include "KeyInput.h"
#include "Lambertian.h"
#include "Model.h"
#include "Plane.h"
#include "Random.h"
#include "Renderer.h"
#include "Scene.h"
#include "Sphere.h"
#include "stb_image.h"
#include "SceneObject.h"
#include "Emissive.h"
#include "Metal.h"
#include "Color.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Renderer renderer = Renderer();
    renderer.Initialize();
    renderer.CreateWindow(300,200);
    Camera cam = Camera(renderer);
    cam.SetView({0,0,0},{0,0,1},{0,1,0});
    
    //Image img = Image(); img.Load("bg.jpg"); PostProcess::Posterize(img,16); PostProcess::Brightness(img,-100);
    
    SetBlendMode(BlendMode::Alpha);
    FrameBuffer fbuff = FrameBuffer(renderer,renderer.width,renderer.height);
    KeyInput key = KeyInput();
    int mx; int my;
    
    auto startnano = std::chrono::high_resolution_clock::now();

    /*
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
    */

    //RAYTRACING

    vector<shared_ptr<Material>> mats;
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 192, 192, 192, 255 })); //0
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 255, 0, 0, 255 })); //1
    mats.push_back(std::make_shared<Metal>(SDL_Color{ 0, 0, 255, 255 }, 1)); //2
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 255, 0, 255, 255 })); //3
    mats.push_back(std::make_shared<Emissive>(SDL_Color{ 0, 255, 255, 255 }, 1)); //4
    mats.push_back(std::make_shared<Emissive>(SDL_Color{ 255, 255, 255, 255 }, 0.05)); //5
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 255, 255, 0, 255 })); //6
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 255, 0, 0, 255 })); //7
    mats.push_back(std::make_shared<Lambertian>(SDL_Color{ 0, 255, 0, 255 })); //8
    mats.push_back(std::make_shared<Metal>(SDL_Color{ 128, 128, 128, 255 },2)); //9
    mats.push_back(std::make_shared<Metal>(SDL_Color{ 255, 0, 0, 255 }, 5)); //10
    mats.push_back(std::make_shared<Metal>(SDL_Color{ 0, 255, 0, 255 }, 5)); //11
    mats.push_back(std::make_shared<Metal>(SDL_Color{ 192, 192, 192, 255 }, 5)); //12

    Scene scene;

    auto plane6 = new Plane(glm::vec3{0, 0, -0.5}, glm::vec3{0, 0, -1}, mats[0]); scene.m_objects.push_back(plane6);

    scene.m_objects.push_back(new Sphere({0,2,5}, 1, mats.at(5)));

    
    auto plane4 = new Plane(glm::vec3{2, 0, 0}, glm::vec3{-1, 0, 0}, mats[7]); scene.m_objects.push_back(plane4);
    auto plane3 = new Plane(glm::vec3{-2, 0, 0}, glm::vec3{1, 0, 0}, mats[8]); scene.m_objects.push_back(plane3);
    auto plane5 = new Plane(glm::vec3{0, 0, 5.5}, glm::vec3{0, 0, -1}, mats[0]); scene.m_objects.push_back(plane5);

    auto plane = new Plane(glm::vec3{0, -1.5, 0}, glm::vec3{0, 1, 0}, mats[0]); scene.m_objects.push_back(plane);
    auto plane2 = new Plane(glm::vec3{0, 2, 0}, glm::vec3{0, -1, 0}, mats[0]); scene.m_objects.push_back(plane2);
    
    //auto obj1 = new Model(mats[0]); scene.m_objects.push_back(obj1); while(true) { if (obj1->Load("centeredtorus.obj")) { break; } }
    //auto obj2 = new Model(mats[6]); scene.m_objects.push_back(obj2); obj2->SetColor({0,255,0,0}); while(true) { if (obj2->Load("cube.obj")) { break; } }
    /*
    for (int i = 0; i < obj2->m_vertices.size()-2; i+=3 )
    {
        scene.m_objects.push_back( new Triangle(obj2->m_vertices[i],obj2->m_vertices[i+1],obj2->m_vertices[i+2],obj2->m_material));
        cout << obj2->m_vertices[i].x << ", " << obj2->m_vertices[i].y << ", " << obj2->m_vertices[i].z << '\n';
        cout << obj2->m_vertices[i+1].x << ", " << obj2->m_vertices[i+1].y << ", " << obj2->m_vertices[i+1].z << '\n';
        cout << obj2->m_vertices[i+2].x << ", " << obj2->m_vertices[i+2].y << ", " << obj2->m_vertices[i+2].z << "\n\n";
    }
    */
    //auto obj3 = new Model(mats[5],{0,2.5,5}); scene.m_objects.push_back(obj3); obj3->SetColor({0,0,0,0}); while(true) { if (obj3->Load("cube.obj")) { break; } }
    //auto obj4 = new Model(mats[12],{-1,-1,5}); scene.m_objects.push_back(obj4); obj4->SetColor({0,0,0,0}); while(true) { if (obj4->Load("cube.obj")) { break; } }
    
    //for (int i = 0; i < 20; ++i)
    //{
        //auto sphere = new Sphere(random(glm::vec3{-12 }, glm::vec3{12 }) + glm::vec3{2.5,2.5,20}, (rand()%21+5)/10, mats.at(rand()%7+1));
        //cout << sphere->m_center.x << ", " << sphere->m_center.y << ", " << sphere->m_center.z << "\n";
        //scene.m_objects.push_back(sphere);
    //}
    //scene.m_objects.push_back(new Sphere({-1.5,0,6}, 1, mats.at(5)));
    //scene.m_objects.push_back(new Sphere({0,1.75,8}, 1, mats.at(2)));
    //scene.m_objects.push_back(new Sphere({1,0,5}, 1, mats.at(12)));
    //scene.m_objects.push_back(new Triangle({-0.5,0.5,5.5},{-0.5,0.5,5.5},{0.5,-0.5,5.5}, mats.at(6)));
    //scene.m_objects.push_back(new Triangle({0,1,5.5},{1,-2,5.5},{-1,0,5.5}, mats.at(6)));

    
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
            cout << "\n\n" << chrono::duration_cast<chrono::milliseconds>(nextnano-startnano).count()*0.001f << "\n\n";
            startnano = nextnano;
            cam.CalculateViewPlane();
            
            //input
            /*
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
                cam.SetView(cam.m_eye + glm::vec3{0,0,0.1},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            if (key.GetKey("v"))
            {
                cam.m_projection = glm::translate(cam.m_projection,{0,0,-0.02});
                cam.SetView(cam.m_eye + glm::vec3{0,0,-0.1},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            if (key.GetKey("w"))
            {
                cam.m_position = glm::rotate(cam.m_position,0.02f, glm::normalize(glm::vec3(1.0,0,0.0)));
                cam.SetView(cam.m_eye + glm::vec3{0,0.01,0},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            if (key.GetKey("s"))
            {
                cam.m_position = glm::rotate(cam.m_position,-0.02f, glm::normalize(glm::vec3(1.0,0,0.0)));
                cam.SetView(cam.m_eye + glm::vec3{0,-0.01,0},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            if (key.GetKey("a"))
            {
                cam.m_position = glm::rotate(cam.m_position,0.02f, glm::normalize(glm::vec3(0,1.0,0.0)));
                cam.SetView(cam.m_eye + glm::vec3{-0.01,0,0},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            if (key.GetKey("d"))
            {
                cam.m_position = glm::rotate(cam.m_position,-0.02f, glm::normalize(glm::vec3(0,1.0,0.0)));
                cam.SetView(cam.m_eye + glm::vec3{0.01,0,0},cam.m_eye + glm::vec3{0,0,1},{0,1,0});
            }
            */
            /*
            //pos = glm::rotate(pos,0.01f,normalize(glm::vec3(0.5,1.0,0.0)));
            obj1.Draw(fbuff,pos1,cam);
            SetBlendMode(BlendMode::Normal);
            obj2.Draw(fbuff,pos2,cam);
            SetBlendMode(BlendMode::Additive);
            obj3.Draw(fbuff,pos3,cam);
            */

            //draw
            scene.Render(fbuff,cam,renderer,5,20);
            renderer.Draw();
            
            //fbuff.Update();
            //fbuff.CopyFrameBuffer(renderer);
            
            //SDL_RenderPresent(renderer.r);
            while (mc != 2)
            {
                SDL_PumpEvents();
                mc = SDL_GetMouseState(&mx,&my);
            }
            fbuff.Clear({ 0,0,0,255 });
        }
    }
    return 0;
}
