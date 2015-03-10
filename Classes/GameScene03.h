#ifndef __GAMESCENE03_H__
#define __GAMESCENE03_H__

#include "GameSceneBase.h"

class GameScene03 : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene03);
	MapEnemy* createMapEnemy() override;
private:
};

#endif