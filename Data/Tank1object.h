#include "Game.h"
#include "Shell.h"
class Tank1object
{
public:
    Tank1object();
    ~Tank1object();
    void update();
    void render();
    void SetAngle(int _angle)
        {
            angle=_angle;
        }
    Shell tankshell;
    int xpos;
    int ypos;
    int typeofshell=1;
    void lowerHP(int damage)
    {
        hp=hp-damage;
    }
    int getHP()
    {
        return hp;
    }
    void BoomedAnimation(int enemyshell)
    {
        if(hp<=0)
        {   if(enemyshell==1)
            {objectTexture=TextureManager::LoadImage("Assets/image/explosion2.png");}
            else
            {objectTexture=TextureManager::LoadImage("Assets/image/explosion3.png");}
        }
    }
    void setVelocity(int newvelo)
    {
        velocity=newvelo;
    }
    int getVelocity()
    {
        return velocity;
    }
    bool NewShell=0;
private:
    int hp=10;
    int velocity;
    int angle=0;
    SDL_Texture* objectTexture;
    SDL_Rect srcR,dstR;
    bool firing=0;

};

