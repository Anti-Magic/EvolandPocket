#include "GameManager.h"
#include "GameConfig.h"
#include "Player.h"
#include "GameMap.h"
#include "MapEnemy.h"
#include "OperatorBase.h"
#include "DataService.h"
#include "GameSceneBase.h"
#include "SimpleAudioEngine.h"
#include "MapCallBack.h"
#include "TalkLayer.h"
#include "GameOverScene.h"

USING_NS_CC;

GameManager GameManager::_instance;

GameManager::GameManager()
{
	gameInit();
	/*_player = nullptr;
	_gamemap = nullptr;
	_operator = nullptr;
	gameReset(false);
	_isSound = false;
	_isMusic = false;
	_hasplayer2 = false;
	_hasmode7 = false;
	_hasround = false;
	_talkLayer = nullptr;
	_hp1 = 100;
	_hp2 = 100;*/
}

GameManager* GameManager::getInstance()
{
	return &_instance;
}

Player* GameManager::getPlayer()
{
	return _player;
}

void GameManager::setPlayer(Player* player)
{
	_player = player;
	if (_gamemap != nullptr) {
		_gamemap->addChild(_player, 6);
	}
}

GameMap* GameManager::getGameMap()
{
	return _gamemap;
}

void GameManager::setGameMap(GameMap* gamemap)
{
	_gamemap = gamemap;
}

const std::vector<MapEnemy*>& GameManager::getMapEnemys() const
{
	return _mapEnemys;
}

void GameManager::setMapEnemys(std::vector<MapEnemy*>& enemys)
{
	_mapEnemys.clear();
	if (enemys.size() > 0) {
		for (auto e : enemys) {
			_mapEnemys.push_back(e);
			_gamemap->addChild(e, 100);
		}
	}
}

void GameManager::addMapEnemy(MapEnemy* mapEnemy)
{
	_mapEnemys.push_back(mapEnemy);
	_gamemap->addChild(mapEnemy, 100);
}

OperatorBase* GameManager::getOperator()
{
	return _operator;
}

void GameManager::setOperator(OperatorBase* op)
{
	_operator = op;
}

std::string GameManager::getCallBack()
{
	auto res = _callBack;
	_callBack = "";
	return res;
}

void GameManager::setCallBack(const std::string& callback)
{
	_callBack = callback;
}

GameSceneBase* GameManager::getGameScene()
{
	return _gameScene;
}

void GameManager::setGameScene(GameSceneBase* gameScene)
{
	_gameScene = gameScene;
}

TipsLayer* GameManager::getTipsLayer()
{
	return _tipsLayer;
}

void GameManager::setTipsLayer(TipsLayer* tipsLayer)
{
	_tipsLayer = tipsLayer;
}

TalkLayer* GameManager::getTalkLayer()
{
	return _talkLayer;
}

void GameManager::setTalkLayer(TalkLayer* talkLayer)
{
	_talkLayer = talkLayer;
}

bool GameManager::getIsSound()
{
	return _isSound;
}

void GameManager::setIsSound(bool sound)
{
	_isSound = sound;
}

bool GameManager::getIsMusic()
{
	return _isMusic;
}

void GameManager::setIsMusic(bool music)
{
	_isMusic = music;
}

void GameManager::gamePause(Node* target)
{
	if (target != nullptr) {
		auto children = target->getChildren();
		if (children.size() > 0) {
			for (auto child : children) {
				gamePause(child);
			}
		}
		target->pause();
	}
}

void GameManager::gameResume(cocos2d::Node* target)
{
	if (target != nullptr) {
		auto children = target->getChildren();
		if (children.size() > 0) {
			for (auto child : children) {
				gameResume(child);
			}
		}
		target->resume();
	}
}

void GameManager::gameReset(bool cleanupEnemys)
{
	if (_operator != nullptr) {
		_operator->reset();
	}
	_isMoving = false;
	_isTriggering = false;
	_moveTimer = 0.0f;
	_triggerTimer = 0.0f;
	_callBack = "";
	if (cleanupEnemys) {
		if (_mapEnemys.size() > 0) {
			for (auto e : _mapEnemys) {
				e->removeFromParentAndCleanup(true);
			}
		}
	}
	_mapEnemys.clear();
}

void GameManager::gameInit()
{
	_player = nullptr;
	_gamemap = nullptr;
	_operator = nullptr;
	gameReset(false);
	_isSound = false;
	_isMusic = false;
	_boxCount = 0;
	_hasplayer2 = false;
	_hasmode7 = false;
	_hasround = false;
	_hasholeround = true;
	_talkLayer = nullptr;
	_hp1 = 100;
	_hp2 = 100;
}

void GameManager::addMoveTimer(float dlt)
{
	_moveTimer += dlt;
	if (_moveTimer >= GameConfig::getInstance()->timePerMove) {
		_isMoving = false;
		_moveTimer = 0.0f;
	}
}

void GameManager::addTriggerTimer(float dlt)
{
	_triggerTimer += dlt;
	if (_triggerTimer >= GameConfig::getInstance()->timePerAttack) {
		_isTriggering = false;
		_triggerTimer = 0.0f;
	}
}

void GameManager::killEnemy()
{
	Vec2 curTileCoord = Tools::posToTileCoord(
		_player->getPosition());
	Vec2 frontTileCoord = Tools::posToTileCoord(
		_player->getPosition() + Tools::getStep(_player->getFaceto()));

	for (auto it = _mapEnemys.begin(); it != _mapEnemys.end(); it++) {
		auto enemyTileCoord = Tools::posToTileCoord((*it)->getPosition());
		if (enemyTileCoord == frontTileCoord || enemyTileCoord == curTileCoord) {
			(*it)->died();
			_mapEnemys.erase(it);
			if (_isSound) {
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CocosDenshion::SimpleAudioEngine::getInstance()
						->playEffect("Music/killenemy.OGG", false);
				#else
					CocosDenshion::SimpleAudioEngine::getInstance()
						->playEffect("Music/killenemy.mp3", false);
				#endif
			}

			break;
		}
	}
}

void GameManager::cutGrass()
{
	Vec2 frontPos = _player->getPosition() 
		+ Tools::getStep(_player->getFaceto());
	Vec2 frontTileCoord = Tools::posToTileCoord(frontPos);
	if (_gamemap->checkCutGrass(frontTileCoord)) {
		DataService::getInstance()->cutGrass(frontTileCoord);
		ParticleSystem* particle = 
			ParticleSystemQuad::create("Particle/cut_grass_1.plist");
		particle->setPosition(frontPos);
		particle->setAutoRemoveOnFinish(true);
		_gamemap->addChild(particle, 100);
		if (_isSound) {
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				CocosDenshion::SimpleAudioEngine::getInstance()
					->playEffect("Music/cutgrass.OGG", false);
			#else
				CocosDenshion::SimpleAudioEngine::getInstance()
					->playEffect("Music/cutgrass.mp3", false);
			#endif
		}
	}
}

bool GameManager::checkOpenBox(const cocos2d::Vec2& tileCoord)
{
	if (_gamemap->checkOpenBox(tileCoord)) {
		_boxCount++;
		DataService::getInstance()->openBox(tileCoord);
		MapCallBack::getInstance()->executeBoxCallBack(_callBack);
		if (_isSound) {
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				CocosDenshion::SimpleAudioEngine::getInstance()
					->playEffect("Music/openbox.OGG", false);
			#else
				CocosDenshion::SimpleAudioEngine::getInstance()
					->playEffect("Music/openbox.mp3", false);
			#endif
		}
		return true;
	}
	return false;
}

void GameManager::checkSaveGame(const cocos2d::Vec2& tileCoord)
{
	if (_gamemap->isSaveArea(tileCoord)) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playEffect("Music/save.OGG", false);
		#else
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playEffect("Music/save.mp3", false);
		#endif
		DataService::getInstance()->saveRecord(_gameScene->getClassName());
		_tipsLayer->makeTips("gameSave");
	}
}

void GameManager::checkTransMap(const cocos2d::Vec2& tileCoord)
{
	if (_gamemap->checkTrans(tileCoord)) {
		MapCallBack::getInstance()
			->executeTransCallBack(_callBack);
	}
}

void GameManager::checkPlayerDied()
{
	if (_mapEnemys.size() > 0) {
		for (auto e : _mapEnemys) {
			auto enemyPos = e->getPosition();
			auto playerPos = _player->getPosition();
			if (std::abs(enemyPos.x - playerPos.x) <= 9 && std::abs(enemyPos.y - playerPos.y) <= 9) {
				//log("%s....%d", "die", rand());
				_player->setVisible(false);
				ParticleSystem* particle =
					ParticleSystemQuad::create("Particle/kill_enemy_1.plist");
				particle->setPosition(_player->getPosition());
				particle->setAutoRemoveOnFinish(true);
				_gamemap->addChild(particle, 100);
				_gameScene->runAction(Sequence::createWithTwoActions(
					DelayTime::create(1.0f),
					CallFunc::create([]() {
					auto scene = GameOverScene::createScene();
					Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
				})));
				for (auto e : _mapEnemys) {
					e->pause();
				}
				_gameScene->unscheduleUpdate();
				_operator->getEventDispatcher()->removeEventListenersForTarget(_operator);
				gameReset(false);
				DataService::getInstance()->reset();
				break;
			}
		}
	}
}