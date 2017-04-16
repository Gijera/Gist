#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_

#include "cocos2d.h"

class SourceLoad : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onEnterTransitionDidFinish();

	void loadSpriteSheets(cocos2d::ValueVector spriteSheets);

	void progressUpdate();

	CREATE_FUNC(SourceLoad);
protected:
	int _sourceCount;

	cocos2d::ProgressTimer *_progress;

	float _progressInterval;
};
#endif