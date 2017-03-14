#include "scheduler.h"
#include "collision.h"
#include "global.h"

Scheduler::Scheduler()
{
    timer = 0;

    score = 0;

    quit = false;
    dead = false;
    start = false;
    pause = false;
    
    pauseButton.x = 420;
    pauseButton.y = 0;
    pauseButton.w = 60;
    pauseButton.h = 45;

    restartButton.x = 90;
    restartButton.y = 400;
    restartButton.w = 300;
    restartButton.h = 41;

    quitButton.x = 90;
    quitButton.y = 500;
    quitButton.w = 300;
    quitButton.h = 41;
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
    if(hero != NULL)
        hero->handleEvent(e);
    
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(isInRect(x, y, pauseButton)){
            pause = !pause;
        }

        if(start && isInRect(x, y, restartButton)){
            dead = true;
        }

        if(start && isInRect(x, y, quitButton)){
            quit = true;
        }
    }
}

void Scheduler::move()
{
    static int timerTmp = 300;
    
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

        if(timer % timerTmp == 0){
            int tmp;
            tmp = rand() % 300;
            if(tmp >= 150)
                timerTmp = tmp;
            
            tmp = rand() % 9;
            if(tmp >= 0 && tmp <= 4)
                enemys.push_back(new Enemy(ENEMY_1, rand()%SCREEN_WIDTH, 0, 0, 1));
            else if(tmp >= 5 && tmp <= 7)
                enemys.push_back(new Enemy(ENEMY_2, rand()%SCREEN_WIDTH, 0, 0, 1));
            else
                enemys.push_back(new Enemy(ENEMY_3, rand()%SCREEN_WIDTH, 0, 0, 1));
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
            if(ufo->isDead()){
                delete ufo;
                ufo = NULL;
            }else{
                ufo->move();
            }
        }
        
        if(hero != NULL){
            if(hero->dead){
                delete hero;
                hero = NULL;
                start = true;
            }else{
                hero->move();
            }
        }
        
        heroEnemyCollision();
        heroUfoCollision();
        heroBulletCollision();
        enemyBulletCollision();
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

    char tmp[8];
    sprintf(tmp, "%d", score);
    std::string text = "score:";
    text += tmp;
    scoreTexture.loadFromRenderedText(text, textColor);
    scoreTexture.render(10, 0);

    
    if(start){
        restartTexture.render(restartButton.x, restartButton.y);
        quitTexture.render(quitButton.x, quitButton.y);
    }
}

void Scheduler::heroUfoCollision()
{
    if(ufo != NULL && hero != NULL && OTORectCollision(hero->heroRect, ufo->ufoRect)){
        ufo->collision();
        if(ufo->type == true)
            hero->collision(_UFO1);
        else
            hero->collision(_UFO2);
        Mix_PlayChannel(-1, getUfo, 0);
    }
}

void Scheduler::heroEnemyCollision()
{
    if(hero != NULL){
        for(auto it = enemys.begin(); it != enemys.end(); ++it){
            if(OTORectCollision(hero->heroRect, (*it)->enemyRect)){
                hero->collision(_ENEMY);
                (*it)->collision(_HERO);
                break;
            }
        }
    }
}

void Scheduler::heroBulletCollision()
{
    if(hero != NULL){
        for(auto it = enemys.begin(); it != enemys.end(); ++it){
            for(auto tmp = (*it)->enemyLauncher.bullets.begin(); tmp != (*it)->enemyLauncher.bullets.end(); ++tmp){
                if(OTORectCollision(hero->heroRect, tmp->bulletRect)){
                    hero->collision(_ENEMYBULLET);
                    tmp->collision();
                }
            }
        }
    }
}

void Scheduler::enemyBulletCollision()
{
    if(hero != NULL){
        if(hero->heroBaseLauncher.enable){
            for(auto it = enemys.begin(); it != enemys.end(); ++it){
                for(auto tmp = hero->heroBaseLauncher.bullets.begin(); tmp != hero->heroBaseLauncher.bullets.end(); ++tmp){
                    if(OTORectCollision((*it)->enemyRect, tmp->bulletRect)){
                        tmp->collision();
                        (*it)->collision(_HEROBULLET);
                        score++;
                        Mix_PlayChannel(-1, heroBullet, 0);
                    }
                }
            }
        }

        if(hero->heroBombLauncher.enable){
            for(auto it = enemys.begin(); it != enemys.end(); ++it){
                for(auto tmp = hero->heroBombLauncher.bullets.begin(); tmp != hero->heroBombLauncher.bullets.end(); ++tmp){
                    if(OTORectCollision((*it)->enemyRect, tmp->bulletRect)){
                        tmp->collision();
                        (*it)->collision(_BOMBBULLET);
                        score += 10;
                        Mix_PlayChannel(-1, bombBullet, 0);
                    }
                }
            }
        }

        if(hero->heroLeftLauncher.enable){
            for(auto it = enemys.begin(); it != enemys.end(); ++it){
                for(auto tmp = hero->heroLeftLauncher.bullets.begin(); tmp != hero->heroLeftLauncher.bullets.end(); ++tmp){
                    if(OTORectCollision((*it)->enemyRect, tmp->bulletRect)){
                        tmp->collision();
                        (*it)->collision(_HEROBULLET);
                        score++;
                        Mix_PlayChannel(-1, heroBullet, 0);
                    }
                }
            }
        }

        if(hero->heroRightLauncher.enable){
            for(auto it = enemys.begin(); it != enemys.end(); ++it){
                for(auto tmp = hero->heroRightLauncher.bullets.begin(); tmp != hero->heroRightLauncher.bullets.end(); ++tmp){
                    if(OTORectCollision((*it)->enemyRect, tmp->bulletRect)){
                        tmp->collision();
                        (*it)->collision(_HEROBULLET);
                        score++;
                        Mix_PlayChannel(-1, heroBullet, 0);
                    }
                }
            }
        }
    }
}
