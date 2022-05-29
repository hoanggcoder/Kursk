#include "TextureManager.h"
SDL_Texture* TextureManager::LoadImage(const char* file)
{
    SDL_Surface* tempoSur=IMG_Load(file);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(Game::renderer,tempoSur);
    SDL_FreeSurface(tempoSur);
    return texture;
}
void TextureManager::Draw(SDL_Texture* tex,SDL_Rect srcR,SDL_Rect dstR)
{
    SDL_RenderCopy(Game::renderer,tex,&srcR,&dstR);
}
