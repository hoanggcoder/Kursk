#ifndef TextureManager_h
#define TextureManager_h
#include "Game.h"
class TextureManager
{
public:
    static SDL_Texture* LoadImage(const char* file);
    static void Draw(SDL_Texture* tex,SDL_Rect srcR,SDL_Rect dstR);
};
#endif // TextureManager_h
