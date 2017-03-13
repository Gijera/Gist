#include "bullet.h"
#include "global.h"

Bullet::Bullet(enum bulletType t, int x, int y, int vx, int vy)
{
    dead = false;
    type = t;
    posX = x;
    posY = y;
    velX = vx;
    velY = vy;
    
    bulletRect.x = posX;
    bulletRect.y = posY;

    switch(type){
    case HERO:
        bulletRect.w = 5;
        bulletRect.h = 11;
        break;
    case ENEMY:
        bulletRect.w = 5;
        bulletRect.h = 11;
        break;
    case BOMB:
        bulletRect.w = 10;
        bulletRect.h = 25;
    }
}

void Bullet::move()
{
    posX += velX;
    posY += velY;

    if(posX < 0 || posX > SCREEN_WIDTH || posY < 0 || posY > SCREEN_HEIGHT)
        dead = true;

    bulletRect.x = posX;
    bulletRect.y = posY;
}

void Bullet::render()
{
    if(type == HERO)
        heroBulletTexture.render(posX, posY);
    else if(type == ENEMY)
        enemyBulletTexture.render(posX, posY);
    else
        bombBulletTexture.render(posX, posY);
}

bool Bullet::isDead()
{
    return dead;
}
