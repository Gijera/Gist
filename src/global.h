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

extern Scheduler scheduler;

extern Texture mainTexture;

extern Texture heroTexture;

#define HEROBLOWUP 4
extern Texture heroBlowUpTexture[HEROBLOWUP];

#define ENEMY1DOWN 4
extern Texture enemy1Texture;
extern Texture enemy1DownTexture[ENEMY1DOWN];

#define ENEMY2DOWN 4
extern Texture enemy2Texture;
extern Texture enemy2DownTexture[ENEMY2DOWN];

#define ENEMY3DOWN 6
extern Texture enemy3Texture;
extern Texture enemy3DownTexture[ENEMY3DOWN];

extern Texture heroBulletTexture;
extern Texture enemyBulletTexture;
extern Texture bombBulletTexture;
extern Texture ufo1Texture;
extern Texture ufo2Texture;
extern Texture pauseTexture;
extern Texture resumeTexture;

extern bool isInRect(int x, int y, SDL_Rect rect);
#endif
