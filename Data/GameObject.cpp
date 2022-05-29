#include "GameObject.h"
#include "TextureManager.h"
#include "Input.h"
GameObject::GameObject(const char* filedir,int x, int y,int v)
{
    objectTexture=TextureManager::LoadImage(filedir);
    xpos=x;
    ypos=y;
    velocity=v;
}
void GameObject::update()
{   if(player1controlled==true)
    {if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {   if(xpos>=BASIC_WIDTH)
        {xpos=xpos-velocity;}
        SetAngle(-90);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
    {   if(ypos>=BASIC_HEIGHT)
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
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
    {
        typeofshell=2;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E))
    {
        typeofshell=1;
    }
    if(typeofshell==2)
    {
        tankshell.ShellTexture=TextureManager::LoadImage("Assets/shell2.png");
    }
    if(typeofshell==1) {tankshell.ShellTexture=TextureManager::LoadImage("Assets/shell.png");}
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {   if(firing==0&&typeofshell==1)
        {
            tankshell.angle=angle;
            tankshell.velocity=10;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=5;
            firing=1;
        }
        else if(firing==0&&typeofshell==2)
        {
            tankshell.angle=angle;
            tankshell.velocity=25;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=1;
            firing=1;
        }
        if(tankshell.xpos>=SCREEN_WIDTH||tankshell.xpos<=0||tankshell.ypos>=SCREEN_HEIGHT||tankshell.ypos<=0)
        {
            firing=0;
        }
    }
    }

    if(player1controlled==false)
    {if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
    {   if(xpos>=BASIC_WIDTH)
        {xpos=xpos-velocity;}
        SetAngle(-90);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP))
    {   if(ypos>=BASIC_HEIGHT)
        {ypos=ypos-velocity;}
        SetAngle(0);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
    {   if(xpos<=SCREEN_WIDTH-BASIC_WIDTH*2)
        {xpos=xpos+velocity;}
        SetAngle(90);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN))
    {   if(ypos<=SCREEN_HEIGHT-BASIC_HEIGHT*2)
        {ypos=ypos+velocity;}
        SetAngle(180);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFTBRACKET))
    {
        typeofshell=2;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHTBRACKET))
    {
        typeofshell=1;
    }
    if(typeofshell==2)
    {
        tankshell.ShellTexture=TextureManager::LoadImage("Assets/shell2.png");
    }
    if(typeofshell==1) {tankshell.ShellTexture=TextureManager::LoadImage("Assets/shell.png");}
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_BACKSPACE))
    {   if(firing==0&&typeofshell==1)
        {
            tankshell.angle=angle;
            tankshell.velocity=10;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=5;
            firing=1;
        }
        if(firing==0&&typeofshell==2)
        {
            tankshell.angle=angle;
            tankshell.velocity=25;
            tankshell.xpos=xpos+10;
            tankshell.ypos=ypos+10;
            tankshell.damage=1;
            firing=1;
        }
        if(tankshell.xpos>=SCREEN_WIDTH||tankshell.xpos<=0||tankshell.ypos>=SCREEN_HEIGHT||tankshell.ypos<=0)
        {
            firing=0;
            tankshell.xpos=2000;
            tankshell.ypos=2000;
        }
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
void GameObject::render()
{
    SDL_RenderCopyEx(Game::renderer,objectTexture,&srcR,&dstR,angle,NULL,SDL_FLIP_NONE);
}
