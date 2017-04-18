#ifndef _PLAYERSPRITE_H_
#define _PLAYERSPRITE_H_

#include "cocos2d.h"
#include "GlobalFunc.h"

USING_NS_CC;

#define PS_UP 5
#define PS_DOWN 6
#define PS_RIGHT 7
#define PS_LEFT 8

class PlayerSprite : public Sprite{
private:
	int _X = 0, _Y = 14;
	int _director = 0;
public:
	static PlayerSprite* create(const std::string &filename){
		PlayerSprite *sprite = new PlayerSprite();
		if (sprite && sprite->initWithFile(filename)){
			sprite->autorelease();
			return sprite;
		}
		return nullptr;
	}
	
	int getX(){ return _X; }
	int getY(){ return _Y; }

	void setXY(int x, int y){
		_X = x;
		_Y = y;
	}

	int getDirector(){ return _director; }

	void setDirector(int i){
		if (i >= 5 && i <= 8)
			_director = i;
		else
			_director = 0;
	}
	
	void move(){
		switch (_director){
		case PS_DOWN:
			if (_Y < 14)
				_Y++;
			break;
		case PS_UP:
			if (_Y > 0)
				_Y--;
			break;
		case PS_RIGHT:
			if (_X < 19)
				_X++;
			break;
		case PS_LEFT:
			if (_X > 0)
				_X--;
			break;
		default:
			break;
		}

		this->setPosition( convertToMap(Vec2(_X, _Y)) );
	}
};
#endif