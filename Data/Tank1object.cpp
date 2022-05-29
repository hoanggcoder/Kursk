#include "Tank1object.h"
#include "TextureManager.h"
#include "Input.h"
#include "Sound.h"
Tank1object::Tank1object()
{
    objectTexture=TextureManager::LoadImage("Assets/image/tankp1.png");
    xpos=TANK_1_START_XPOS;
    ypos=TANK_1_START_YPOS;
    velocity=START_VELOCITY;
}
void Tank1object::update()
{

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        if(xpos>=BASIC_WIDTH)
        {xpos=xpos-velocity;}
        SetAngle(-90);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {
        if(ypos>=BASIC_HEIGHT)
        {ypos=ypos-velocity;}
        SetAngle(0);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
    {   if(xpos<=SCREEN_WIDTH-BASIC_WIDTH*2)
        {xpos=xpos+velocity;}
        SetAngle(90);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {   if(ypos<=SCREEN_HEIGHT-BASIC_HEIGHT*2)
        {ypos=ypos+velocity;}
        SetAngle(180);
    }
    if(NewShell==0)
    {if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
    {
        typeofshell=2;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E))
    {
        typeofshell=1;
    }
    }
    else
    {
        typeofshell=3;
    }
    if(typeofshell==1)
    {tankshell.ShellTexture=TextureManager::LoadImage("Assets/image/shell.png");}
    if(typeofshell==2)
    {
        tankshell.ShellTexture=TextureManager::LoadImage("Assets/image/shell2.png");
    }
    if(typeofshell==3)
    {
        tankshell.ShellTexture=TextureManager::LoadImage("Assets/image/shell3.png");
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {   if(firing==0&&typeofshell==1)
        {   Sound::Instance()->LoadEffect("Assets/sound/cannon.wav");
            Sound::Instance()->PlayEffect("Assets/sound/cannon.wav");
            tankshell.angle=angle;
            tankshell.velocity=10;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=4;
            firing=1;
        }
        if(firing==0&&typeofshell==2)
        {   Sound::Instance()->LoadEffect("Assets/sound/beam.wav");
            Sound::Instance()->PlayEffect("Assets/sound/beam.wav");
            tankshell.angle=angle;
            tankshell.velocity=25;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=1;
            firing=1;
        }
        if(firing==0&&typeofshell==3)
        {   Sound::Instance()->LoadEffect("Assets/sound/special.wav");
            Sound::Instance()->PlayEffect("Assets/sound/special.wav");
            tankshell.angle=angle;
            tankshell.velocity=25;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=5;
            firing=1;
        }
        if(tankshell.xpos>=SCREEN_WIDTH||tankshell.xpos<=0||tankshell.ypos>=SCREEN_HEIGHT||tankshell.ypos<=0)
        {
            firing=0;
        }
    }
    srcR.h=BASIC_WIDTH;
    srcR.w=BASIC_HEIGHT;
    srcR.x=0;
    srcR.y=0;
    dstR.x=xpos;
    dstR.y=ypos;
    dstR.w=srcR.w;
    dstR.h=srcR.h;
}
void Tank1object::render()
{
    SDL_RenderCopyEx(Game::renderer,objectTexture,&srcR,&dstR,angle,NULL,SDL_FLIP_NONE);
}

