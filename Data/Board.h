#include "Game.h"
class Board
{
public:
    Board();
    ~Board();
    void update();
    void render(int id);

private:
    int xpos;
    int ypos;
    SDL_Texture* objectTexture;
    SDL_Rect srcR,dstR;
};
