#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#define OPTION 4
#define OPT_WIDTH 180
#define OPT_HEIGHT 60
#define SPACE 20

class Interface
{
public:
    Interface();

    void handleEvent(SDL_Event *e);
    
    void render();
private:
    SDL_Rect option[OPTION];
};
#endif
