#ifndef _BULLET_H_
#define _BULLET_H_

#include <SDL2/SDL.h>

enum bulletType{HERO, ENEMY, BOMB};

class Bullet{
public:
    Bullet(enum bulletType type, int posx, int posy, int velx, int vely);
    
    void move();

    void render();

    bool isDead();
private:
    bool dead;
    enum bulletType type;
    int posX, posY;
    int velX, velY;
    SDL_Rect bulletRect;
};
#endif
