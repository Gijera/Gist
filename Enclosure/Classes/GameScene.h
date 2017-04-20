#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "EnemySprite.h"
#include "PlayerSprite.h"

class Game : public cocos2d::Layer{
public:
	static cocos2d::Scene* createSceneWithLevel(int level);
	
	static const int Column = (640 / 32);

	static const int Line = (480 / 32);

	static const int Side = 32;
	
	virtual bool init();

	CREATE_FUNC(Game);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);

	void update(float delta);
	
	int _screenWidth, _screenHeight;
private:
	bool _isMenu;
	bool _isPause;
	int _score = 0;
	int _level = 1;
	PlayerSprite *_player;
	cocos2d::Vector<EnemySprite *> _enemy;	
	cocos2d::Vector<cocos2d::Sprite *> _trace;
	std::vector<cocos2d::Point> _newget;
	std::vector<cocos2d::Point> _newunget;
	std::vector<cocos2d::Point> _get;
	std::vector<cocos2d::Point> _unget;	

	void getNewUnget();
	void fillAll(float x, float y);
	void handle();
	bool collisionDetection(float delta);
};
#endif