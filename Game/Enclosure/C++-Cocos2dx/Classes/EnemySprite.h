#ifndef _ENEMYSPRITE_H_
#define _ENEMYSPRITE_H_

#include "cocos2d.h"
#include "GlobalFunc.h"

USING_NS_CC;

#define LEFTUP 1
#define LEFTDOWN 2
#define RIGHTUP 3
#define RIGHTDOWN 4

class EnemySprite : public cocos2d::Sprite{
private:
	int _director;
	int _X, _Y;
	int _vec;
public:
	static EnemySprite* create(const std::string &filename){
		EnemySprite *sprite = new EnemySprite();
		if (sprite && sprite->initWithFile(filename)){
			sprite->autorelease();
			return sprite;
		}
		return nullptr;
	}
	
	void setDirector(int x){
		if (x > 0 && x < 5)
			_director = x;
	}

	void setXY(const int x, const int y){
		_X = x;
		_Y = y;
	}

	int getX(){ return _X; }
	int getY(){ return _Y; }

	void setVec(int v){
		_vec = v;
	}

	virtual void move(std::vector<cocos2d::Point> vec){
		cocos2d::Point temp;

		switch (_director){
		case LEFTUP:
			if (isInVector(temp = getPointWithDirector(Vec2(_X, _Y), _director), vec, true)){
				if ((isInVector(Vec2(temp.x + 1, temp.y), vec, true) && isInVector(Vec2(temp.x, temp.y - 1), vec, true)) || 
					(!isInVector(Vec2(temp.x + 1, temp.y), vec, true) && !isInVector(Vec2(temp.x, temp.y - 1), vec, true))){
					_director = RIGHTDOWN;
				}else if ((isInVector(Vec2(temp.x + 1, temp.y), vec, true))){
					_director = LEFTDOWN;
				}else{
					_director = RIGHTUP;
				}
			}
			break;
		case LEFTDOWN:
			if (isInVector(temp = getPointWithDirector(Vec2(_X, _Y), _director), vec, true)){
				if ((isInVector(Vec2(temp.x + 1, temp.y), vec, true) && isInVector(Vec2(temp.x, temp.y + 1), vec, true)) ||
					(!isInVector(Vec2(temp.x + 1, temp.y), vec, true) && !isInVector(Vec2(temp.x, temp.y + 1), vec, true))){
					_director = RIGHTUP;
				}
				else if ((isInVector(Vec2(temp.x + 1, temp.y), vec, true))){
					_director = LEFTUP;
				}
				else{
					_director = RIGHTDOWN;
				}
			}
			break;
		case RIGHTUP:
			if (isInVector(temp = getPointWithDirector(Vec2(_X, _Y), _director), vec, true)){
				if ((isInVector(Vec2(temp.x - 1, temp.y), vec, true) && isInVector(Vec2(temp.x, temp.y - 1), vec, true)) ||
					(!isInVector(Vec2(temp.x - 1, temp.y), vec, true) && !isInVector(Vec2(temp.x, temp.y - 1), vec, true))){
					_director = LEFTDOWN;
				}
				else if ((isInVector(Vec2(temp.x - 1, temp.y), vec, true))){
					_director = RIGHTDOWN;
				}
				else{
					_director = LEFTUP;
				}
			}
			break;
		case RIGHTDOWN:
			if (isInVector(temp = getPointWithDirector(Vec2(_X, _Y), _director), vec, true)){
				if ((isInVector(Vec2(temp.x - 1, temp.y), vec, true) && isInVector(Vec2(temp.x, temp.y + 1), vec, true)) ||
					(!isInVector(Vec2(temp.x - 1, temp.y), vec, true) && !isInVector(Vec2(temp.x, temp.y + 1), vec, true))){
					_director = LEFTUP;
				}
				else if ((isInVector(Vec2(temp.x - 1, temp.y), vec, true))){
					_director = RIGHTUP;
				}
				else{
					_director = LEFTDOWN;
				}
			}
			break;
		default:
			break;
		}

		setPointWithDirector();
		this->setPosition(Vec2(_X, _Y));
	}

	void setPointWithDirector(){
		switch (_director){
		case LEFTUP:
			_X -= _vec;
			_Y += _vec;
			break;
		case LEFTDOWN:
			_X -= _vec;
			_Y -= _vec;
			break;
		case RIGHTUP:
			_X += _vec;
			_Y += _vec;
			break;
		case RIGHTDOWN:
			_X += _vec;
			_Y -= _vec;
			break;
		default:
			break;
		}
	}

	cocos2d::Point getPointWithDirector(cocos2d::Point point, int dir){
		switch (dir){
		case LEFTUP:
			point.x -= 17;
			point.y += 17;
			break;
		case LEFTDOWN:
			point.x -= 17;
			point.y -= 17;
			break;
		case RIGHTUP:
			point.x += 17;
			point.y += 17;
			break;
		case RIGHTDOWN:
			point.x += 17;
			point.y -= 17;
			break;
		default:
			break;
		}
		return point;
	}
};
#endif