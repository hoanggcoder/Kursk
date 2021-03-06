#include "Board.h"
#include "TextureManager.h"
Board::Board()
{
    xpos=340;
    ypos=280;
}
void Board::update()
{
    srcR.w=BASIC_WIDTH*8;
    srcR.h=BASIC_HEIGHT*6;
    srcR.x=0;
    srcR.y=0;
    dstR.x=xpos;
    dstR.y=ypos;
    dstR.w=srcR.w;
    dstR.h=srcR.h;
}
void Board::render(int id)
{   if(id==1)
    {
    objectTexture=TextureManager::LoadImage("Assets/image/resultp1win.png");
    }
    if(id==2)
    {
    objectTexture=TextureManager::LoadImage("Assets/image/resultp2win.png");
    }
    if(id==3)
    {
     objectTexture=TextureManager::LoadImage("Assets/image/opening.png");
        xpos=0;
        ypos=0;
        srcR.w=600;
        srcR.h=600;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w*5/3;
        dstR.h=srcR.h*4/3;
    }
    if(id==4)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/resultdraw.png");
    }
    if(id==5)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/paused.png");
    }
    if(id==6)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p1hp1.png");
        xpos=80;
        ypos=40;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==7)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p1hp2.png");
        xpos=80;
        ypos=40;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==8)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p1hp3.png");
        xpos=80;
        ypos=40;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==9)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p2hp1.png");
        xpos=800;
        ypos=720;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==10)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p2hp2.png");
        xpos=800;
        ypos=720;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==11)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p2hp3.png");
        xpos=800;
        ypos=720;
        srcR.w=120;
        srcR.h=40;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==12)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/choosemap.png");
        xpos=0;
        ypos=0;
        srcR.w=1000;
        srcR.h=800;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==13)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p1instruct.png");
        xpos=100;
        ypos=150;
        srcR.w=200;
        srcR.h=500;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==14)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/p2instruct.png");
        xpos=700;
        ypos=150;
        srcR.w=200;
        srcR.h=500;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==15)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/instruct3.png");
        xpos=340;
        ypos=60;
        srcR.w=320;
        srcR.h=200;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    if(id==16)
    {
        objectTexture=TextureManager::LoadImage("Assets/image/instruct4.png");
        xpos=340;
        ypos=540;
        srcR.w=320;
        srcR.h=200;
        dstR.x=xpos;
        dstR.y=ypos;
        dstR.w=srcR.w;
        dstR.h=srcR.h;
    }
    SDL_RenderCopy(Game::renderer,objectTexture,&srcR,&dstR);
}
