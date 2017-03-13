#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL2/SDL.h>
#include "enum.h"
#include "launcher.h"

class Enemy{
public:
    Enemy();

    Enemy(enum enemyType t, int x, int y, int vx, int vy);
    
    void setEnemy(enum enemyType t, int x, int y, int vx, int vy);

    void move();

    void render();
    
    enum enemyType type;
    bool dead;
    int life;
    int posX, posY;
    int velX, velY;
    SDL_Rect enemyRect;
    Launcher enemyLauncher;
};
#endif
