#include "hero.h"
#include "global.h"

Hero::Hero()
{
    posX = (SCREEN_WIDTH - 106) / 2;
    posY = SCREEN_HEIGHT - 126;
    velX = 0;
    velY = 0;

    heroRect.x = posX;
    heroRect.y = posY;
    heroRect.w = 106;
    heroRect.h = 126;

    heroBaseLauncher.setLauncher(true, posX + 50, posY, 0, -5);
}

void Hero::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_UP:
            velY -= heroVel;
            break;
        case SDLK_DOWN:
            velY += heroVel;
            break;
        case SDLK_LEFT:
            velX -= heroVel;
            break;
        case SDLK_RIGHT:
            velX += heroVel;
            break;
        }
    }else if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
        case SDLK_UP:
            velY += heroVel;
            break;
        case SDLK_DOWN:
            velY -= heroVel;
            break;
        case SDLK_LEFT:
            velX += heroVel;
            break;
        case SDLK_RIGHT:
            velX -= heroVel;
            break;
        }
    }
}

void Hero::move()
{
    posX += velX;
    if(posX < 0 || posX + 102 > SCREEN_WIDTH)
        posX -= velX;
    
    posY += velY;
    if(posY < 0 || posY + 126 > SCREEN_HEIGHT)
        posY -= velY;

    heroRect.x = posX;
    heroRect.y = posY;
    heroBaseLauncher.move(posX + 50, posY);
}

void Hero::render()
{
    heroTexture.render(posX, posY);
    heroBaseLauncher.render();
}
