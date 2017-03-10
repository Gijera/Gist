#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

#include <SDL2/SDL.h>
#include <vector>
#include "bullet.h"

class Launcher{
public:
    static const int launcherVel = 10;

    Launcher();
    
    void setLauncher(bool type, int x, int y, int vx, int vy);

    void move(int x, int y);

    void render();
private:
    bool type;
    std::vector<Bullet> bullets;
    int posX, posY;
    int velX, velY;
};
#endif
