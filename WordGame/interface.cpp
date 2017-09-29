#include "interface.h"
#include "global.h"

Interface::Interface()
{
    int xPox = (SCREEN_WIDTH - OPT_WIDTH)/2;
    int yPox = SCREEN_HEIGHT - OPTION * (OPT_HEIGHT + SPACE);
    for(int i = 0; i < OPTION; i++){
        option[i].x = xPox;
        option[i].y = yPox + i * (OPT_HEIGHT + SPACE);
        option[i].w = OPT_WIDTH;
        option[i].h = OPT_HEIGHT;
    }
}

void Interface::handleEvent(SDL_Event *e)
{
    int i;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x,y;
        SDL_GetMouseState(&x, &y);
        for(i = 0; i < OPTION; i++){
            if(isInRect(x, y, option[i]))
                break;
        }

        switch(i){
        case 0:
            windowState = BEGIN;
            break;
        case 1:
            windowState = EDIT;
            break;
        case 2:
            windowState = SETTING;
            break;
        case 3:
            windowState = EXIT;
            break;
        default:
            break;
        }
    }
}

void Interface::render()
{
    interfaceTexture.render(0, 0);
}

