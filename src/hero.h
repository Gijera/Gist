#ifndef _HERO_H_
#define _HERO_H_

#include <SDL2/SDL.h>
#include "launcher.h"

class Hero{
public:
    static const int heroVel = 5;
    
    Hero();

    void handleEvent(SDL_Event &e);

    void move();

    void render();
private:
    int posX, posY;
    int velX, velY;
    SDL_Rect heroRect;
    Launcher heroBaseLauncher;
    Launcher heroBombLauncher;
    Launcher heroLeftLauncher;
    Launcher heroRightLauncher;
};
#endif
