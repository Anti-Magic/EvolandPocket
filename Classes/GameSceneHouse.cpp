#include "GameSceneHouse.h"
#include "Player_3.h"
#include "Virtualkeys.h"
#include "TalkLayer.h"

USING_NS_CC;

Scene* GameSceneHouse::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSceneHouse::create();
	scene->addChild(layer);
	return scene;
}

bool GameSceneHouse::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameSceneHouse";
	_gameManager = GameManager::getInstance();

	_gameManager->setGameMap(GameMap::create("Maps/house.tmx"));
	_gameManager->setPlayer(Player_3::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	auto talkLayer = TalkLayer::create();
	_gameManager->setTalkLayer(talkLayer);
	addChild(talkLayer, 10);
	//_gameManager->setOperator(Virtualkeys::create());
	_gameManager->setGameScene(this);

	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	return true;
}