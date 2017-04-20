#ifndef _LEVELSCENE_H_
#define _LEVELSCENE_H_

#include "cocos2d.h"

class LevelUtils : public cocos2d::Ref{
public:
	static int readLevelFromFile(){
		int _successLevel = cocos2d::UserDefault::getInstance()->getIntegerForKey("SuccessLevel");
		if (_successLevel)
			return _successLevel;

		return 1;
	}

	static void writeLevelToFile(int level){
		cocos2d::UserDefault::getInstance()->setIntegerForKey("SuccessLevel", level);
	}
};

class LevelScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelScene);
private:
	int _successLevel;
	int _screenWidth, _screenHeight;
};
#endif