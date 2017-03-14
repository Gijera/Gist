#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "texture.h"
#include "scheduler.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *font;

extern Mix_Music *music;
extern Mix_Chunk *heroBullet;
extern Mix_Chunk *bombBullet;
extern Mix_Chunk *enemyDead;
extern Mix_Chunk *getUfo;

extern Scheduler *scheduler;

extern Texture mainTexture;

extern Texture heroTexture;

extern Texture enemy1Texture;

extern Texture enemy2Texture;

extern Texture enemy3Texture;

extern Texture heroBulletTexture;
extern Texture enemyBulletTexture;
extern Texture bombBulletTexture;
extern Texture ufo1Texture;
extern Texture ufo2Texture;
extern Texture pauseTexture;
extern Texture resumeTexture;
extern Texture scoreTexture;
extern Texture restartTexture;
extern Texture quitTexture;
extern bool isInRect(int x, int y, SDL_Rect rect);
#endif
