#pragma once
#include <map>
#include <SDL.h>

class KeyInput
{
public:
    std::map<std::string, bool> keymap;
    std::map<std::string, bool> waspressed;
    std::map<std::string, bool> keyclick;
    const Uint8* keystate; //= SDL_GetKeyboardState(nullptr);
    
    KeyInput()
    {
        keystate = SDL_GetKeyboardState(nullptr);

    }

    void Update()
    {
        Scancodes();
        for (auto const& key : keymap)
        {
            keyclick[key.first] = 0;
            if (GetKey(key.first))
            {
                if (!waspressed[key.first])
                {
                    keyclick[key.first] = 1;
                }
                waspressed[key.first] = 1;
            }
            else
            {
                waspressed[key.first] = 0;
            }
        }
        
    }

    bool GetKey(std::string c)
    {
        return keymap[c];
    }

    bool GetKeyDown(std::string c)
    {
        return keyclick[c];
    }
    
    void Scancodes()
    {
        keystate = SDL_GetKeyboardState(nullptr);
        
        //scancode hell
        keymap["a"] = keystate[SDL_SCANCODE_A];
        keymap["b"] = keystate[SDL_SCANCODE_B];
        keymap["c"] = keystate[SDL_SCANCODE_C];
        keymap["d"] = keystate[SDL_SCANCODE_D];
        keymap["e"] = keystate[SDL_SCANCODE_E];
        keymap["f"] = keystate[SDL_SCANCODE_F];
        keymap["g"] = keystate[SDL_SCANCODE_G];
        keymap["h"] = keystate[SDL_SCANCODE_H];
        keymap["i"] = keystate[SDL_SCANCODE_I];
        keymap["j"] = keystate[SDL_SCANCODE_J];
        keymap["k"] = keystate[SDL_SCANCODE_K];
        keymap["l"] = keystate[SDL_SCANCODE_L];
        keymap["m"] = keystate[SDL_SCANCODE_M];
        keymap["n"] = keystate[SDL_SCANCODE_N];
        keymap["o"] = keystate[SDL_SCANCODE_O];
        keymap["p"] = keystate[SDL_SCANCODE_P];
        keymap["q"] = keystate[SDL_SCANCODE_Q];
        keymap["r"] = keystate[SDL_SCANCODE_R];
        keymap["s"] = keystate[SDL_SCANCODE_S];
        keymap["t"] = keystate[SDL_SCANCODE_T];
        keymap["u"] = keystate[SDL_SCANCODE_U];
        keymap["v"] = keystate[SDL_SCANCODE_V];
        keymap["w"] = keystate[SDL_SCANCODE_W];
        keymap["x"] = keystate[SDL_SCANCODE_X];
        keymap["y"] = keystate[SDL_SCANCODE_Y];
        keymap["z"] = keystate[SDL_SCANCODE_Z];
        keymap["1"] = keystate[SDL_SCANCODE_1];
        keymap["2"] = keystate[SDL_SCANCODE_2];
        keymap["3"] = keystate[SDL_SCANCODE_3];
        keymap["4"] = keystate[SDL_SCANCODE_4];
        keymap["5"] = keystate[SDL_SCANCODE_5];
        keymap["6"] = keystate[SDL_SCANCODE_6];
        keymap["7"] = keystate[SDL_SCANCODE_7];
        keymap["8"] = keystate[SDL_SCANCODE_8];
        keymap["9"] = keystate[SDL_SCANCODE_9];
        keymap["0"] = keystate[SDL_SCANCODE_0];
        keymap["-"] = keystate[SDL_SCANCODE_MINUS];
        keymap["="] = keystate[SDL_SCANCODE_EQUALS];
        keymap["["] = keystate[SDL_SCANCODE_LEFTBRACKET];
        keymap["]"] = keystate[SDL_SCANCODE_RIGHTBRACKET];
        keymap["\\"] = keystate[SDL_SCANCODE_BACKSLASH];
        keymap[";"] = keystate[SDL_SCANCODE_SEMICOLON];
        keymap["\'"] = keystate[SDL_SCANCODE_APOSTROPHE];
        keymap[","] = keystate[SDL_SCANCODE_COMMA];
        keymap["."] = keystate[SDL_SCANCODE_PERIOD];
        keymap["/"] = keystate[SDL_SCANCODE_SLASH];
        keymap["esc"] = keystate[SDL_SCANCODE_ESCAPE];
        keymap["`"] = keystate[SDL_SCANCODE_GRAVE];
        keymap["tab"] = keystate[SDL_SCANCODE_TAB];
        keymap["caps"] = keystate[SDL_SCANCODE_CAPSLOCK];
        keymap["lshift"] = keystate[SDL_SCANCODE_LSHIFT];
        keymap["lctrl"] = keystate[SDL_SCANCODE_LCTRL];
        keymap["win"] = keystate[SDL_SCANCODE_LGUI];
        keymap["lalt"] = keystate[SDL_SCANCODE_LALT];
        keymap["space"] = keystate[SDL_SCANCODE_SPACE];
        keymap["rshift"] = keystate[SDL_SCANCODE_RSHIFT];
        keymap["rctrl"] = keystate[SDL_SCANCODE_RCTRL];
        keymap["ralt"] = keystate[SDL_SCANCODE_RALT];
        keymap["left"] = keystate[SDL_SCANCODE_LEFT];
        keymap["up"] = keystate[SDL_SCANCODE_UP];
        keymap["right"] = keystate[SDL_SCANCODE_RIGHT];
        keymap["down"] = keystate[SDL_SCANCODE_DOWN];
        keymap["backspace"] = keystate[SDL_SCANCODE_BACKSPACE];
        keymap["enter"] = keystate[SDL_SCANCODE_RETURN];
    }
};
