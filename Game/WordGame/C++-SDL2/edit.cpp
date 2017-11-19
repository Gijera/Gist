#include "edit.h"
#include "global.h"

enum FLAG{
    NONE,
    ADD,
    FIND
};

static enum FLAG flag = NONE;
static SDL_Color textColor = {0, 0, 0, 0xFF};

bool Edit::isWord()
{
    return infoText != "" && infoText != "add success" && infoText != "data error or word already exit, fail!" && infoText != "no find!" && infoText != "delete success!";
}

Edit::Edit()
{
    buttonRect[0].x = 50;
    buttonRect[0].y = 30;
    buttonRect[0].w = 60;
    buttonRect[0].h = 40;

    buttonRect[1].x = 70;
    buttonRect[1].y = 140;
    buttonRect[1].w = 450;
    buttonRect[1].h = 50;

    buttonRect[2].x = 520;
    buttonRect[2].y = 140;
    buttonRect[2].w = 50;
    buttonRect[2].h = 50;

    buttonRect[3].x = 70;
    buttonRect[3].y = 240;
    buttonRect[3].w = 450;
    buttonRect[3].h = 50;

    buttonRect[4].x = 520;
    buttonRect[4].y = 240;
    buttonRect[4].w = 50;
    buttonRect[4].h = 50;

    addText = "word + score";
    findText = "findword";
    infoText = "";

    editRect.x = 450;
    editRect.y = 340;
    editRect.w = 50;
    editRect.h = 50;

    hideDeleteRect.x = 520;
    hideDeleteRect.y = 340;
    hideDeleteRect.w = 50;
    hideDeleteRect.h = 50;
}

void Edit::handleEvent(SDL_Event *e)
{
    int i;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);

        for(i = 0; i < EDIT_BUTTON_RECT; i++){
            if(isInRect(x, y, buttonRect[i]))
                break;
        }

        if(isInRect(x, y, editRect) && isWord()){
            addText = infoText;
            deleteWordFromVector(infoText);
            infoText = "";
            i = 1;
        }

        if(isInRect(x, y, hideDeleteRect) && isWord()){
            deleteWordFromVector(infoText);
            infoText = "delete success!";
        }
        
        switch(i){
        case 0:
            windowState = INTERFACE;
            break;
        case 1:
            flag = ADD;
            break;
        case 2:
            if(addToVector(addText)){
                infoText = "add success";
            }
            else{
                infoText = "data error or word already exit, fail!";
            }
            addText = "";
            break;
        case 3:
            flag = FIND;
            break;
        case 4:{
            std::string tmp = findFromVector(findText);
            if(tmp != "")
                infoText = tmp;
            else
                infoText = "no find!";
            findText = "";
        }
            break;
        default:
            break;
        }
    }else if(e->type == SDL_KEYDOWN){
        switch(flag){
        case ADD:
            if(e->key.keysym.sym == SDLK_BACKSPACE && addText.length() > 0)
                addText.pop_back();
            break;
        case FIND:
            if(e->key.keysym.sym == SDLK_BACKSPACE && findText.length() > 0)
                findText.pop_back();
            break;
        default:
            break;
        }
    }else if(e->type == SDL_TEXTINPUT){
        switch(flag){
        case ADD:
            addText += e->text.text;
            break;
        case FIND:
            findText += e->text.text;
            break;
        default:
            break;
        }
    }

    if(flag != NONE){
        if(flag == ADD){
            if(addText != "")
                editAddTexture.loadFromRenderedText(addText.c_str(), textColor);
            else
                editAddTexture.loadFromRenderedText(" ",textColor);
        }else{
            if(findText != "")
                editFindTexture.loadFromRenderedText(findText.c_str(), textColor);
            else
                editFindTexture.loadFromRenderedText(" ",textColor);
        }
    }

    if(infoText != "")
        editInfoTexture.loadFromRenderedText(infoText.c_str(), textColor);
    else
        editInfoTexture.loadFromRenderedText(" ",textColor);
    
    char str[10];
    sprintf(str,"%d", (int)vecData.size());
    editCountTexture.loadFromRenderedText(str, textColor);
}

void Edit::render()
{
    editTexture.render(0, 0);
    editAddTexture.render(buttonRect[1].x + 5, buttonRect[1].y + 5);
    editFindTexture.render(buttonRect[3].x + 5, buttonRect[3].y + 5);
    editCountTexture.render(500, 30);
    editInfoTexture.render(70, 340);
    if(isWord())
        editDeleteTexture.render(editRect.x, editRect.y);
}

std::string Edit::getAddText()
{
    return addText;
}

std::string Edit::getFindText()
{
    return findText;
}

std::string Edit::getInfoText()
{
    return infoText;
}
