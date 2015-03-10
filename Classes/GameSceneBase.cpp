#include "GameSceneBase.h"
#include "PopDialog.h"

USING_NS_CC;

bool GameSceneBase::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto dialog = PopDialog::create();
	addChild(dialog, 10000);
	scheduleUpdate();
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_BACKSPACE || code == EventKeyboard::KeyCode::KEY_ESCAPE) {
			dialog->pop("readyquitgame", "readyQuitGame");
		}
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}

void GameSceneBase::initByManager()
{
	_gameManager->setOperator(DataService::getInstance()->createCurOperator());
	_operator = _gameManager->getOperator();
	addChild(_operator, 1000);

	_player = _gameManager->getPlayer();
	_gameMap = _gameManager->getGameMap();
	_gameMap->setAnchorPoint(Vec2::ZERO);

	_gameLayer = Layer::create();
	_gameLayer->addChild(_gameMap, 1);
	_gameLayer->setAnchorPoint(Vec2::ZERO);
	addChild(_gameLayer, 1);

	_tipsLayer = _gameManager->getTipsLayer();
	addChild(_tipsLayer, 10);
}

void GameSceneBase::update(float dlt)
{
	moveResponse(dlt);
	triggerResponse(dlt);
}

void GameSceneBase::fillData(SceneData& data)
{
	_player->setFaceto(data.playerFaceto);
	_player->setPosition(data.playerPos);
	_gameMap->setPosition(data.gameMapPos);
	for (auto p : data.cutgrassPos) {
		_gameMap->checkCutGrass(p);
	}
	for (auto p : data.openboxPos) {
		_gameMap->removeBox(p);
	}
	for (auto p : data.destroyPos) {
		_gameMap->destroy(p);
	}
	for (int i = 0; i < data.enemyPos.size(); i++) {
		auto tileSize = _gameMap->getTileSize();
		auto enemy = createMapEnemy();
		enemy->setPositionByTileCoord(Tools::posToTileCoord(data.enemyPos[i]));
		enemy->setFaceto(data.enemyFaceto[i]);
		_gameManager->addMapEnemy(enemy);
	}
	/*
	GameManager::getInstance()->getGameScene()
		->getEventDispatcher()->removeAllEventListeners();
	auto opOld = GameManager::getInstance()->getOperator();
	opOld->reset();
	opOld->removeFromParentAndCleanup(true);
	GameManager::getInstance()->setOperator(data.op);
	_operator = data.op;
	addChild(_operator, 1000);*/
}

const std::string& GameSceneBase::getClassName()
{
	return _className;
}

void GameSceneBase::moveResponse(float dlt)
{
	if (!_gameManager->_isMoving) {
		auto dir = _operator->getDirection();
		if (_player->move(dir)) {
			_gameMap->move(dir);
		}
	}
	if (_gameManager->_isMoving) {
		_gameManager->addMoveTimer(dlt);
	}
}

void GameSceneBase::triggerResponse(float dlt)
{
	if (!_gameManager->_isTriggering) {
		_player->attack(_operator->isTrigger());
	}
	if (_gameManager->_isTriggering) {
		_gameManager->addTriggerTimer(dlt);
	}
}

MapEnemy* GameSceneBase::createMapEnemy()
{
	return nullptr;
}

void GameSceneBase::setOperator(OperatorBase* op)
{
	_operator = op;
	addChild(_operator, 1000);
}

Layer* GameSceneBase::getGameLayer()
{
	return _gameLayer;
}