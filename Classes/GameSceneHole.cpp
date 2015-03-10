#include "GameSceneHole.h"
#include "Player_3.h"
#include "MapEnemy_3.h"
#include "Virtualkeys.h"
#include "RoundFight.h"

USING_NS_CC;

Scene* GameSceneHole::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSceneHole::create();
	scene->addChild(layer);
	return scene;
}

bool GameSceneHole::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameSceneHole";
	_gameManager = GameManager::getInstance();

	_gameManager->setGameMap(GameMap::create("Maps/hole.tmx"));
	_gameManager->setPlayer(Player_3::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	_gameManager->setGameScene(this);
	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	if (GameManager::getInstance()->getIsMusic()) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			_gameManager->_bgmusicName = "Music/bg_hole.OGG";
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_hole.OGG", true);
		#else
			_gameManager->_bgmusicName = "Music/bg_hole.mp3";
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_hole.mp3", true);
		#endif
	}
	_roundfight = nullptr;
	if (_gameManager->_hasholeround) {
		_roundfight = RoundFight::create("Others/bg_round2.png");
		_roundfight->setNoEnemyLayer(_gameMap->getLayer("noenemy"));
		addChild(_roundfight);
	}
	return true;
}

MapEnemy* GameSceneHole::createMapEnemy()
{
	return MapEnemy_3::create();
}