#include "RoundFight.h"
#include "GameManager.h"
#include "RoundFightScene.h"
#include "OperatorBase.h"
#include "RoundEnemy_1.h"
#include "RoundEnemy_2.h"
#include "RoundPlayer_1.h"
#include "RoundPlayer_2.h"
#include "GameMap.h"
#include "Player.h"

USING_NS_CC;

RoundFight* RoundFight::create(const std::string& bgName)
{
	RoundFight *pRet = new RoundFight();
	if (pRet && pRet->init(bgName)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool RoundFight::init(const std::string& bgName)
{
	if (!Node::init()) {
		return false;
	}
	_bgName = bgName;
	_noEnemyLayer = nullptr;
	_gameManager = GameManager::getInstance();
	_ready = false;
	scheduleUpdate();
	return true;
}

void RoundFight::update(float dlt)
{
	if (_gameManager->_isMoving) {
		_ready = true;
	}
	if (_ready && !_gameManager->_isMoving) {
		_ready = false;
		auto tileCoord = Tools::posToTileCoord(
			GameManager::getInstance()->getPlayer()->getPosition());
		if (_noEnemyLayer != nullptr && _noEnemyLayer->getTileGIDAt(tileCoord) != 0) {
			return;
		}
		if (checkFight()) {
			GameManager::getInstance()->getOperator()->reset();
			auto scene = RoundFightScene::createScene(getEnemys(), getPlayers(), _bgName);
			Director::getInstance()->pushScene(
				TransitionSplitRows::create(0.5f, scene));
		}
	}
}

void RoundFight::setNoEnemyLayer(cocos2d::TMXLayer* layer)
{
	_noEnemyLayer = layer;
}

bool RoundFight::checkFight()
{
	auto half = RAND_MAX / 2;
	if (rand() < half && rand() < half && rand() < half && rand() < half) {
		return true;
	}
	return false;
}

std::vector<RoundRole*> RoundFight::getEnemys()
{
	std::vector<RoundRole*> enemys;
	int count = rand() % 3 + 1;
	for (int i = 0; i < count; i++) {
		int type = rand() % 2 + 1;
		if (type == 1) {
			enemys.push_back(RoundEnemy_1::create());
		}
		else if (type == 2) {
			enemys.push_back(RoundEnemy_2::create());
		}
	}
	return enemys;
}

std::vector<RoundRole*> RoundFight::getPlayers()
{
	std::vector<RoundRole*> players;
	auto player1 = RoundPlayer_1::create();
	players.push_back(player1);
	if (GameManager::getInstance()->_hasplayer2) {
		auto player2 = RoundPlayer_2::create();
		players.push_back(player2);
	}
	return players;
}