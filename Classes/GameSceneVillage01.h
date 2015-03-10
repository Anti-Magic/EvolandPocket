#ifndef __GAMESCENEVILLAGE01_H__
#define __GAMESCENEVILLAGE01_H__

#include "GameSceneBase.h"

class GameSceneVillage01 : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameSceneVillage01);
private:
	virtual void moveResponse(float dlt) override;
	cocos2d::TMXLayer* _npcLayer;
};

#endif