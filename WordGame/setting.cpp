#include "setting.h"
#include "global.h"

Setting::Setting()
{
    set[0].x = 50;
    set[0].y = 30;
    set[0].w = 60;
    set[0].h = 40;

    for(int i = 1; i < SET; i++){
        set[i].w = 60;
        set[i].h = 40;
    }
    
    set[1].x = 300;
    set[1].y = 180;
    
    set[2].x = 360;
    set[2].y = 180;

    set[3].x = 300;
    set[3].y = 250;

    set[4].x = 360;
    set[4].y = 250;

    musicSetRect.x = 360;
    musicSetRect.y = 180;
    musicSetRect.w = 60;
    musicSetRect.h = 40;
    
    soundSetRect.x = 360;
    soundSetRect.y = 250;
    soundSetRect.w = 60;
    soundSetRect.h = 60;
}

void Setting::handleEvent(SDL_Event *e)
{
    int i;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(i = 0; i < SET; i++){
            if(isInRect(x, y, set[i]))
                break;
        }

        switch(i){
        case 0:
            windowState = INTERFACE;
            break;
        case 1:
            if(Mix_PlayingMusic()){
                musicSetRect.x = 300;
                Mix_PauseMusic();
            }
            break;
        case 2:
            if(Mix_PausedMusic()){
                musicSetRect.x = 360;
                Mix_ResumeMusic();
            }
            break;
        case 3:
            if(soundOn == 1){
                soundSetRect.x = 300;
                soundOn = 0;
            }
            break;
        case 4:
            if(soundOn == 0){
                soundSetRect.x = 360;
                soundOn = 1;
            }
            break;
        default:
            break;
        }
    }
}

void Setting::render()
{
    settingTexture.render(0, 0);
    settingButtonTexture.render(musicSetRect.x, musicSetRect.y);
    settingButtonTexture.render(soundSetRect.x, soundSetRect.y);
}
