#include "GameScene03.h"
#include "Player_3.h"
#include "MapEnemy_3.h"
#include "Virtualkeys.h"

#include "Joystick.h"

USING_NS_CC;

Scene* GameScene03::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene03::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene03::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameScene03";
	_gameManager = GameManager::getInstance();

	_gameManager->setGameMap(GameMap::create("Maps/map03.tmx"));
	_gameManager->setPlayer(Player_3::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	_gameManager->setGameScene(this);
	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	if (GameManager::getInstance()->getIsMusic()) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg1.OGG", true);
		#else
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg1.mp3", true);
		#endif
	}
	return true;
}

MapEnemy* GameScene03::createMapEnemy()
{
	return MapEnemy_3::create();
}