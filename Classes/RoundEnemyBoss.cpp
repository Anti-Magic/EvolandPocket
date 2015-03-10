#include "RoundEnemyBoss.h"

USING_NS_CC;

bool RoundEnemyBoss::init()
{
	if (!RoundRole::initWithFile("Enemy/boss_1.png")) {
		return false;
	}
	_roleName = "boss";
	_hp = 100;
	_power = 4;
	auto size = getContentSize();
	_injuredSprite->setPosition(size.width / 2, size.height / 2);
	initBossAnimation();
	return true;
}

void RoundEnemyBoss::initBossAnimation()
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Enemy/boss_1.png");
	animation->addSpriteFrameWithFile("Enemy/boss_2.png");
	animation->addSpriteFrameWithFile("Enemy/boss_3.png");
	animation->addSpriteFrameWithFile("Enemy/boss_4.png");
	animation->addSpriteFrameWithFile("Enemy/boss_5.png");
	animation->addSpriteFrameWithFile("Enemy/boss_6.png");
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.05f);
	AnimationCache::getInstance()->addAnimation(animation, "bossAnimation");
}

void RoundEnemyBoss::initAttackAnimation()
{
	_attackName = "RoundBossAttack";
	if (AnimationCache::getInstance()->getAnimation(_attackName) == nullptr) {
		auto attackAnimation = Animation::create();
		attackAnimation->addSpriteFrameWithFile("Enemy/boss_7.png");
		attackAnimation->addSpriteFrameWithFile("Enemy/boss_1.png");
		attackAnimation->setLoops(3);
		attackAnimation->setDelayPerUnit(0.05f);
		AnimationCache::getInstance()->addAnimation(attackAnimation, _attackName);
	}
}

void RoundEnemyBoss::initInjuredAnimation()
{
	_injuredName = "RoundEnemyInjured";
	if (AnimationCache::getInstance()->getAnimation(_injuredName) == nullptr) {
		auto injuredAnimation = Animation::create();
		injuredAnimation->addSpriteFrameWithFile("Others/att21.png");
		injuredAnimation->addSpriteFrameWithFile("Others/att22.png");
		injuredAnimation->addSpriteFrameWithFile("Others/att23.png");
		injuredAnimation->setLoops(1);
		injuredAnimation->setDelayPerUnit(0.08f);
		AnimationCache::getInstance()
			->addAnimation(injuredAnimation, _injuredName);
	}
}

Action* RoundEnemyBoss::getDeathAction()
{
	auto action = Sequence::createWithTwoActions(
		CallFunc::create([=]() {
		auto frame = SpriteFrame::create("Enemy/boss_7.png", Rect(0, 0, 90, 92));
		setSpriteFrame(frame);
	}),
		FadeOut::create(0.5f));
	return action;
}