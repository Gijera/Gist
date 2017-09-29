#ifndef _UFO_H_
#define _UFO_H_

#include <SDL2/SDL.h>

#define UFOWIDTH 30
#define UFOHEIGHT 45

class Ufo{
public:
    Ufo();

    void move();

    void render();

    bool isDead();

    void collision();

    int type;
    SDL_Rect ufoRect;
private:
    int posX, posY;
    int velX, velY;
    bool dead;
};
#endif
