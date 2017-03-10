#include "scheduler.h"
#include "global.h"

Scheduler::Scheduler()
{
    timer = 0;
    
    pause = false;
    
    pauseButton.x = 420;
    pauseButton.y = 0;
    pauseButton.w = 60;
    pauseButton.h = 45;

    hero = new Hero();
}

Scheduler::~Scheduler()
{
    delete hero;
}

void Scheduler::handleEvent(SDL_Event &e)
{
    hero->handleEvent(e);
    
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
    if(!pause){
        ++timer;
        hero->move();
    }
}

void Scheduler::render()
{
    mainTexture.render(0, 0);
    if(pause){
        resumeTexture.render(pauseButton.x, pauseButton.y);
    }else{
        pauseTexture.render(pauseButton.x, pauseButton.y);
    }
            
    hero->render();
}
