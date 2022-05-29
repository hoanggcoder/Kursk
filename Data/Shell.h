#include "Game.h"
#include "TextureManager.h"
#ifndef SHELL_H
#define SHELL_H
class Shell
{
public:
    Shell();
    ~Shell();
    void update();
    void render();
    int xpos;
    int ypos;
    int velocity;
    int angle;
    int damage;
    SDL_Texture* ShellTexture=TextureManager::LoadImage("Assets/image/shell.png");
    SDL_Rect srcR,dstR;

};
#endif // SHELL_H
