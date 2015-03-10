#ifndef __GAMESCENEWORLD_H__
#define __GAMESCENEWORLD_H__

class RoundFight;

#include "GameSceneBase.h"

class GameSceneWorld : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameSceneWorld);
	RoundFight* _roundfight;
private:
};

#endif