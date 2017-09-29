#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include <vector>
#include "texture.h"
#include "interface.h"
#include "setting.h"
#include "edit.h"
#include "file.h"
#include "game.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *font;
extern Mix_Music *music;
extern Mix_Chunk *down;
extern Mix_Chunk *wipe;
extern Mix_Chunk *error;
extern Texture mainTexture;
extern bool quit;

enum windowstate{
    INTERFACE,
    BEGIN,
    EDIT,
    SETTING,
    EXIT,
    GAMEOVER
};
extern enum windowstate windowState;

extern Texture interfaceTexture;
extern Interface interface;

extern bool soundOn;
extern Texture settingTexture;
extern Texture settingButtonTexture;
extern Setting setting;

extern Texture editTexture;
extern Texture editAddTexture;
extern Texture editFindTexture;
extern Texture editCountTexture;
extern Texture editInfoTexture;
extern Texture editDeleteTexture;
extern Edit edit;
extern std::string filePath;
extern std::vector<std::string> vecData;


extern Texture gameTexture;
extern Texture gameScoreTexture;
extern Texture gameWordTexture;
extern Texture gameOverTexture;
extern Texture alphaTexture[ALPHA];
extern Texture alphaCTexture[ALPHA];
extern Game game;
extern bool isInRect(int x, int y, SDL_Rect rect);
#endif
