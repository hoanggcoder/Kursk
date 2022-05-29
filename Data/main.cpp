#include "Game.h"
#include"Input.h"
#include "StartStats.h"
Game *game=nullptr;
Uint32 StartTime;
int NeededFrameTime;
const int DesiredFrameTime=1000/FPS;
void waitUntilKeyPressed();
int main(int argv, char** args)
    {
        game=new Game();
        game->init(GAME_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,FULLSCREEN);
        while(game->is_running())
        {
            StartTime=SDL_GetTicks();
            game->handleEvents();
            game->update();
            if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_P))
            {
                game->paused=true;
            }
            if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_O))
            {
                game->paused=false;
            }
            NeededFrameTime=SDL_GetTicks()-StartTime;
            if(DesiredFrameTime>NeededFrameTime)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DesiredFrameTime-NeededFrameTime));
            }
            game->render();
        }
        game->clean();

        return 0;
    }
