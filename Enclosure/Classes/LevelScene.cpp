#include "LevelScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelScene::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	auto background = Sprite::create("Background.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);

	auto returnButton = Sprite::create("return.png");
	returnButton->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.2));
	returnButton->setTag(100);
	this->addChild(returnButton, 4);

	//add level
	_successLevel = LevelUtils::readLevelFromFile();
	std::string imagePath = "";
	
	//level = 10
	for (int i = 0; i != 10; i++){
		imagePath = i < _successLevel ? "level.png" : "lock.png";
		
		auto level = Sprite::create(imagePath);
		level->setTag(i + 1);
		level->setAnchorPoint(Vec2::ZERO);
		float x = 120 + i % 5 * (40 + 50);
		float y = 300 - i / 5 * (40 + 40);
		level->setPosition(Vec2(x, y));
		if (i < _successLevel){
			std::string str = StringUtils::format("%d", i + 1);
			auto *num = Label::createWithSystemFont(str, "arial", 30, Size(40, 40), TextHAlignment::CENTER);
			num->setAnchorPoint(Vec2::ZERO);
			num->setPosition(Vec2(x, y));
			this->addChild(num, 2);
		}
		this->addChild(level, 1);
	}
	
	//add Event listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch *touch, Event *event){
		Vec2 touchLocation = touch->getLocation();
		Vec2 nodeLocation = this->convertToNodeSpace(touchLocation);
		
		for (int i = 0; i < this->getChildrenCount(); i++){
			auto tempSprite = this->getChildren().at(i);
			
			if (tempSprite->getBoundingBox().containsPoint(nodeLocation)){
				if ((tempSprite->getTag() < _successLevel + 1) && (tempSprite->getTag() > 0)){
					Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
					//auto transition = TransitionSplitRows::create(2.0f, Game::createSceneWithLevel(tempSprite->getTag()));
					//Director::getInstance()->replaceScene(transition);
					
				}else if (tempSprite->getTag() > _successLevel && tempSprite->getTag() < 11){
					MessageBox("not open!", "Note");
					return true;
				}else if (tempSprite->getTag() == 100){
					auto transition = TransitionSplitRows::create(2.0f, MainMenu::createScene());
					Director::getInstance()->replaceScene(transition);
				}
			}
		}

		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}