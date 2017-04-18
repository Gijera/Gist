#include "GameScene.h"
#include "GlobalFunc.h"
#include "ui/CocosGUI.h"
#include <sstream>

USING_NS_CC;
using namespace ui;

static int currentLevel;
static Point getWithDirector(Point p, int d);

Scene* Game::createSceneWithLevel(int level)
{
    currentLevel = level;
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	_level = currentLevel;
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	std::string answer = StringUtils::format("level%d.png", _level);
	for (int i = 0; i != Line; i++){
		for (int j = 0; j != Column; j++){
			auto rect = Rect(j * 32, i * 32, 32, 32);
			auto sprite = Sprite::create(answer, rect);

			if (i == 0 || i == Line - 1 || j == 0 || j == Column - 1){
				sprite->setPosition(Vec2(Side / 2 + j * Side, _screenHeight - Side / 2 - i * Side));
				this->addChild(sprite, 5);
				_get.push_back(Point(j, i));
			}else{
				_unget.push_back(Point(j, i));
			}
		}
	}
	
	//background
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(_screenWidth / 2, _screenHeight / 2));
	this->addChild(background, 0);

	//level label
	std::ostringstream buf;
	buf << "level:" << _level << std::endl;
	auto levelLabel = LabelTTF::create(buf.str(), "Enclosure", 30);
	levelLabel->setColor(Color3B(0, 0, 0));
	levelLabel->setAnchorPoint(Vec2(0, 1));
	levelLabel->setPosition(Vec2(0, 480));
	this->addChild(levelLabel, 10);

	//health
	for (int i = 0; i != _health; i++){
		auto health = Sprite::create("health.png");
		health->setPosition(Vec2(300 + i * 40, 460));
		this->addChild(health, 11);
	}

	//menu
	auto returnButton = Button::create("menu.png");
	returnButton->setPosition(Vec2(620, 460));
	returnButton->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			;
		}
	});
	this->addChild(returnButton, 12);

	//player
	_player = PlayerSprite::create("player.png");
	this->addChild(_player, 7);
	_player->move();
	//listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//enemy
	for (int i = 0; i != _level; i++){
		EnemySprite *enemy = EnemySprite::create("enemy.png");
		enemy = EnemySprite::create("enemy.png");
		enemy->setXY(48 + rand() % 500, 48 + rand() % 380);
		enemy->setVec(1);
		enemy->setDirector(rand() % 5);
		_enemy.pushBack(enemy);
		this->addChild(enemy, 6);
	}
	//update
	//schedule(schedule_selector(Game::updateCustom), 0.1f, kRepeatForever, 0);
	scheduleUpdate();

	return true;
}

void Game::update(float delta){
	for (auto it = _enemy.begin(); it != _enemy.end(); it++)
		(*it)->move(_get);
}

void Game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	static bool flag = false;
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_player->setDirector(PS_UP);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_player->setDirector(PS_DOWN);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_player->setDirector(PS_RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_player->setDirector(PS_LEFT);
		break;
	default:
		_player->setDirector(0);
		break;
	}

	if (_player->getDirector() != 0 && !isInVector(Vec2(_player->getX(), _player->getY()), _get, false) 
		&& !isInVector(Vec2(_player->getX(), _player->getY()), _newget, false)){
		auto trace = Sprite::create("trace.png");
		trace->setPosition(convertToMap(Vec2(_player->getX(), _player->getY())));
		this->addChild(trace, 4);
		_trace.pushBack(trace);
		_newget.push_back(Vec2(_player->getX(), _player->getY()));
		flag = true;
	}

	_player->move();

	if (flag && isInVector(Vec2(_player->getX(), _player->getY()), _get, false)){
		std::vector<Point> temp;
		getNewUnget();
		handle();

		for (auto it = _trace.begin(); it != _trace.end(); it++){
			this->removeChild(*it);
		}
		_trace.clear();
		_newget.clear();
		flag = false;
	}
}

void Game::handle()
{
	std::string answer = StringUtils::format("level%d.png", _level);
	for (auto it = _unget.begin(); it != _unget.end(); it++){
		if (!isInVector((*it), _newunget, false)){
			auto rect = Rect(it->x * 32, it->y * 32, 32, 32);
			auto sprite = Sprite::create(answer, rect);
			sprite->setPosition(convertToMap(Vec2(it->x, it->y)));
			this->addChild(sprite, 5);
			_get.push_back(*it);
		}
	}

	_unget.swap(_newunget);
	_newunget.clear();
}

void Game::getNewUnget()
{
	float x, y;
	for (auto it = _enemy.begin(); it != _enemy.end(); it++){
		x = ((*it)->getX()) / 32;
		y = 15 - ((*it)->getY()) / 32;
		fillAll(x, y);
	}
}



void Game::fillAll(float x, float y)
{
	float m, n;
	if (isInVector(Vec2(x, y), _unget, false) && !isInVector(Vec2(x, y), _newget, false) && !isInVector(Vec2(x, y), _newunget, false)){
		_newunget.push_back(Vec2(x, y));
	}

	m = x;
	n = y - 1;
	if (isInVector(Vec2(m, n), _unget, false) && !isInVector(Vec2(m, n), _newget, false) && !isInVector(Vec2(m, n), _newunget, false)){
		_newunget.push_back(Vec2(m, n));
		fillAll(m, n);
	}
	m = x + 1;
	n = y;
	if (isInVector(Vec2(m, n), _unget, false) && !isInVector(Vec2(m, n), _newget, false) && !isInVector(Vec2(m, n), _newunget, false)){
		_newunget.push_back(Vec2(m, n));
		fillAll(m, n);
	}
	m = x;
	n = y + 1;
	if (isInVector(Vec2(m, n), _unget, false) && !isInVector(Vec2(m, n), _newget, false) && !isInVector(Vec2(m, n), _newunget, false)){
		_newunget.push_back(Vec2(m, n));
		fillAll(m, n);
	}
	m = x - 1;
	n = y;
	if (isInVector(Vec2(m, n), _unget, false) && !isInVector(Vec2(m, n), _newget, false) && !isInVector(Vec2(m, n), _newunget, false)){
		_newunget.push_back(Vec2(m, n));
		fillAll(m, n);
	}
	return;
}

