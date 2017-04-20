#ifndef _GLOBALFUNC_H_
#define _GLOBALFUNC_H_

#include "cocos2d.h"

extern cocos2d::Point convertToGame(cocos2d::Point point);
extern cocos2d::Point convertToMap(cocos2d::Point point);
extern bool isInVector(cocos2d::Point point, std::vector<cocos2d::Point> vec, bool convert);

#endif