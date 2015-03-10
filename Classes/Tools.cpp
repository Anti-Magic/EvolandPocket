#include "Tools.h"
#include "GameManager.h"
#include "GameMap.h"

USING_NS_CC;

std::string Tools::dirToString(Direction dir)
{
	switch (dir) {
	case Direction::NONE:
		return "NONE";
	case Direction::UP:
		return "UP";
	case Direction::DOWN:
		return "DOWN";
	case Direction::LEFT:
		return "LEFT";
	case Direction::RIGHT:
		return "RIGHT";
	}
	return "";
}

Vec2 Tools::getStep(Direction dir)
{
	auto tileSize = GameManager::getInstance()
		->getGameMap()->getTileSize();
	switch (dir) {
	case Direction::NONE:
		return Vec2::ZERO;
	case Direction::UP:
		return Vec2(0, tileSize.height);
	case Direction::DOWN:
		return Vec2(0, -tileSize.height);
	case Direction::LEFT:
		return Vec2(-tileSize.width, 0);
	case Direction::RIGHT:
		return Vec2(tileSize.width, 0);
	}
	return Vec2::ZERO;
}

Vec2 Tools::tileCoordToPos(const Vec2& tileCoord)
{
	auto tileSize = GameManager::getInstance()
		->getGameMap()->getTileSize();
	auto mapSize = GameManager::getInstance()
		->getGameMap()->getMapSize();
	float posx = tileCoord.x * tileSize.width;
	float posy = (mapSize.height - tileCoord.y) * tileSize.height;
	return Vec2(posx, posy);
}

Vec2 Tools::posToTileCoord(const Vec2& pos)
{
	auto tileMap = GameManager::getInstance()->getGameMap();
	Size tileSize = tileMap->getTileSize();
	float mapHeight = tileMap->getMapSize().height * tileSize.height;
	int newx = pos.x / tileSize.width;
	int newy = (mapHeight - pos.y) / tileSize.height;
	return Vec2(newx, newy);
}