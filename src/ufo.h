#ifndef _UFO_H_
#define _UFO_H_

class Ufo{
public:
    Ufo();

    void move();

    void render();

    bool isDead();
private:
    int posX, posY;
    int velX, velY;
    int type;
    bool dead;
};
#endif
