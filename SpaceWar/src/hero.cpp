#include "hero.h"
#include "global.h"

Hero::Hero()
{
    dead = false;
    
    posX = (SCREEN_WIDTH - HEROWIDTH) / 2;
    posY = (SCREEN_HEIGHT - HEROHEIGHT) / 2;
    velX = 0;
    velY = 0;

    heroRect.x = posX;
    heroRect.y = posY;
    heroRect.w = HEROWIDTH;
    heroRect.h = HEROHEIGHT;

    heroBaseLauncher.setLauncher(HERO, posX + 25, posY, 0, -5);
    heroBombLauncher.setLauncher(BOMB, posX + 21, posY, 0, -5, 20);
    heroRightLauncher.setLauncher(HERO, posX + 40, posY + 22, 0, -5);
    heroLeftLauncher.setLauncher(HERO, posX + 7, posY + 22, 0, -5);
    heroBaseLauncher.enable = true;
    heroBombLauncher.enable = false;
    heroLeftLauncher.enable = false;
    heroRightLauncher.enable = false;
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
    if(posX < 0 || posX + HEROWIDTH > SCREEN_WIDTH){
        posX -= velX;
    }

    posY += velY;
    if(posY < 0 || posY + HEROHEIGHT > SCREEN_HEIGHT){
        posY -= velY;
    }
    
    heroRect.x = posX;
    heroRect.y = posY;
    
    heroBaseLauncher.move(posX + 25, posY);
    heroBombLauncher.move(posX + 21, posY);
    heroRightLauncher.move(posX + 40, posY + 22);
    heroLeftLauncher.move(posX + 7, posY + 22);
}

void Hero::render()
{
    heroTexture.render(posX, posY);
    heroBaseLauncher.render();
    heroBombLauncher.render();
    heroRightLauncher.render();
    heroLeftLauncher.render();
}

void Hero::collision(enum collisionType type)
{
    switch(type){
    case _UFO1:
        heroBaseLauncher.enable = false;
        heroBombLauncher.enable = false;
        heroLeftLauncher.enable = true;
        heroRightLauncher.enable = true;
        break;
    case _UFO2:
        heroBaseLauncher.enable = false;
        heroRightLauncher.enable = false;
        heroLeftLauncher.enable = false;
        heroBombLauncher.enable = true;
        break;
    case _ENEMY:
    case _ENEMYBULLET:
        dead = true;
        break;
    default:
        break;
    }
}
