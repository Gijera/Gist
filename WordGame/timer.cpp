#include "timer.h"
#include "global.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::start()
{
    startTicks = SDL_GetTicks() - pausedTicks;
}

void Timer::pause()
{
    pausedTicks = SDL_GetTicks() - startTicks;
}

Uint32 Timer::getTicks()
{
    return startTicks/1000;
}
