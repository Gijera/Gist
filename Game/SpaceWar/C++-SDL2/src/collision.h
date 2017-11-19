#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <SDL2/SDL.h>
#include <vector>

/*O:one T:to M:many*/

bool OTORectCollision(const SDL_Rect &a, const SDL_Rect &b);

bool OTMRectCollision(SDL_Rect rect, std::vector<SDL_Rect> rects);

bool MTMRectCollision(std::vector<SDL_Rect> a, std::vector<SDL_Rect> b);
#endif
