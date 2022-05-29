#ifndef Input_H
#define Input_H
#include "SDL.h"
class Input
{
public:
    static Input* GetInstance()
    {
        return s_Instance=(s_Instance!=nullptr) ? s_Instance: new Input();
    }
    bool Listen();
    bool GetKeyDown(SDL_Scancode key);
private:
    Input();
    void KeyUp();
    void KeyDown();
    const Uint8* m_KeyStates;
    static Input* s_Instance;

};

#endif // Input_H
