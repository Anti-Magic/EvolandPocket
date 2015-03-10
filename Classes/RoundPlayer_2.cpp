#include "RoundPlayer_2.h"

USING_NS_CC;

bool RoundPlayer_2::init()
{
	if (!RoundRole::initWithFile("Roles/girl_1.png")) {
		return false;
	}
	_roleName = "girl";
	_hp = 100;
	_power = 5;
	auto size = getContentSize();
	_injuredSprite->setPosition(size.width / 2, size.height / 2);
	return true;
}

void RoundPlayer_2::initAttackAnimation()
{
	_attackName = "RoundPlayerAttack_2";
	auto attackAnimation = Animation::create();
	attackAnimation->addSpriteFrameWithFile("Roles/girl_2.png");
	attackAnimation->addSpriteFrameWithFile("Roles/girl_3.png");
	attackAnimation->addSpriteFrameWithFile("Roles/girl_4.png");
	attackAnimation->addSpriteFrameWithFile("Roles/girl_1.png");
	attackAnimation->setLoops(1);
	attackAnimation->setDelayPerUnit(0.07f);
	AnimationCache::getInstance()->addAnimation(attackAnimation, _attackName);
}

void RoundPlayer_2::initInjuredAnimation()
{
	_injuredName = "RoundPlayerInjured";
	if (AnimationCache::getInstance()->getAnimation(_injuredName) == nullptr) {
		auto injuredAnimation = Animation::create();
		injuredAnimation->addSpriteFrameWithFile("Others/att11.png");
		injuredAnimation->addSpriteFrameWithFile("Others/att12.png");
		injuredAnimation->addSpriteFrameWithFile("Others/att13.png");
		injuredAnimation->setLoops(1);
		injuredAnimation->setDelayPerUnit(0.1f);
		AnimationCache::getInstance()
			->addAnimation(injuredAnimation, _injuredName);
	}
}

Action* RoundPlayer_2::getDeathAction()
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Roles/player2_death.png");
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}