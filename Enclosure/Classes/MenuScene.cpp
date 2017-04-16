#include "MenuScene.h"
#include "LoadScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	auto menuBackground = Sprite::create("MenuBackground.jpg");
	menuBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menuBackground, 0);

	auto startButton = Button::create("button.png");
	startButton->setTitleText("Start");
	startButton->setTitleFontName("Î¢ÈíÑÅºÚ");
	startButton->setTitleFontSize(16);
	startButton->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height*0.7));
	startButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			auto transition = TransitionSlideInL::create(2.0f, SourceLoad::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(startButton, 10);
	auto moveto1 = MoveTo::create(2, Point(visibleSize.width * 0.7, visibleSize.height * 0.55));
	startButton->runAction(moveto1);


	auto settingButton = Button::create("button.png");
	settingButton->setTitleText("Setting");
	settingButton->setTitleFontName("Î¢ÈíÑÅºÚ");
	settingButton->setTitleFontSize(16);
	settingButton->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.5));
	settingButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			;
		}
	});
	this->addChild(settingButton, 11);
	auto moveto2 = MoveTo::create(2, Point(visibleSize.width * 0.7, visibleSize.height * 0.4));
	settingButton->runAction(moveto2);

	auto closeButton = Button::create("button.png");
	closeButton->setTitleText("Close");
	closeButton->setTitleFontName("Î¢ÈíÑÅºÚ");
	closeButton->setTitleFontSize(16);
	closeButton->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height*0.3));
	closeButton->addTouchEventListener([](Ref *pSender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button, windows store apps do not implement a close button", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	});
	this->addChild(closeButton, 12);
	auto moveto3 = MoveTo::create(2, Point(visibleSize.width * 0.7, visibleSize.height * 0.25));
	closeButton->runAction(moveto3);
	return true;
}