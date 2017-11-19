#include "element.h"
#include "global.h"

Element::Element()
{
    vecId = 0;
}

void Element::setId(int id)
{
    vecId = id;
    for(int i = 0; i < MAXALPHA; i++){
        vecButton[i].x = vecId * 40;
        vecButton[i].y = 400 - (i * 40);
        vecButton[i].w = 40;
        vecButton[i].h = 40;
    }
}

void Element::sendAlpha()
{
    if(soundOn)
        Mix_PlayChannel(-1, down, 0);
    int tmpalpha = (rand() % 26);
    vecAlpha.push_back(tmpalpha);
    vecSelect.push_back(false);
}

void Element::render()
{
    for(int i = 0; i < vecAlpha.size(); i++){
        if(vecSelect[i] == false)
            alphaTexture[vecAlpha[i]].render(vecButton[i].x , vecButton[i].y);
        else
            alphaCTexture[vecAlpha[i]].render(vecButton[i].x , vecButton[i].y);
    }
}

void Element::handleEvent(SDL_Event *e)
{
    if(vecAlpha.size() > MAXALPHA){
        Mix_PlayChannel(-1, error, 0);
        windowState = GAMEOVER;
        return;
    }
    
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i = 0; i < vecAlpha.size(); i++)
            if(isInRect(x, y, vecButton[i])){
                if(vecSelect[i] == false){
                    vecSelect[i] = true;
                    game.wordId.push_back(vecId);
                    game.wordPos.push_back(i);
                    game.wordSelect.push_back(vecAlpha[i] + 65);
                }else{
                    vecSelect[i] = false;
                    for(int j = 0; j < game.wordSelect.size(); j++){
                        if((*(game.wordPos.begin() + j)) == i && (*(game.wordId.begin() + j) == vecId)){
                            game.wordSelect.erase(j, 1);
                            game.wordPos.erase(game.wordPos.begin() + j);
                            game.wordId.erase(game.wordId.begin() + j);
                            break;
                        }    
                    }
                }
            }
    }
}

void Element::deleteAlpha(int i)
{
    std::vector<int>::iterator it;
    it = vecAlpha.begin() + i;
    vecAlpha.erase(it);
}
