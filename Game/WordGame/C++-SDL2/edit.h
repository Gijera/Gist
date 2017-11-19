#ifndef _EDIT_H_
#define _EDIT_H_

#include <SDL2/SDL.h>
#include <string>
#define EDIT_BUTTON_RECT 5

class Edit{
public:
    Edit();

    void handleEvent(SDL_Event *e);

    void render();

    bool isWord();
    std::string getAddText();
    std::string getFindText();
    std::string getInfoText();
private:
    SDL_Rect buttonRect[EDIT_BUTTON_RECT];
    SDL_Rect editRect;
    SDL_Rect hideDeleteRect;
    std::string addText;
    std::string findText;
    std::string infoText;
};
#endif
