#include "LoadScene.h"
#include "LevelScene.h"

USING_NS_CC;

Scene* SourceLoad::createScene()
{
	auto scene = Scene::create();
	auto layer = SourceLoad::create();
	scene->addChild(layer);
	return scene;
}

bool SourceLoad::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Background.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);

	auto barSprite = Sprite::create("LoadingBar.png");

	_progress = ProgressTimer::create(barSprite);
	_progress->setPercentage(0.0f);
	_progress->setMidpoint(Vec2(0.0f, 1.0f));
	_progress->setBarChangeRate(Vec2(1.0f, 0.0f));
	_progress->setType(ProgressTimer::Type::BAR);
	_progress->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_progress, 10);

	auto label = LabelTTF::create("Loading...", "Marker Felt", 30);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
	this->addChild(label);
	return true;
}

void SourceLoad::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	
	ValueMap map = FileUtils::getInstance()->getValueMapFromFile("SourceLoad.plist");

	ValueVector spriteSheets = map.at("SpriteSheets").asValueVector();
	
	_sourceCount = spriteSheets.size();

	_progressInterval = 100 / _sourceCount;
	
	loadSpriteSheets(spriteSheets);
}

void SourceLoad::loadSpriteSheets(ValueVector spriteSheets)
{
	for (unsigned int i = 0; i != spriteSheets.size(); i++){
		Value v = spriteSheets.at(i);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(v.asString().c_str());
		progressUpdate();
	}
}

void SourceLoad::progressUpdate()
{
	if (--_sourceCount){
		_progress->setPercentage(100.0f - (_progressInterval * _sourceCount));
	}else{
		auto ptf = ProgressFromTo::create(1.0f, _progress->getPercentage(), 100);

		auto callFunc = CallFunc::create([=]{
			auto delay = DelayTime::create(1.0f);
			Director::getInstance()->replaceScene(LevelScene::createScene());
		});

		auto action = Sequence::create(ptf, callFunc, NULL);
		_progress->runAction(action);
	}
}