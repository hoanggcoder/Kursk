#include "Input.h"
#include "Game.h"
Input* Input::s_Instance=nullptr;
Input::Input()
{
m_KeyStates=SDL_GetKeyboardState(nullptr);
}
bool Input::Listen()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {   case SDL_QUIT: return false ;
            case SDL_KEYDOWN: KeyDown();break;
            case SDL_KEYUP: KeyUp();break;
        }
        return true;
    }
}
bool Input::GetKeyDown(SDL_Scancode key)
{
    if(m_KeyStates[key]==1)
       {
          return true;
       }
    return false;
}
void Input::KeyUp()
{
    m_KeyStates=SDL_GetKeyboardState(nullptr);
}
void Input::KeyDown()
{
    m_KeyStates=SDL_GetKeyboardState(nullptr);
}


