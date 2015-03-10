#include "GameSceneWorld.h"
#include "Player_3.h"
#include "MapEnemy_1.h"
#include "Virtualkeys.h"
#include "TalkLayer.h"
#include "RoundFight.h"

USING_NS_CC;

Scene* GameSceneWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSceneWorld::create();
	scene->addChild(layer);
	return scene;
}

bool GameSceneWorld::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameSceneWorld";
	_gameManager = GameManager::getInstance();

	_gameManager->setGameMap(GameMap::create("Maps/world.tmx"));
	_gameManager->setPlayer(Player_3::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	auto talkLayer = TalkLayer::create();
	_gameManager->setTalkLayer(talkLayer);
	addChild(talkLayer, 10);
	//_gameManager->setOperator(Virtualkeys::create());
	_gameManager->setGameScene(this);

	initByManager(); //新建以后一定要初始化
	
	_gameLayer->setScale(80.0f / 16);

	_roundfight = nullptr;
	if (_gameManager->_hasround) {
		_roundfight = RoundFight::create("Others/bg_round1.png");
		_roundfight->setNoEnemyLayer(_gameMap->getLayer("noenemy"));
		addChild(_roundfight);
	}
	if (_gameManager->_hasmode7) {
		_gameLayer->runAction(RotateBy::create(0.5f, Vec3(-20, 0, 0)));
	}

	if (GameManager::getInstance()->getIsMusic()) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			_gameManager->_bgmusicName = "Music/bg_world.OGG";
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_world.OGG", true);
		#else
			_gameManager->_bgmusicName = "Music/bg_world.mp3";
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_world.mp3", true);
		#endif
	}
	return true;
}