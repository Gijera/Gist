#include "ufo.h"
#include "global.h"

Ufo::Ufo()
{
    posX = rand() % (SCREEN_WIDTH - 58);
    posY = 0;
    velX = 0;
    velY = 5;
    
    type = (rand() % 2 == 0)? true : false;
    
    dead = false;
}

void Ufo::move()
{
    posX += velX;
    posY += velY;

    if(posX < 0 || posX + 58 > SCREEN_WIDTH)
        posX -= velX;
    if(posY < 0 || posY + 88 > SCREEN_HEIGHT)
        dead = true;
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
