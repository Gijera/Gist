#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <SDL2/SDL.h>
#include "enum.h"
#include "hero.h"
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

    Hero *hero = NULL;
    Ufo *ufo = NULL;
};
#endif
