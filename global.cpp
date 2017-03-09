#include "global.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
Mix_Music *music = NULL;
Mix_Chunk *down = NULL;
Mix_Chunk *wipe = NULL;
Mix_Chunk *error = NULL;
Texture mainTexture;
bool quit = false;

enum windowstate windowState = INTERFACE;

Texture interfaceTexture;
Interface interface;

bool soundOn = 1;
Texture settingTexture;
Texture settingButtonTexture;
Setting setting;

Texture editTexture;
Texture editAddTexture;
Texture editFindTexture;
Texture editCountTexture;
Texture editInfoTexture;
Texture editDeleteTexture;
Edit edit;
std::string filePath = "./file/word.txt";
std::vector<std::string> vecData;

Texture gameTexture;
Texture gameScoreTexture;
Texture gameWordTexture;
Texture gameOverTexture;
Texture alphaTexture[ALPHA];
Texture alphaCTexture[ALPHA];
Game game;
bool isInRect(int x, int y, SDL_Rect rect)
{
    bool inside = true;
    if(x < rect.x)
        inside = false;
    else if(x > (rect.x + rect.w))
        inside = false;
    else if(y < rect.y)
        inside = false;
    else if(y > (rect.y + rect.h))
        inside = false;
    return inside;
}
