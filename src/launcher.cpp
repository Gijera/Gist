#include "launcher.h"
#include "global.h"

Launcher::Launcher()
{
    
}

void Launcher::setLauncher(bool t, int x, int y, int vx, int vy)
{
    type = t;
    posX = x;
    posY = y;
    velX = vx;
    velY = vy;
}

void Launcher::move(int x, int y)
{
    static int timer = 0;
    posX = x;
    posY = y;
    if(++timer == launcherVel){
        bullets.push_back(Bullet(type, posX, posY, velX, velY));
        timer = 0;
    }

    for(auto it = bullets.begin(); it != bullets.end(); ){
        if(it->isDead()){
            bullets.erase(it);
            continue;
        }
        it->move();
        ++it;
    }
}

void Launcher::render()
{
    for(auto it =  bullets.begin(); it != bullets.end(); ++it)
        it->render();
}
