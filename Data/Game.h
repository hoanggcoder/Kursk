#ifndef Game_h
#define Game_h
#include<SDL.h>
#include<SDL_image.h>
#include "StartStats.h"
#include<iostream>
#include<thread>
#include<chrono>
class Game
{
public:
Game();
~Game();
void init(const char *title,int xpos,int ypos,int width,int height,bool fullscreen);
void update();
void handleEvents();
void render();
void clean();
bool is_running() {return isRunning;}
static SDL_Renderer * renderer;
bool paused=0;
SDL_Renderer* Getrenderer(){return renderer;}
int p1lives=3;
int p2lives=3;
int timer;
private:
    bool isRunning=false;
    SDL_Window* window;
};
#endif // Game_h
