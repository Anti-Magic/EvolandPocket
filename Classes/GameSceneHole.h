#ifndef __GAMESCENEHOLE_H__
#define __GAMESCENEHOLE_H__

class RoundFight;

#include "GameSceneBase.h"

class GameSceneHole : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameSceneHole);
	MapEnemy* createMapEnemy() override;
	RoundFight* _roundfight;
private:
};

#endif