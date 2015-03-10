#include "RoundEnemy_1.h"

USING_NS_CC;

bool RoundEnemy_1::init()
{
	if (!RoundRole::initWithFile("Enemy/enemy_a1.png")) {
		return false;
	}
	_roleName = "enemy1";
	_hp = 11;
	_power = 4;
	auto size = getContentSize();
	_injuredSprite->setPosition(size.width / 2, size.height / 2);
	return true;
}

void RoundEnemy_1::initAttackAnimation()
{
	_attackName = "RoundEnemyAttack_1";
	if (AnimationCache::getInstance()->getAnimation(_attackName) == nullptr) {
		auto attackAnimation = Animation::create();
		attackAnimation->addSpriteFrameWithFile("Enemy/enemy_a2.png");
		attackAnimation->addSpriteFrameWithFile("Enemy/enemy_a1.png");
		attackAnimation->setLoops(3);
		attackAnimation->setDelayPerUnit(0.05f);
		AnimationCache::getInstance()->addAnimation(attackAnimation, _attackName);
	}
}

void RoundEnemy_1::initInjuredAnimation()
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

Action* RoundEnemy_1::getDeathAction()
{
	auto action = Sequence::createWithTwoActions(
		CallFunc::create([=]() {
			auto frame = SpriteFrame::create("Enemy/enemy_a2.png", Rect(0, 0, 42, 32));
			setSpriteFrame(frame);
		}),
		FadeOut::create(0.5f));
	return action;
}