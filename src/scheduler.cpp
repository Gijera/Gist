#include "scheduler.h"
#include "collision.h"
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
    delete ufo;
    std::vector<Enemy *>tmp;
    tmp.swap(enemys);
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
        if(timer % 1000 == 0){
            if(ufo != NULL){
                ufo = new Ufo();
            }else{
                delete ufo;
                ufo = new Ufo();
            }
        }

        if(timer % 300 == 0){
            enemys.push_back(new Enemy(ENEMY_2, rand()%SCREEN_WIDTH, 0, 0, 1));
        }

        for(auto it = enemys.begin(); it != enemys.end();){
            if((*it)->dead){
                delete (*it);
                enemys.erase(it);
                continue;
            }
            (*it)->move();
            ++it;
        }
        
        if(ufo != NULL){
            ufo->move();
            if(ufo->isDead()){
                delete ufo;
                ufo = NULL;
            }
        }

        if(hero != NULL){
            hero->move();
            if(hero->dead){
                delete hero;
                hero = NULL;
            }
        }

        if(ufo != NULL && hero != NULL && OTORectCollision(hero->heroRect, ufo->ufoRect)){
                    ufo->collision();
                    if(ufo->type == true)
                        hero->collision(_UFO1);
                    else
                        hero->collision(_UFO2);
        }
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

    if(hero != NULL)
        hero->render();
    if(ufo != NULL)
        ufo->render();

    for(auto it = enemys.begin(); it != enemys.end(); ++it){
        (*it)->render();
    }
}
