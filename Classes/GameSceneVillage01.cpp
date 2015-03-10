#include "GameSceneVillage01.h"
#include "Player_3.h"
#include "Virtualkeys.h"
#include "MapEnemy_1.h"
#include "TalkLayer.h"

USING_NS_CC;

Scene* GameSceneVillage01::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSceneVillage01::create();
	scene->addChild(layer);
	return scene;
}

bool GameSceneVillage01::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameSceneVillage01";
	_gameManager = GameManager::getInstance();
	_gameManager->setGameMap(GameMap::create("Maps/village01.tmx"));
	_gameManager->setPlayer(Player_3::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	_gameManager->setGameScene(this);
	auto talkLayer = TalkLayer::create();
	_gameManager->setTalkLayer(talkLayer);
	addChild(talkLayer, 10);
	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	_npcLayer = _gameMap->getLayer("npc");

	if (GameManager::getInstance()->getIsMusic()) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_village.OGG", true);
		#else
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg_village.mp3", true);
		#endif
	}

	return true;
}

void GameSceneVillage01::moveResponse(float dlt)
{
	auto dir = _operator->getDirection();
	if (!_gameManager->_isMoving) {
		if (_player->move(dir)) {
			_gameMap->move(dir);
		}
	}
	else {
		Vec2 step = Tools::getStep(dir);
		Vec2 tarPos = _player->getPosition() + step;
		Vec2 tarTileCoord = Tools::posToTileCoord(tarPos);
		if (_npcLayer->getTileGIDAt(tarTileCoord)) {
			GameManager::getInstance()->getTalkLayer()->talk("sorry");
		}
	}
	if (_gameManager->_isMoving) {
		_gameManager->addMoveTimer(dlt);
	}
}