#ifndef __GAMESCENEBASE_H__
#define __GAMESCENEBASE_H__

#include "TipsLayer.h"
#include "GameManager.h"
#include "GameMap.h"
#include "Player.h"
#include "MapEnemy.h"
#include "OperatorBase.h"
#include "cocos2d.h"
#include "DataService.h"

class GameSceneBase : public cocos2d::Layer
{
public:
	virtual ~GameSceneBase() {}
	virtual bool init() override;
	virtual void update(float dlt) override;
	virtual void fillData(SceneData& data);
	const std::string& getClassName();
	cocos2d::Layer* getGameLayer();
	virtual MapEnemy* createMapEnemy();
	void setOperator(OperatorBase* op);
protected:
	void initByManager();
	virtual void moveResponse(float dlt);
	virtual void triggerResponse(float dlt);

	cocos2d::Layer* _gameLayer;
	OperatorBase* _operator;
	GameMap* _gameMap;
	Player* _player;
	TipsLayer* _tipsLayer;
	GameManager* _gameManager;

	std::string _className;
};

#endif