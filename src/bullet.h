#ifndef _BULLET_H_
#define _BULLET_H_

#include <SDL2/SDL.h>
#include "enum.h"


class Bullet{
public:
    Bullet(enum bulletType type, int posx, int posy, int velx, int vely);
    
    void move();

    void render();

    bool isDead();

    void collision();
    
    SDL_Rect bulletRect;
private:
    bool dead;
    enum bulletType type;
    int posX, posY;
    int velX, velY;
};
#endif
