#include "global.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
Texture mainTexture;

Texture heroTexture[HERO];

Texture heroBlowUpTexture[HEROBLOWUP];

Texture enemy1Texture;
Texture enemy1DownTexture[ENEMY1DOWN];
Texture enemy2Texture;
Texture enemy2DownTexture[ENEMY2DOWN];
Texture enemy3Texture;
Texture enemy3DownTexture[ENEMY3DOWN];

Texture heroBulletTexture;
Texture enemyBulletTexture;
Texture bombBulletTexture;
Texture ufo1Texture;
Texture ufo2Texture;
Texture pauseTexture;
Texture resumeTexture;
