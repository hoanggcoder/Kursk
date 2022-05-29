#include"Shell.h"
#include "TextureManager.h"
#include "Input.h"
Shell::Shell()
{   xpos=SHELL_OUT;
    ypos=SHELL_OUT;
}
Shell::~Shell()
{
}
void Shell::update()
{   if(angle==0)
    {ypos=ypos-velocity;}
    if(angle==90)
    {xpos=xpos+velocity;}
    if(angle==180)
    {ypos=ypos+velocity;}
    if(angle==-90)
    {xpos=xpos-velocity;}
    srcR.h=BASIC_WIDTH;
    srcR.w=BASIC_HEIGHT;
    srcR.x=0;
    srcR.y=0;
    dstR.x=xpos;
    dstR.y=ypos;
    dstR.w=srcR.w/2;
    dstR.h=srcR.h/2;
}
void Shell::render()
{
    SDL_RenderCopyEx(Game::renderer,ShellTexture,&srcR,&dstR,angle,NULL,SDL_FLIP_NONE);
}
