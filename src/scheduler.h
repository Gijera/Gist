#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include <SDL2/SDL.h>
#include <vector>
#include "enum.h"
#include "hero.h"
#include "enemy.h"
#include "ufo.h"

static SDL_Color textColor = {0x00, 0x00, 0x00};

class Scheduler{
public:
    Scheduler();

    ~Scheduler();
    
    void handleEvent(SDL_Event &e);

    void move();
    
    void render();

    void heroEnemyCollision();

    void heroUfoCollision();

    void heroBulletCollision();

    void enemyBulletCollision();
    
    Uint32 timer;

    int score;
private:
    bool start;
    bool pause;
    SDL_Rect pauseButton;
    SDL_Rect restartButton;
    std::vector<Enemy *>enemys;
    Hero *hero = NULL;
    Ufo *ufo = NULL;
};
#endif
