#include "MapEnemy_3.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

MapEnemy_3* MapEnemy_3::create()
{
	MapEnemy_3 *enemy = new MapEnemy_3();
	string fileName = "Enemy/enemyc_down1.png";
	if (enemy && enemy->init(fileName))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool MapEnemy_3::init(const string& fileName)
{
	if (!MapEnemy::init(fileName)) {
		return false;
	}
	_moveNameHalf = "3";
	initMoveAnimation();
	return true;
}

void MapEnemy_3::initMoveAnimation()
{
	Vector<SpriteFrame*> frames;
	Rect frameRect(0, 0, 16, 16);
	float delay = _timePerExecute / 4; //frames.size() * 2;
	auto cache = AnimationCache::getInstance();
	auto config = GameConfig::getInstance();
	SpriteFrame* frame1 = nullptr;
	SpriteFrame* frame2 = nullptr;
	Animation* animation = nullptr;
	string animationName;

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemyc_up1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemyc_up2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::UP) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemyc_down1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemyc_down2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::DOWN) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemyc_left1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemyc_left2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::LEFT) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemyc_right1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemyc_right2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::RIGHT) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}
}