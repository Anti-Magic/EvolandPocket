#include "MapEnemy.h"
#include "GameConfig.h"
#include "GameManager.h"
#include "GameMap.h"

USING_NS_CC;
using namespace std;

bool MapEnemy::init()
{
	if (!Sprite::init()) {
		return false;
	}
	_faceto = Tools::Direction::DOWN;
	_timePerExecute = GameConfig::getInstance()->timePerMove * 4;
	schedule(schedule_selector(MapEnemy::execute), _timePerExecute);
	initMoveAnimation();
	return true;
}

bool MapEnemy::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	//initMoveAnimation();
	_faceto = Tools::Direction::DOWN;
	_timePerExecute = GameConfig::getInstance()->timePerMove * 4;
	schedule(schedule_selector(MapEnemy::execute), _timePerExecute);
	return true;
}

void MapEnemy::setPositionByTileCoord(const Vec2& tileCoord)
{
	auto gamemap = GameManager::getInstance()->getGameMap();
	if (gamemap == nullptr) {
		return;
	}
	Vec2 pos = Tools::tileCoordToPos(tileCoord);
	auto tileSize = gamemap->getTileSize();
	setPosition(pos.x + tileSize.width / 2,
		pos.y - tileSize.height / 2);
}

Tools::Direction MapEnemy::getFaceto()
{
	return _faceto;
}

void MapEnemy::setFaceto(Tools::Direction dir)
{
	_faceto = dir;
	string animationName = GameConfig::getInstance()->getEnemyMoveName(dir) + _moveNameHalf;
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	auto animate = Animate::create(animation);
	runAction(animate);
}

void MapEnemy::execute(float dlt)
{
	Vec2 step(0, 0);
	Vec2 tileCoord(0, 0);
	Vec2 tarTileCoord(0, 0);
	Tools::Direction dir = Tools::Direction::NONE;

	int index = 0;
	for (; index < 5; index++) {
		int randNum = rand() % 4 + 1;
		dir = (Tools::Direction)randNum;
		step = Tools::getStep(dir);
		Vec2 tarPos = getPosition() + step;
		tileCoord = Tools::posToTileCoord(tarPos);
		if (GameManager::getInstance()->getGameMap()->isPassage(tileCoord)) {
			tarTileCoord = tileCoord;
			break;
		}
	}
	setFaceto(dir);
	if (index < 5) {
		auto move = MoveBy::create(_timePerExecute, step);
		runAction(move);
	}
}

void MapEnemy::died()
{
	ParticleSystem* particle =
		ParticleSystemQuad::create("Particle/kill_enemy_1.plist");
	particle->setPosition(getPosition());
	particle->setAutoRemoveOnFinish(true);
	GameManager::getInstance()->getGameMap()->addChild(particle, 100);
	removeFromParentAndCleanup(true);
}