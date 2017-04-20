#include "GameScene.h"
#include "GlobalFunc.h"
#include "ui/CocosGUI.h"
#include "LevelScene.h"
#include "MenuScene.h"
#include <sstream>
#include <iostream>
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
	
	_isMenu = false;
	_isPause = false;
	_level = currentLevel;
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	std::string answer = StringUtils::format("level%d.png", _level);
	for (int i = 0; i != Line; i++){
		for (int j = 0; j != Column; j++){
			auto rect = Rect(j * 32, i * 32, 32, 32);
			auto spriteFrame = SpriteFrame::create(answer, rect);
			std::string spriteName = StringUtils::format("answer%d", i * Column + j);
			SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, spriteName);

			if (i == 0 || i == Line - 1 || j == 0 || j == Column - 1){
				auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
				auto sprite = Sprite::createWithSpriteFrame(spriteFrame);
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
	auto levelLabel = LabelTTF::create(buf.str(), "Î¢ÈíÑÅºÚ", 30);
	levelLabel->setColor(Color3B(0, 0, 0));
	levelLabel->setAnchorPoint(Vec2(0, 1));
	levelLabel->setPosition(Vec2(0, 480));
	this->addChild(levelLabel, 10);

	auto pauseButton = Button::create("pause.png");
	pauseButton->setPosition(Vec2(620, 460));
    pauseButton->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			if (_isPause){
				Director::getInstance()->resume();
				_isPause = false;
			}else{
				Director::getInstance()->pause();
				_isPause = true;
			}
		}
	});
	pauseButton->setOpacity(0);
	this->addChild(pauseButton, 13);
	
	auto levelButton = Button::create("levelButton.png");
	levelButton->setPosition(Vec2(620, 460));
	levelButton->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			auto transition = TransitionSlideInR::create(2.0, LevelScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	levelButton->setOpacity(0);
	this->addChild(levelButton, 14);
	
	auto menuButton = Button::create("menuButton.png");
	menuButton->setPosition(Vec2(620, 460));
	menuButton->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			auto transition = TransitionSlideInR::create(2.0, MainMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	menuButton->setOpacity(0);
	this->addChild(menuButton, 15);
	
	//menu
	auto returnButton = Button::create("menu.png");
	returnButton->setPosition(Vec2(620, 460));
	returnButton->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			if (_isMenu){
				auto action1 = MoveTo::create(2.0, Vec2(620, 460));
				auto fadeOut1 = FadeOut::create(2.0);
				pauseButton->runAction(Spawn::create(action1, fadeOut1, NULL));
				auto action2 = MoveTo::create(2.0, Vec2(620, 460));
				auto fadeOut2 = FadeOut::create(2.0);
				levelButton->runAction(Spawn::create(action2, fadeOut2, NULL));
				auto action3 = MoveTo::create(2.0, Vec2(620, 460));
				auto fadeOut3 = FadeOut::create(2.0);
				menuButton->runAction(Spawn::create(action3, fadeOut3, NULL));
				_isMenu = false;
			}else{
				auto action1 = MoveTo::create(2.0, Vec2(500, 460));
				auto fadeIn1 = FadeIn::create(2.0);
				pauseButton->runAction(Spawn::create(action1, fadeIn1, NULL));
				auto action2 = MoveTo::create(2.0, Vec2(540, 460));
				auto fadeIn2 = FadeIn::create(2.0);
				levelButton->runAction(Spawn::create(action2, fadeIn2, NULL));
				auto action3 = MoveTo::create(2.0, Vec2(580, 460));
				auto fadeIn3 = FadeIn::create(2.0);
				menuButton->runAction(Spawn::create(action3, fadeIn3, NULL));
				_isMenu = true;
			}
		}
	});
	this->addChild(returnButton, 16);

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
		enemy->setDirector(rand() % 4 + 1);
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

	if (_get.size() > 240){
		this->unscheduleUpdate();
		_eventDispatcher->removeAllEventListeners();
		if (currentLevel == 20){
			auto transition = TransitionSlideInL::create(2.0, LevelScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}

		if (currentLevel == LevelUtils::readLevelFromFile()){
			LevelUtils::writeLevelToFile(currentLevel + 1);
		}
		
		auto nextButton = Button::create("button.png");
		nextButton->setScale(1.2f);
		nextButton->setPosition(Vec2(_screenWidth / 2, _screenHeight * 0.6));
		nextButton->setTitleText("Next Level");
		nextButton->setTitleFontName("Î¢ÈíÑÅºÚ");
		nextButton->setTitleFontSize(25);
		nextButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED){
				auto transition = TransitionSlideInL::create(2.0, Game::createSceneWithLevel(currentLevel + 1));
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(nextButton, 100);

		auto menuButton = Button::create("button.png");
		menuButton->setScale(1.2f);
		menuButton->setPosition(Vec2(_screenWidth / 2, _screenHeight * 0.4));
		menuButton->setTitleText("Main Menu");
		menuButton->setTitleFontName("Î¢ÈíÑÅºÚ");
		menuButton->setTitleFontSize(25);
		menuButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED){
				auto transition = TransitionSlideInL::create(2.0, MainMenu::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(menuButton, 101);
	}

	if (collisionDetection(delta)){
		this->unscheduleUpdate();
		_eventDispatcher->removeAllEventListeners();
		auto nextButton = Button::create("button.png");
		nextButton->setScale(1.2f);
		nextButton->setPosition(Vec2(_screenWidth / 2, _screenHeight * 0.6));
		nextButton->setTitleText("Restart");
		nextButton->setTitleFontName("Î¢ÈíÑÅºÚ");
		nextButton->setTitleFontSize(25);
		nextButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED){
				auto transition = TransitionSlideInL::create(2.0, Game::createSceneWithLevel(currentLevel));
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(nextButton, 100);

		auto menuButton = Button::create("button.png");
		menuButton->setScale(1.2f);
		menuButton->setPosition(Vec2(_screenWidth / 2, _screenHeight * 0.4));
		menuButton->setTitleText("Main Menu");
		menuButton->setTitleFontName("Î¢ÈíÑÅºÚ");
		menuButton->setTitleFontSize(25);
		menuButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED){
				auto transition = TransitionSlideInL::create(2.0, MainMenu::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
		this->addChild(menuButton, 101);
	}
}

bool Game::collisionDetection(float delta)
{
	for (auto it = _trace.begin(); it != _trace.end(); it++){
		for (auto oit = _enemy.begin(); oit != _enemy.end(); oit++){
			if ((*it)->getBoundingBox().intersectsRect((*oit)->getBoundingBox()))
				return true;
		}
	}
	return false;
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
		getNewUnget();
		handle();

		for (auto it = _trace.begin(); it != _trace.end(); it++){
			this->removeChild(*it);
		}

		_unget.swap(_newunget);
		_newunget.clear();
		//_newunget.erase(_newunget.begin(), _newunget.end());
		//std::vector<Point> temp;
		//temp.swap(_newunget);

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
			int temp = (it->y) * Column + (it->x);
			std::string spriteName = StringUtils::format("answer%d", temp);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
			auto sprite = Sprite::createWithSpriteFrame(spriteFrame);
			sprite->setPosition(convertToMap(Vec2(it->x, it->y)));
			auto fadeIn = FadeIn::create(2);
			sprite->setOpacity(0);
			this->addChild(sprite, 5);
			sprite->runAction(fadeIn);
			_get.push_back(*it);
		}
	}
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
}

