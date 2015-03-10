#include "RoundEnemy_2.h"

USING_NS_CC;

bool RoundEnemy_2::init()
{
	if (!RoundRole::initWithFile("Enemy/enemy_b1.png")) {
		return false;
	}
	_roleName = "enemy2";
	_hp = 16;
	_power = 6;
	auto size = getContentSize();
	_injuredSprite->setPosition(size.width / 2, size.height / 2);
	return true;
}

void RoundEnemy_2::initAttackAnimation()
{
	_attackName = "RoundEnemyAttack_2";
	auto attackAnimation = Animation::create();
	attackAnimation->addSpriteFrameWithFile("Enemy/enemy_b2.png");
	attackAnimation->addSpriteFrameWithFile("Enemy/enemy_b1.png");
	attackAnimation->setLoops(3);
	attackAnimation->setDelayPerUnit(0.05f);
	AnimationCache::getInstance()->addAnimation(attackAnimation, _attackName);
}

void RoundEnemy_2::initInjuredAnimation()
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

Action* RoundEnemy_2::getDeathAction()
{
	auto action = Sequence::createWithTwoActions(
		CallFunc::create([=]() {
			auto frame = SpriteFrame::create("Enemy/enemy_b2.png", Rect(0, 0, 64, 32));
			setSpriteFrame(frame);
		}),
		FadeOut::create(0.5f));
	return action;
}