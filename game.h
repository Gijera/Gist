#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <string>
#include "element.h"

enum alpha{
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
};
#define ALPHA 26
#define ELEMENT 16

class Game{
public:
    Game();

    void handleEvent(SDL_Event *e);
    
    void render();

    std::vector<int> wordId;
    std::vector<int> wordPos;
    std::string wordSelect;
    Element element[ELEMENT];
private:
    int score;
    std::string gameWord;
    SDL_Rect toMenu;
    SDL_Rect wordOk;
    SDL_Rect wordDel;
};
#endif
