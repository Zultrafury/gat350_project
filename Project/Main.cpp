#include <iostream>
#include <SDL.h>

#include "Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
    Renderer::Initialize();
    Renderer::CreateWindow();
    
    return 0;
}
