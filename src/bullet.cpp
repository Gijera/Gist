#include "bullet.h"
#include "global.h"

Bullet::Bullet(bool t, int x, int y, int vx, int vy)
{
    dead = false;
    type = t;
    posX = x;
    posY = y;
    velX = vx;
    velY = vy;
    
    bulletRect.x = posX;
    bulletRect.y = posY;
    bulletRect.w = 5;
    bulletRect.h = 11;
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
    if(type)
        heroBulletTexture.render(posX, posY);
    else
        enemyBulletTexture.render(posX, posY);
}

bool Bullet::isDead()
{
    return dead;
}
