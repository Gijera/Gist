#ifndef _HERO_H_
#define _HERO_H_

#include <SDL2/SDL.h>
#include "launcher.h"
#include "enum.h"

#define HEROWIDTH 51
#define HEROHEIGHT 63

class Hero{
public:
    static const int heroVel = 5;
    
    Hero();

    void handleEvent(SDL_Event &e);

    void move();

    void render();

    void collision(enum collisionType type);

    bool dead;
    SDL_Rect heroRect;
    int posX, posY;
    int velX, velY;
    Launcher heroBaseLauncher;
    Launcher heroBombLauncher;
    Launcher heroLeftLauncher;
    Launcher heroRightLauncher;
};
#endif
