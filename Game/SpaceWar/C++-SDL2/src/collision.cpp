#include "collision.h"
#include "global.h"

bool OTORectCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    bool collision = true;
    if(a.x + a.w < b.x)
        collision = false;
    else if(a.y + a.h < b.y)
        collision = false;
    else if(b.x + b.w < a.x)
        collision = false;
    else if(b.y + b.h < a.y)
        collision = false;
    return collision;
}

bool OTMRectCollision(SDL_Rect rect, std::vector<SDL_Rect> rects);

bool MTMRectCollision(std::vector<SDL_Rect> a, std::vector<SDL_Rect> b);
