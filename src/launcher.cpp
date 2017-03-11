#include "launcher.h"
#include "global.h"

Launcher::Launcher()
{
    enable = true;
}

void Launcher::setLauncher(enum bulletType t, int x, int y, int vx, int vy, int vel)
{
    type = t;
    posX = x;
    posY = y;
    velX = vx;
    velY = vy;
    launcherVel = vel;
}

void Launcher::move(int x, int y)
{
        posX = x;
        posY = y;
        if(enable){
            if(++timer == launcherVel){
                bullets.push_back(Bullet(type, posX, posY, velX, velY));
                timer = 0;
            }
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
