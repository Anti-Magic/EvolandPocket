#include "RoundPlayer_1.h"
#include "GameConfig.h"

USING_NS_CC;

bool RoundPlayer_1::init()
{
	if (!RoundRole::initWithFile("Roles/left_c1.png")) {
		return false;
	}
	_roleName = "me";
	_hp = 100;
	_power = 12;
	auto size = getContentSize();
	_injuredSprite->setPosition(size.width / 2, size.height / 2);
	return true;
}

void RoundPlayer_1::initAttackAnimation()
{
	_attackName = GameConfig::getInstance()->getPlayerAttackName(Tools::Direction::LEFT);
}

void RoundPlayer_1::initInjuredAnimation()
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

Action* RoundPlayer_1::getDeathAction()
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Roles/player1_death.png");
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}