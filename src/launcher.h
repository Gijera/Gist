#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

#include <SDL2/SDL.h>
#include <vector>
#include "bullet.h"

class Launcher{
public:
    Launcher();

    void setLauncher(enum bulletType type, int x, int y, int vx, int vy, int vel = 10);

    void move(int x, int y);

    void render();

    bool enable;

    std::vector<Bullet> bullets;
private:
    int timer = 0;
    int launcherVel;
    enum bulletType type;
    int posX, posY;
    int velX, velY;
};
#endif
