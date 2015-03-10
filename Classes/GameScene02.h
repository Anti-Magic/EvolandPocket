#ifndef __GAMESCENE02_H__
#define __GAMESCENE02_H__

#include "GameSceneBase.h"

class GameScene02 : public GameSceneBase
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	//void update(float dlt) override;
	//void fillData(SceneData& data) override;
	CREATE_FUNC(GameScene02);
	MapEnemy* createMapEnemy() override;
private:
};

#endif