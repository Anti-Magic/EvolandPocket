#ifndef __GAMESCENE01_H__
#define __GAMESCENE01_H__

#include "GameSceneBase.h"

class GameScene01 : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	void update(float dlt) override;
	CREATE_FUNC(GameScene01);
	MapEnemy* createMapEnemy() override;
	bool _isroll; //ÇÐ»»¹ö¶¯ºÍ¾í¶¯
	cocos2d::Sprite* _black1;
	cocos2d::Sprite* _black2;
private:
	cocos2d::TMXLayer* _scrollLayer;
	int GID_Scroll_LR;
	int GID_Scroll_UD;
	void moveResponse2(float dlt);
};

#endif