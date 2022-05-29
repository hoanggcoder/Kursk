#include "map.h"
void Map::LoadMap(const char* mapdir)
{
    std::ifstream readmap(mapdir);
    if(!readmap) {std::cout<<"Khong the mo file map";}
    else
    {for(int row = 0; row < MAPROW; row++)
        {for(int column = 0; column < MAPCOL; column++)
            {readmap >> gameMap[row][column];
                if (!readmap) {
                std::cout << "Khong the doc noi dung file map"<< std::endl;
                return;}
            }
        }
    }
}
Map::Map(const char* mapdir)
{
    LoadMap(mapdir);
    srcR.x=0;
    srcR.y=0;
    srcR.w=BASIC_WIDTH;
    srcR.h=BASIC_HEIGHT;
    dstR.w=BASIC_WIDTH;
    dstR.h=BASIC_HEIGHT;
    dstR.x=0;
    dstR.y=0;
}

void Map::DrawMap()
{   int type;
    for(int row=0;row<MAPROW;row++)
        {for(int col=0;col<MAPCOL;col++)
    {
        type=gameMap[row][col];
        dstR.x=col*BASIC_WIDTH;
        dstR.y=row*BASIC_HEIGHT;
        switch(type)
        {
            case 0:
                TextureManager::Draw(dirt,srcR,dstR);
                break;
            case 1:
                TextureManager::Draw(grass,srcR,dstR);
                break;
            case 2:
                TextureManager::Draw(water,srcR,dstR);
                break;
            case 3:
                TextureManager::Draw(trench,srcR,dstR);
                break;
            case 4:
                TextureManager::Draw(fence,srcR,dstR);
                break;
            case 5:
                TextureManager::Draw(hole,srcR,dstR);
                break;
            case 6:
                TextureManager::Draw(wall,srcR,dstR);
                break;
            case 7:
                TextureManager::Draw(powerup1,srcR,dstR);
                break;
            case 8:
                TextureManager::Draw(powerup2,srcR,dstR);
                break;
            default:
                break;
        }
    }
        }
}
