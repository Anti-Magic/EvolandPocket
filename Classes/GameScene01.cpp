#include "GameScene01.h"
#include "Player_1.h"
#include "Player_2.h"
#include "MapEnemy_1.h"
#include "Virtualkeys.h"

#include "GameScene02.h"
#include "DataService.h"

USING_NS_CC;

Scene* GameScene01::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene01::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene01::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameScene01";
	_gameManager = GameManager::getInstance();

	//一定要先新建好各种组件，然后再设置属性
	_gameManager->setGameMap(GameMap::create("Maps/map01.tmx"));
	_gameManager->setPlayer(Player_1::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	_gameManager->setGameScene(this);

	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	_isroll = true;
	_scrollLayer = _gameMap->getLayer("trans");
	GID_Scroll_LR = 122;
	GID_Scroll_UD = 121;

	return true;
}

void GameScene01::update(float dlt)
{
	if (_isroll) {
		moveResponse(dlt);
	}
	else {
		moveResponse2(dlt);
	}
	triggerResponse(dlt);
}

MapEnemy* GameScene01::createMapEnemy()
{
	return MapEnemy_1::create();
}

void GameScene01::moveResponse2(float dlt)
{
	if (!_gameManager->_isMoving) {
		auto playerTileCoord = Tools::posToTileCoord(_player->getPosition());
		auto scrollgid = _scrollLayer->getTileGIDAt(playerTileCoord);
		if (scrollgid == GID_Scroll_LR) {
			if (_player->getFaceto() == Tools::Direction::LEFT) {
				for (int i = 0; i < 8; i++) {
					_gameMap->move(Tools::Direction::LEFT);
				}
				_player->move(_player->getFaceto());
			}
			else if (_player->getFaceto() == Tools::Direction::RIGHT) {
				for (int i = 0; i < 8; i++) {
					_gameMap->move(Tools::Direction::RIGHT);
				}
				_player->move(_player->getFaceto());
			}
		}
		else if (scrollgid == GID_Scroll_UD) {
			if (_player->getFaceto() == Tools::Direction::UP) {
				for (int i = 0; i < 5; i++) {
					_gameMap->move(Tools::Direction::UP);
				}
				_player->move(_player->getFaceto());
			}
			else if (_player->getFaceto() == Tools::Direction::DOWN) {
				for (int i = 0; i < 5; i++) {
					_gameMap->move(Tools::Direction::DOWN);
				}
				_player->move(_player->getFaceto());
			}
		}
		else {
			if (!_player->move(_operator->getDirection())
				&& _gameManager->_isMoving) {
				/*BoxCallBack::getInstance()
					->executeBoxCallBack(_gameManager->getCallBack());*/
			}
		}
	}
	if (_gameManager->_isMoving) {
		_gameManager->addMoveTimer(dlt);
	}
}