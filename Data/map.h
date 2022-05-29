#include"Game.h"
#include"TextureManager.h"
#include <fstream>
#include <iostream>
class Map
{
public:
    Map(const char * mapdir);
    ~Map();
    void LoadMap(const char* mapdir);
    void DrawMap();
    int GetGameMap(int x,int y)
    {
        return gameMap[x][y];
    }
    void ChangeGameMap(int x,int y,int dirt)
    {
        gameMap[x][y]=dirt;
    }
private:
    SDL_Rect srcR,dstR;
    SDL_Texture * dirt=TextureManager::LoadImage("Assets/image/dirt.png");
    SDL_Texture * grass=TextureManager::LoadImage("Assets/image/grass.png");
    SDL_Texture * water=TextureManager::LoadImage("Assets/image/water.png");
    SDL_Texture * fence=TextureManager::LoadImage("Assets/image/fence.png");
    SDL_Texture * trench=TextureManager::LoadImage("Assets/image/trench.png");
    SDL_Texture * hole=TextureManager::LoadImage("Assets/image/hole.png");
    SDL_Texture * wall=TextureManager::LoadImage("Assets/image/wall.png");
    SDL_Texture * powerup1=TextureManager::LoadImage("Assets/image/powerup1.png");
    SDL_Texture * powerup2=TextureManager::LoadImage("Assets/image/powerup2.png");
    int gameMap[MAPROW][MAPCOL];
};

