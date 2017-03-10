#include "scheduler.h"
#include "global.h"

Scheduler::Scheduler()
{
    pauseButton.x = 420;
    pauseButton.y = 0;
    pauseButton.w = 60;
    pauseButton.h = 45;

    timer = 0;
    
    pause = false;
}

void Scheduler::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(isInRect(x, y, pauseButton)){
            pause = !pause;
        }
    }
}

void Scheduler::move()
{
    if(!pause)
        ++timer;
}

void Scheduler::render()
{
    mainTexture.render(0, 0);
    if(pause){
        resumeTexture.render(pauseButton.x, pauseButton.y);
    }else{
        pauseTexture.render(pauseButton.x, pauseButton.y);
    }
}
