#include "GlobalFunc.h"

cocos2d::Point convertToGame(cocos2d::Point point)
{
	cocos2d::Point temp;
	temp.x = (int)(point.x / 32);
	temp.y = (int)(15 - point.y / 32);
	return temp;
}

cocos2d::Point convertToMap(cocos2d::Point point)
{
	cocos2d::Point temp;
	temp.x = (int)(16 + point.x * 32);
	temp.y = (int)(480 - 16 - point.y * 32);
	return temp;
}

bool isInVector(cocos2d::Point point, std::vector<cocos2d::Point> vec, bool convert){
	if (convert)
		point = convertToGame(point);

	for (auto it = vec.begin(); it != vec.end(); it++){
		if (it->x == point.x && it->y == point.y)
			return true;
	}

	return false;
}