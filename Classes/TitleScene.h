#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
#include "PopDialog.h"

class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(TitleScene);
private:
	void preloadMusic();
	void initTitle();
	void initButtons();

	void startButtonPress(cocos2d::Ref* sender);
	void continueButtonPress(cocos2d::Ref* sender);
	void exitButtonPress(cocos2d::Ref* sender);

	void update(float dlt);
	cocos2d::Sprite* _cloud1;
	cocos2d::Sprite* _cloud2;
	PopDialog* _popdialog;

	cocos2d::Scene* getNewGameScene();
	cocos2d::Scene* getContinueGameScene();
};

#endif