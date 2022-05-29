#include "Game.h"
#include "Shell.h"
class GameObject
{
public:
    GameObject(const char* filedir,int x,int y,int v=5);
    ~GameObject();
    void update();
    void render();
    void managecontrol()
        {
            player1controlled=1;
        }
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

private:
    int hp=10;
    int velocity;
    int angle=0;
    bool player1controlled=0;
    SDL_Texture* objectTexture;
    SDL_Rect srcR,dstR;
    bool firing=0;

};
