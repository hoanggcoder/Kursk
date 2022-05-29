#include "Game.h"
#include "TextureManager.h"
#include "Tank1object.h"
#include "Tank2object.h"
#include "map.h"
#include "Input.h"
#include "Board.h"
#include "Sound.h"
#include<cstdlib>
#include<ctime>
#include<thread>
#include<chrono>
#include<vector>
Tank1object* player1;
Tank2object* player2;
Map* themap;
Board* ResultBoard;
Board* guide;
Board* p1hp;
Board* p2hp;
Board* chooseMap;
Board* p1instruct;
Board* p2instruct;
Board* instruct3;
Board* instruct4;
SDL_Renderer* Game::renderer=nullptr;
Game::Game()
{}
Game::~Game()
{}
std::vector<int> waterx;
std::vector<int> watery;
std::vector<int> holex;
std::vector<int> holey;
std::vector<int> wallx;
std::vector<int> wally;
int powerup[2][2];
void waitUntilKeyPressed();
void waitUntilKeyPressed()
{
 SDL_Event e;
 while (true) {
 if ( SDL_WaitEvent(&e) != 0 &&
 (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
 return;
 SDL_Delay(100);
 }
}
void Game::init(const char*title,int xpos,int ypos,int width,int height,bool fullscreen)
{
    int flags=0;
    if(fullscreen)
    {
        flags=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout<<"Da khoi tao"<<std::endl;
        window=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
        if(window==nullptr)
        {
            SDL_Log(SDL_GetError());
            return ;
        }
        if(window)
        {
            std::cout<<"Da tao Window moi"<<std::endl;
        }
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if(renderer==nullptr)
        {
            SDL_Log(SDL_GetError());
            return;
        }
        if(renderer)
        {   SDL_SetRenderDrawColor(renderer,255,255,255,255);
            std::cout<<"Da tao Renderer moi"<<std::endl;
        }
        isRunning=true;

    }else {isRunning=false;}
    player1=new Tank1object();
    player2=new Tank2object();
    chooseMap=new Board();
    chooseMap->update();
    guide= new Board();
    guide->update();
    int play=0;
    SDL_RenderClear(renderer);
    guide->update();
    guide->render(3);
    SDL_RenderPresent(renderer);
    while(play==0)
    {waitUntilKeyPressed();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_O))
    {
        play=1;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        play=1;
        isRunning=false;
    }
    }
    if(isRunning!=false)
    {SDL_RenderClear(renderer);
    chooseMap->render(12);
    SDL_RenderPresent(renderer);
    while(themap==nullptr)
    {waitUntilKeyPressed();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_1))
    {themap= new Map("maps/map1.txt");
    Sound::Instance()->LoadMusic("Assets/sound/song.wav");
    Sound::Instance()->PlayMusic("Assets/sound/song.wav");
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_2))
    {themap= new Map("maps/map2.txt");
    Sound::Instance()->LoadMusic("Assets/sound/song3.wav");
    Sound::Instance()->PlayMusic("Assets/sound/song3.wav");
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_3))
    {themap= new Map("maps/map3.txt");
    Sound::Instance()->LoadMusic("Assets/sound/song3.wav");
    Sound::Instance()->PlayMusic("Assets/sound/song3.wav");}
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_4))
    {themap= new Map("maps/map4.txt");
    Sound::Instance()->LoadMusic("Assets/sound/song2.wav");
    Sound::Instance()->PlayMusic("Assets/sound/song2.wav");
    }
    }


    for(int i=1;i<MAPROW-1;i++)
    {
        for(int j=1;j<MAPCOL-1;j++)
        {if(themap->GetGameMap(i,j)==2)
            {
                waterx.push_back(j*BASIC_WIDTH);
                watery.push_back(i*BASIC_HEIGHT);
            }
         if(themap->GetGameMap(i,j)==5)
         {
             holex.push_back(j*BASIC_WIDTH);
             holey.push_back(i*BASIC_HEIGHT);
         }
         if(themap->GetGameMap(i,j)==6)
         {
             wallx.push_back(j*BASIC_WIDTH);
             wally.push_back(i*BASIC_HEIGHT);
         }
         if(themap->GetGameMap(i,j)==7)
         {
             powerup[0][0]=i;
             powerup[0][1]=j;
         }
         if(themap->GetGameMap(i,j)==8)
         {
             powerup[1][0]=i;
             powerup[1][1]=j;
         }
        }
    }
    ResultBoard=new Board();
    ResultBoard->update();
    p1instruct=new Board();
    p1instruct->update();
    p2instruct=new Board();
    p2instruct->update();
    instruct3=new Board();
    instruct3->update();
    instruct4=new Board();
    instruct4->update();
    p1hp= new Board();
    p1hp->update();
    p2hp=new Board();
    p2hp->update();
    }

}
bool OneTankBoomed()
{
    if(player1->getHP()<=0||player2->getHP()<=0)
        return true;
    return false;
}
bool BothStuck()
{
    if(player1->getVelocity()==0&&player2->getVelocity()==0)
    {
        return true;
    }
    return false;
}
void handleCollide();
void handlewaterP1(int x,int y);
void handleHoleP1(int x,int y);
void handleHoleP2(int x,int y);
void handlewaterP2(int x,int y);
void handleWallP1(int x,int y);
void handleWallP2(int x,int y);
void handleWallShell1(int x,int y);
void handleWallShell2(int x,int y);
bool p1hitp2()
{
    return((player1->tankshell.xpos-player2->xpos)<=ERRORMARGIN&&(player1->tankshell.ypos-player2->ypos)<=ERRORMARGIN&&(player1->tankshell.xpos-player2->xpos)>=-ERRORMARGIN&&(player1->tankshell.ypos-player2->ypos)>=-ERRORMARGIN);
}
bool p2hitp1()
{
    return((player2->tankshell.xpos-player1->xpos)<=ERRORMARGIN&&(player2->tankshell.ypos-player1->ypos)<=ERRORMARGIN&&(player2->tankshell.xpos-player1->xpos)>=-ERRORMARGIN&&(player2->tankshell.ypos-player1->ypos)>=-ERRORMARGIN);
}
void Game::update()
{   if(paused==false)
{
    timer++;
    handleCollide();
    for(int k=0;k<waterx.size();k++)
    {
        handlewaterP1(waterx[k],watery[k]);
    }
    for(int k=0;k<waterx.size();k++)
    {
        handlewaterP2(waterx[k],watery[k]);
    }
    for(int k=0;k<holex.size();k++)
    {
        handleHoleP1(holex[k],holey[k]);
    }
    for(int k=0;k<holex.size();k++)
    {
        handleHoleP2(holex[k],holey[k]);
    }
    for(int k=0;k<wallx.size();k++)
    {
        handleWallP1(wallx[k],wally[k]);
    }
    for(int k=0;k<wallx.size();k++)
    {
        handleWallP2(wallx[k],wally[k]);
    }
    for(int k=0;k<wallx.size();k++)
    {
        handleWallShell1(wallx[k],wally[k]);
    }
    for(int k=0;k<wallx.size();k++)
    {
        handleWallShell2(wallx[k],wally[k]);
    }
    if(player1->xpos-powerup[0][1]*BASIC_WIDTH<=20&player1->xpos-powerup[0][1]*BASIC_WIDTH>=-20&&player1->ypos-powerup[0][0]*BASIC_HEIGHT<=20&&player1->ypos-powerup[0][0]*BASIC_HEIGHT>=-20)
    {   if(themap->GetGameMap(powerup[0][0],powerup[0][1])!=0)
        {themap->ChangeGameMap(powerup[0][0],powerup[0][1],0);
        player1->setVelocity(5);
        Sound::Instance()->LoadEffect("Assets/sound/eat.wav");
        Sound::Instance()->PlayEffect("Assets/sound/eat.wav");
        }
    }
    if(player2->xpos-powerup[0][1]*BASIC_WIDTH<=20&player2->xpos-powerup[0][1]*BASIC_WIDTH>=-20&&player2->ypos-powerup[0][0]*BASIC_HEIGHT<=20&&player2->ypos-powerup[0][0]*BASIC_HEIGHT>=-20)
    {   if(themap->GetGameMap(powerup[0][0],powerup[0][1])!=0)
        {themap->ChangeGameMap(powerup[0][0],powerup[0][1],0);
        player2->setVelocity(5);
        Sound::Instance()->LoadEffect("Assets/sound/eat.wav");
        Sound::Instance()->PlayEffect("Assets/sound/eat.wav");
        }
    }
    if(player2->xpos-powerup[1][1]*BASIC_WIDTH<=20&player2->xpos-powerup[1][1]*BASIC_WIDTH>=-20&&player2->ypos-powerup[1][0]*BASIC_HEIGHT<=20&&player2->ypos-powerup[1][0]*BASIC_HEIGHT>=-20)
    {   if(themap->GetGameMap(powerup[1][0],powerup[1][1])!=0)
        {Sound::Instance()->LoadEffect("Assets/sound/eat.wav");
        Sound::Instance()->PlayEffect("Assets/sound/eat.wav");
        themap->ChangeGameMap(powerup[1][0],powerup[1][1],0);
        player2->NewShell=1;}
    }
    if(player1->xpos-powerup[1][1]*BASIC_WIDTH<=20&player1->xpos-powerup[1][1]*BASIC_WIDTH>=-20&&player1->ypos-powerup[1][0]*BASIC_HEIGHT<=20&&player1->ypos-powerup[1][0]*BASIC_HEIGHT>=-20)
    {   if(themap->GetGameMap(powerup[1][0],powerup[1][1])!=0)
        {themap->ChangeGameMap(powerup[1][0],powerup[1][1],0);
        player1->NewShell=1;
        Sound::Instance()->LoadEffect("Assets/sound/eat.wav");
        Sound::Instance()->PlayEffect("Assets/sound/eat.wav");}
    }
    player1->update();
    player2->update();
    player2->tankshell.update();
    player1->tankshell.update();
    if(p1hitp2())
    {
        player2->lowerHP(player1->tankshell.damage);
        player1->tankshell.xpos=SHELL_OUT;
        player1->tankshell.ypos=SHELL_OUT;
        if(player1->typeofshell==1)
        {
            Sound::Instance()->LoadEffect("Assets/sound/cannonhit.wav");
            Sound::Instance()->PlayEffect("Assets/sound/cannonhit.wav");
        }
        else
        {Sound::Instance()->LoadEffect("Assets/sound/beamhit.wav");
        Sound::Instance()->PlayEffect("Assets/sound/beamhit.wav");
        }
    }
    if(p2hitp1())
    {
        player1->lowerHP(player2->tankshell.damage);
        player2->tankshell.xpos=SHELL_OUT;
        player2->tankshell.ypos=SHELL_OUT;
        if(player2->typeofshell==1)
        {
            Sound::Instance()->LoadEffect("Assets/sound/cannonhit.wav");
            Sound::Instance()->PlayEffect("Assets/sound/cannonhit.wav");
        }
        else
        {Sound::Instance()->LoadEffect("Assets/sound/beamhit.wav");
        Sound::Instance()->PlayEffect("Assets/sound/beamhit.wav");
        }
    }
    if(OneTankBoomed())
    {
        player1->BoomedAnimation(player2->typeofshell);
        player2->BoomedAnimation(player1->typeofshell);
        SDL_RenderClear(renderer);
        themap->DrawMap();
        player1->render();
        player2->render();
        if(player1->getHP()<=0)
        {   player1=new Tank1object();
            p1lives--;
            if(player2->typeofshell==1)
            {
                Sound::Instance()->LoadEffect("Assets/sound/cannonboom.wav");
                Sound::Instance()->PlayEffect("Assets/sound/cannonboom.wav");
            }
            else
            {
                Sound::Instance()->LoadEffect("Assets/sound/beamboom.wav");
                Sound::Instance()->PlayEffect("Assets/sound/beamboom.wav");
            }
            }
        if(player2->getHP()<=0)
        {   player2=new Tank2object();
            p2lives--;
            if(player1->typeofshell==1)
            {
                Sound::Instance()->LoadEffect("Assets/sound/cannonboom.wav");
                Sound::Instance()->PlayEffect("Assets/sound/cannonboom.wav");
            }
            else
            {
                Sound::Instance()->LoadEffect("Assets/sound/beamboom.wav");
                Sound::Instance()->PlayEffect("Assets/sound/beamboom.wav");
            }
            ;}
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        if(p1lives==0)
        {   SDL_RenderClear(renderer);
            themap->DrawMap();
            player1->render();
            player2->render();
            ResultBoard->render(2);
            SDL_RenderPresent(renderer);
            Mix_PauseMusic();
            Sound::Instance()->LoadEffect("Assets/sound/win.wav");
            Sound::Instance()->PlayEffect("Assets/sound/win.wav");
            SDL_Delay(4000);
            isRunning=0;}
        if(p2lives==0)
        {   SDL_RenderClear(renderer);
            themap->DrawMap();
            player1->render();
            player2->render();
            ResultBoard->render(1);
            SDL_RenderPresent(renderer);
            Mix_PauseMusic();
            Sound::Instance()->LoadEffect("Assets/sound/win.wav");
            Sound::Instance()->PlayEffect("Assets/sound/win.wav");
            SDL_Delay(4000);
            isRunning=0;}
    }
    if(BothStuck())
    {
        SDL_RenderClear(renderer);
        themap->DrawMap();
        player1->render();
        player2->render();
        ResultBoard->render(4);
        SDL_RenderPresent(renderer);
        SDL_Delay(4000);
        isRunning=0;
    }
}
else
{
    SDL_RenderClear(renderer);
    themap->DrawMap();
    player1->render();
    player2->render();
    ResultBoard->render(5);
    p1instruct->render(13);
    p2instruct->render(14);
    instruct3->render(15);
    instruct4->render(16);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
}
}
void Game::render()
{
    SDL_RenderClear(renderer);
    themap->DrawMap();
    p1hp->render(p1lives+5);
    p2hp->render(p2lives+8);
    player1->render();
    player2->render();
    player1->tankshell.render();
    player2->tankshell.render();
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    std::cout<<"Da thoat game"<<std::endl;
}
void Game::handleEvents()
{
    isRunning=(Input::GetInstance()->Listen());
}
void handleCollide()
{
     while(player1->xpos-player2->xpos<=C_ERRORMARGIN&&player1->xpos-player2->xpos>=-C_ERRORMARGIN&&player1->ypos-player2->ypos<=C_ERRORMARGIN&&player1->ypos-player2->ypos>=-C_ERRORMARGIN)
    {   if(player1->xpos<=player2->xpos&&player1->ypos<=player2->ypos)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        if(player2->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player2->ypos++;
        }
        else if(player1->xpos>=player2->xpos&&player1->ypos>=player2->ypos)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player1->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player1->ypos++;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else if(player1->xpos<=player2->xpos&&player1->ypos>=player2->ypos)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->ypos++;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else if(player1->xpos>=player2->xpos&&player1->ypos<=player2->ypos)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        if(player2->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player2->ypos++;
        }
        else break;
    }
}
void handlewaterP1(int x,int y)
{
     while(player1->xpos-x<=C_ERRORMARGIN&&player1->xpos-x>=-C_ERRORMARGIN&&player1->ypos-y<=C_ERRORMARGIN&&player1->ypos-y>=-C_ERRORMARGIN)
    {
        if(player1->xpos<=x&&player1->ypos<=y)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        }
        else if(player1->xpos>=x&&player1->ypos>=y)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player1->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player1->ypos++;
        }
        else if(player1->xpos<=x&&player1->ypos>=y)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->ypos++;
        }
        else if(player1->xpos>=x&&player1->ypos<=y)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        }
        else break;
    }
}
void handleWallP1(int x,int y)
{
     while(player1->xpos-x<=C_ERRORMARGIN&&player1->xpos-x>=-C_ERRORMARGIN&&player1->ypos-y<=C_ERRORMARGIN&&player1->ypos-y>=-C_ERRORMARGIN)
    {
        if(player1->xpos<=x&&player1->ypos<=y)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        }
        else if(player1->xpos>=x&&player1->ypos>=y)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player1->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player1->ypos++;
        }
        else if(player1->xpos<=x&&player1->ypos>=y)
        {
        if(player1->xpos>BASIC_WIDTH) player1->xpos--;
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->ypos++;
        }
        else if(player1->xpos>=x&&player1->ypos<=y)
        {
        if(player1->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player1->xpos++;
        if(player1->ypos>BASIC_HEIGHT) player1->ypos--;
        }
        else break;
    }
}
void handleWallShell1(int x,int y)
{
    if(player1->tankshell.xpos-x<=ERRORMARGIN&player1->tankshell.xpos-x>=-ERRORMARGIN&&player1->tankshell.ypos-y<=ERRORMARGIN&&player1->tankshell.ypos-y>=-ERRORMARGIN)
    {
        player1->tankshell.xpos=2000;
        player1->tankshell.ypos=2000;
    }
}
void handlewaterP2(int x,int y)
{
     while(player2->xpos-x<=C_ERRORMARGIN&&player2->xpos-x>=-C_ERRORMARGIN&&player2->ypos-y<=C_ERRORMARGIN&&player2->ypos-y>=-C_ERRORMARGIN)
    {   if(player2->xpos<=x&&player2->ypos<=y)
        {
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else if(player2->xpos>=x&&player2->ypos>=y)
        {
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player2->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player2->ypos++;
        }
        else if(player2->xpos<=x&&player2->ypos>=y)
        {
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->ypos++;
        }
        else if(player2->xpos>=x&&player2->ypos<=y)
        {
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else break;
    }
}
void handleWallP2(int x,int y)
{
     while(player2->xpos-x<=C_ERRORMARGIN&&player2->xpos-x>=-C_ERRORMARGIN&&player2->ypos-y<=C_ERRORMARGIN&&player2->ypos-y>=-C_ERRORMARGIN)
    {   if(player2->xpos<=x&&player2->ypos<=y)
        {
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else if(player2->xpos>=x&&player2->ypos>=y)
        {
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player2->ypos<SCREEN_HEIGHT-BASIC_HEIGHT*2) player2->ypos++;
        }
        else if(player2->xpos<=x&&player2->ypos>=y)
        {
        if(player2->xpos>BASIC_WIDTH) player2->xpos--;
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->ypos++;
        }
        else if(player2->xpos>=x&&player2->ypos<=y)
        {
        if(player2->xpos<SCREEN_WIDTH-BASIC_WIDTH*2) player2->xpos++;
        if(player2->ypos>BASIC_HEIGHT) player2->ypos--;
        }
        else break;
    }
}
void handleWallShell2(int x,int y)
{
    if(player2->tankshell.xpos-x<=ERRORMARGIN&player2->tankshell.xpos-x>=-ERRORMARGIN&&player2->tankshell.ypos-y<=ERRORMARGIN&&player2->tankshell.ypos-y>=-ERRORMARGIN)
    {
        player2->tankshell.xpos=SHELL_OUT;
        player2->tankshell.ypos=SHELL_OUT;
    }
}
void handleHoleP1(int x,int y)
{
    if(player1->xpos-x<=10&player1->xpos-x>=-10&&player1->ypos-y<=10&&player1->ypos-y>=-10)
    {
        player1->setVelocity(0);
    }
}
void handleHoleP2(int x,int y)
{
    if(player2->xpos-x<=10&player2->xpos-x>=-10&&player2->ypos-y<=10&&player2->ypos-y>=-10)
    {
        player2->setVelocity(0);
    }
}

