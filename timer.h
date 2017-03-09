#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL2/SDL.h>

class Timer{
public:
    Timer();
    void pause();
    void start();
    Uint32 getTicks();
private:
    Uint32 startTicks;
    Uint32 pausedTicks;
};
#endif
