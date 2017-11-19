#ifndef _SETTING_H_
#define _SETTING_H_

#include <SDL2/SDL.h>

#define SET 5

class Setting{
public:
    Setting();

    void handleEvent(SDL_Event *e);

    void render();
private:
    SDL_Rect set[SET];
    SDL_Rect musicSetRect;
    SDL_Rect soundSetRect;
};
#endif
