#ifndef _HERO_H_
#define _HERO_H_

#include <SDL2/SDL.h>
#include "launcher.h"
#include "enum.h"

#define HEROWIDTH 106
#define HEROHEIGHT 126

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
private:
    int posX, posY;
    int velX, velY;
    Launcher heroBaseLauncher;
    Launcher heroBombLauncher;
    Launcher heroLeftLauncher;
    Launcher heroRightLauncher;
};
#endif
