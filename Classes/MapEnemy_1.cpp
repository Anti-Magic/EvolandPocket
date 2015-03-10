#include "MapEnemy_1.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

MapEnemy_1* MapEnemy_1::create()
{
	MapEnemy_1 *enemy = new MapEnemy_1();
	string fileName = "Enemy/enemya_down1.png";
	if (enemy && enemy->init(fileName))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool MapEnemy_1::init(const string& fileName)
{
	if (!MapEnemy::init(fileName)) {
		return false;
	}
	_moveNameHalf = "1";
	initMoveAnimation();
	return true;
}

void MapEnemy_1::initMoveAnimation()
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
	frame1 = SpriteFrame::create("Enemy/enemya_up1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemya_up2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::UP) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemya_down1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemya_down2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::DOWN) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemya_left1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemya_left2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::LEFT) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}

	frames.clear();
	frame1 = SpriteFrame::create("Enemy/enemya_right1.png", frameRect);
	frame2 = SpriteFrame::create("Enemy/enemya_right2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay, 2);
	animationName = config->getEnemyMoveName(Tools::Direction::RIGHT) + _moveNameHalf;
	if (cache->getAnimation(animationName) == nullptr) {
		cache->addAnimation(animation, animationName);
	}
}