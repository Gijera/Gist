#include <algorithm>
#include "game.h"
#include "global.h"

static int timer;
static SDL_Color textColor = {0xB1, 0x23, 0x33, 0xFF};
static SDL_Color wordColor = {0x3b, 0x3b, 0x6d, 0xFF};

Game::Game()
{
    toMenu.x = 540;
    toMenu.y = 15;
    toMenu.w = 100;
    toMenu.h = 40;

    score = 0;

    gameWord = " ";
    wordDel.x = 560;
    wordDel.y = 440;
    wordDel.w = 40;
    wordDel.h = 40;
    wordOk.x = 600;
    wordOk.y = 440;
    wordOk.w = 40;
    wordOk.h = 40;

    for(int i = 0; i < ELEMENT; i++){
        element[i].setId(i);
        element[i].sendAlpha();
        element[i].sendAlpha();
        element[i].sendAlpha();
    }
}

void Game::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(isInRect(x, y, toMenu))
            windowState = INTERFACE;
        if(isInRect(x, y, wordDel)){
            for(int i = 0; i < wordSelect.size(); i++){
                element[wordId[i]].vecSelect[wordPos[i]] = false;
            }
            wordId.clear();
            wordPos.clear();
            wordSelect = "";
        }
        if(isInRect(x, y, wordOk)){
            transform(wordSelect.begin(), wordSelect.end(), wordSelect.begin(),(int(*)(int))tolower);
            if(findFromVector(wordSelect) != ""){
                if(soundOn)
                    Mix_PlayChannel(-1, wipe, 0);
                score += getScore(wordSelect);
                for(int i = 0; i < ELEMENT; i++){
                    std::vector<int>::iterator it = element[i].vecAlpha.begin();
                    std::vector<bool>::iterator itr = element[i].vecSelect.begin();
                    for(;it != element[i].vecAlpha.end();){
                        if(*itr == true){
                            element[i].vecAlpha.erase(it);
                            element[i].vecSelect.erase(itr);
                            continue;
                        }
                        it++;
                        itr++;
                    }
                }
                wordId.clear();
                wordPos.clear();
                wordSelect = "";
            }else{
                if(soundOn)
                    Mix_PlayChannel(-1, error, 0);
            }
            transform(wordSelect.begin(), wordSelect.end(), wordSelect.begin(),(int(*)(int))toupper);
        }
    }

    for(int i = 0; i < ELEMENT; i++){
        int timer = rand()%10 + 1000;
        int x = rand()%(timer-1);
        if(x % timer == 0){
            element[i].sendAlpha();
        }

        element[i].handleEvent(e);
    }
}

void Game::render()
{
    gameTexture.render(0, 0);

    char str[10];
    sprintf(str, "%d", score);
    gameScoreTexture.loadFromRenderedText(str, textColor);
    gameScoreTexture.render(100, 18);

    gameWord = " " + wordSelect;
    gameWordTexture.loadFromRenderedText(gameWord, wordColor);
    gameWordTexture.render(2, 442);

    for(int i = 0; i < ELEMENT; i++)
        element[i].render();
}
