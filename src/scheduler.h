#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <SDL2/SDL.h>

class Scheduler{
public:
    Scheduler();

    void handleEvent(SDL_Event &e);

    void move();
    
    void render();
private:
    SDL_Rect pauseButton;
    Uint32 timer;
    bool pause;
};
#endif
