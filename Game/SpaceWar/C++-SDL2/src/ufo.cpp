#include "ufo.h"
#include "global.h"

Ufo::Ufo()
{
    posX = rand() % (SCREEN_WIDTH - UFOWIDTH);
    posY = 0;
    velX = 0;
    velY = 5;
    
    type = (rand() % 2 == 0)? true : false;
    
    dead = false;

    ufoRect.x = posX;
    ufoRect.y = posY;
    ufoRect.w = UFOWIDTH;
    ufoRect.h = UFOHEIGHT;
}

void Ufo::move()
{
    posX += velX;
    posY += velY;

    if(posX < 0 || posX + UFOWIDTH > SCREEN_WIDTH)
        posX -= velX;
    if(posY < 0 || posY + UFOHEIGHT > SCREEN_HEIGHT)
        dead = true;

    ufoRect.x = posX;
    ufoRect.y = posY;
}

void Ufo::render()
{
    if(type)
        ufo1Texture.render(posX, posY);
    else
        ufo2Texture.render(posX, posY);
}

bool Ufo::isDead()
{
    return dead;
}

void Ufo::collision()
{
    dead = true;
}
