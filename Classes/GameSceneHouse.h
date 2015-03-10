#ifndef __GAMESCENEHOUSE_H__
#define __GAMESCENEHOUSE_H__

#include "GameSceneBase.h"

class GameSceneHouse : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameSceneHouse);
private:
};

#endif