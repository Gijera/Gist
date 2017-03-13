#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <SDL2/SDL.h>
#include <vector>
#include "enum.h"
#include "hero.h"
#include "enemy.h"
#include "ufo.h"

class Scheduler{
public:
    Scheduler();

    ~Scheduler();
    
    void handleEvent(SDL_Event &e);

    void move();
    
    void render();

    Uint32 timer;
private:
    bool pause;
    SDL_Rect pauseButton;

    std::vector<Enemy *>enemys;
    Hero *hero = NULL;
    Ufo *ufo = NULL;
};
#endif
