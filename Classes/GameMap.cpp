#include "GameMap.h"
#include "Player.h"
#include "GameManager.h"
#include "GameConfig.h"

USING_NS_CC;

GameMap* GameMap::create(const std::string& tmxFile)
{
	GameMap *ret = new GameMap();
	if (ret->init(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GameMap::init(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile)) {
		return false;
	}
	_stopLayer = getLayer("stop");
	_grassLayer = getLayer("grass");
	_boxLayer = getLayer("box");
	_otherLayer = getLayer("other");
	_transLayer = getLayer("trans");
	_objectGroup = getObjectGroup("object");
	return true;
}

void GameMap::setPositionByTileCoord(const Vec2& tilecoord)
{
	setPosition(Tools::tileCoordToPos(tilecoord));
}

void GameMap::move(Tools::Direction dir)
{
	if (dir != Tools::Direction::NONE) {
		Vec2 step = -(Tools::getStep(dir));
		auto move = MoveBy::create(GameConfig::getInstance()->timePerMove, step);
		runAction(move);
	}
}

bool GameMap::isPassage(const Vec2& tileCoord)
{
	return !(_stopLayer->getTileGIDAt(tileCoord));
}

bool GameMap::isSaveArea(const Vec2& tileCoord)
{
	return (_otherLayer->getTileGIDAt(tileCoord)
		== GameConfig::getInstance()->GID_SaveArea);
}

bool GameMap::checkTrans(const Vec2& tileCoord)
{
	if (_transLayer->getTileGIDAt(tileCoord)
		//== GameConfig::getInstance()->GID_SaveArea);
		!= 0) {
		//获取CallBack
		std::string objName =
			"x" + Value((int)tileCoord.x).asString() +
			"y" + Value((int)tileCoord.y).asString();
		auto obj = _objectGroup->getObject(objName);
		GameManager::getInstance()->setCallBack(obj["CallBack"].asString());
		return true;
	}
	return false;
}

bool GameMap::checkCutGrass(const cocos2d::Vec2& tileCoord)
{
	if (_grassLayer->getTileGIDAt(tileCoord)) {
		_grassLayer->removeTileAt(tileCoord);
		_stopLayer->removeTileAt(tileCoord);
		return true;
	}
	return false;
}

void GameMap::removeBox(const cocos2d::Vec2& tileCoord)
{
	if (_boxLayer->getTileGIDAt(tileCoord) 
		== GameConfig::getInstance()->GID_Box_Close) {
		_boxLayer->removeTileAt(tileCoord);
		_stopLayer->removeTileAt(tileCoord);
	}
}

void GameMap::destroy(const cocos2d::Vec2& tileCoord)
{
	if (_otherLayer->getTileGIDAt(tileCoord)) {
		_otherLayer->removeTileAt(tileCoord);
		_stopLayer->removeTileAt(tileCoord);
	}
}

bool GameMap::checkOpenBox(const cocos2d::Vec2& tileCoord)
{
	auto config = GameConfig::getInstance();
	if (_boxLayer->getTileGIDAt(tileCoord) == config->GID_Box_Close) {
		_boxLayer->setTileGID(config->GID_Box_Open, tileCoord);
		_boxLayer->getTileAt(tileCoord)->runAction(FadeOut::create(0.3f));
		_stopLayer->removeTileAt(tileCoord);
		//开箱子的画面效果
		runAction(JumpBy::create(0.15f, Vec2(0, 0), 2.5f, 1));
		//获取CallBack
		std::string objName = 
			"x" + Value((int)tileCoord.x).asString() + 
			"y" + Value((int)tileCoord.y).asString();
		auto obj = _objectGroup->getObject(objName);
		GameManager::getInstance()->setCallBack(obj["CallBack"].asString());
		return true;
	}
	return false;
}