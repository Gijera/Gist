#ifndef _BULLET_H_
#define _BULLET_H_

#include <SDL2/SDL.h>

class Bullet{
public:
    Bullet(bool type, int posx, int posy, int velx, int vely);

    void move();

    void render();

    bool isDead();
private:
    bool dead;
    int type;
    int posX, posY;
    int velX, velY;
    SDL_Rect bulletRect;
};
#endif
