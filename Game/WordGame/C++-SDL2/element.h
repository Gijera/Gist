#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <vector>
#include <SDL2/SDL.h>

#define MAXALPHA 9

class Element{
public:
    Element();
    
    void setId(int id);

    void sendAlpha();

    void handleEvent(SDL_Event *e);

    void deleteAlpha(int i);
    
    void render();

    SDL_Rect vecButton[MAXALPHA];
    std::vector<int> vecAlpha;
    std::vector<bool> vecSelect;
    int vecId;
};
#endif
