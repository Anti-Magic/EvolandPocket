#include "Player_1.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

Player_1* Player_1::create()
{
	Player_1 *player = new Player_1();
	if (player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player_1::init()
{
	string fileName = "Roles/down_a1.png";
	if (!Player::init(fileName)) {
		return false;
	}
	initMoveAnimation();
	initFacetoFrame();
	initAttackAnimation();
	return true;
}

void Player_1::initMoveAnimation()
{
	Vector<SpriteFrame*> frames;
	Rect frameRect(0, 0, 12, 16);
	float delay = GameConfig::getInstance()->timePerMove / 2; //frames.size();
	auto cache = AnimationCache::getInstance();
	auto config = GameConfig::getInstance();
	SpriteFrame* frame1 = nullptr;
	SpriteFrame* frame2 = nullptr;
	Animation* animation = nullptr;
	string animationName;

	frames.clear();
	frame1 = SpriteFrame::create("Roles/up_a1.png", frameRect);
	frame2 = SpriteFrame::create("Roles/up_a2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerMoveName(Tools::Direction::UP);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	frames.clear();
	frame1 = SpriteFrame::create("Roles/down_a1.png", frameRect);
	frame2 = SpriteFrame::create("Roles/down_a2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerMoveName(Tools::Direction::DOWN);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	frames.clear();
	frame1 = SpriteFrame::create("Roles/left_a1.png", frameRect);
	frame2 = SpriteFrame::create("Roles/left_a2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerMoveName(Tools::Direction::LEFT);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	frames.clear();
	frame1 = SpriteFrame::create("Roles/right_a1.png", frameRect);
	frame2 = SpriteFrame::create("Roles/right_a2.png", frameRect);
	frames.pushBack(frame1);
	frames.pushBack(frame2);
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerMoveName(Tools::Direction::RIGHT);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);
}

void Player_1::initFacetoFrame()
{
	Rect frameRect(0, 0, 12, 16);
	auto config = GameConfig::getInstance();
	auto cache = SpriteFrameCache::getInstance();
	SpriteFrame* frame = nullptr;
	string name;

	frame = SpriteFrame::create("Roles/up_a1.png", frameRect);
	name = config->getPlayerFacetoName(Tools::Direction::UP);
	if (cache->getSpriteFrameByName(name) != nullptr) {
		cache->removeSpriteFrameByName(name);
	}
	cache->addSpriteFrame(frame, name);

	frame = SpriteFrame::create("Roles/down_a1.png", frameRect);
	name = config->getPlayerFacetoName(Tools::Direction::DOWN);
	if (cache->getSpriteFrameByName(name) != nullptr) {
		cache->removeSpriteFrameByName(name);
	}
	cache->addSpriteFrame(frame, name);

	frame = SpriteFrame::create("Roles/left_a1.png", frameRect);
	name = config->getPlayerFacetoName(Tools::Direction::LEFT);
	if (cache->getSpriteFrameByName(name) != nullptr) {
		cache->removeSpriteFrameByName(name);
	}
	cache->addSpriteFrame(frame, name);

	frame = SpriteFrame::create("Roles/right_a1.png", frameRect);
	name = config->getPlayerFacetoName(Tools::Direction::RIGHT);
	if (cache->getSpriteFrameByName(name) != nullptr) {
		cache->removeSpriteFrameByName(name);
	}
	cache->addSpriteFrame(frame, name);
}

void Player_1::initAttackAnimation()
{
	Vector<SpriteFrame*> frames;
	float delay = GameConfig::getInstance()->timePerMove / 4;
	auto cache = AnimationCache::getInstance();
	auto config = GameConfig::getInstance();
	Animation* animation = nullptr;
	string animationName;
	Rect frameRect(0, 0, 12, 16);

	Rect udFrameRect(0, 0, 12, 24);
	frames.clear();
	frames.pushBack(SpriteFrame::create("Attack/up_a1.png", udFrameRect));
	frames.pushBack(SpriteFrame::create("Attack/up_a2.png", udFrameRect));
	frames.pushBack(SpriteFrame::create("Roles/up_a1.png", frameRect));
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerAttackName(Tools::Direction::UP);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	frames.clear();
	frames.pushBack(SpriteFrame::create("Attack/down_a1.png", udFrameRect));
	frames.pushBack(SpriteFrame::create("Attack/down_a2.png", udFrameRect));
	frames.pushBack(SpriteFrame::create("Roles/down_a1.png", frameRect));
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerAttackName(Tools::Direction::DOWN);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	Rect lrFrameRect(0, 0, 22, 15);
	frames.clear();
	frames.pushBack(SpriteFrame::create("Attack/left_a1.png", lrFrameRect));
	frames.pushBack(SpriteFrame::create("Attack/left_a2.png", lrFrameRect));
	frames.pushBack(SpriteFrame::create("Roles/left_a1.png", frameRect));
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerAttackName(Tools::Direction::LEFT);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);

	frames.clear();
	frames.pushBack(SpriteFrame::create("Attack/right_a1.png", lrFrameRect));
	frames.pushBack(SpriteFrame::create("Attack/right_a2.png", lrFrameRect));
	frames.pushBack(SpriteFrame::create("Roles/right_a1.png", frameRect));
	animation = Animation::createWithSpriteFrames(frames, delay);
	animationName = config->getPlayerAttackName(Tools::Direction::RIGHT);
	if (cache->getAnimation(animationName) != nullptr) {
		cache->removeAnimation(animationName);
	}
	cache->addAnimation(animation, animationName);
}