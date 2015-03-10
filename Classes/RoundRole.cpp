#include "RoundRole.h"

USING_NS_CC;

void RoundRole::attack(Tools::Direction dir)
{
	MoveBy* move = nullptr;
	if (dir == Tools::Direction::LEFT) {
		move = MoveBy::create(0.1f, Vec2(-150, 0));
	}
	else if (dir == Tools::Direction::RIGHT) {
		move = MoveBy::create(0.1f, Vec2(150, 0));
	}
	auto animation = AnimationCache::getInstance()->getAnimation(_attackName);
	runAction(Sequence::create(
		move,
		Animate::create(animation),
		move->reverse(),
		nullptr));
}

bool RoundRole::injured(int power)
{
	auto animation = AnimationCache::getInstance()->getAnimation(_injuredName);
	_injuredSprite->setVisible(true);
	_injuredSprite->runAction(Sequence::createWithTwoActions(
		Animate::create(animation),
		CallFunc::create([=]() {
		_injuredSprite->setVisible(false);
	})));
	runAction(JumpBy::create(0.2f, Vec2(0, 0), 8, 2));
	_hp -= power;
	if (_hp < 0) {
		_hp = 0;
	}
	if (_hp <= 0) {
		runAction(getDeathAction());
		return false;
	}
	return true;
}

void RoundRole::treat(int power)
{
	auto animation = AnimationCache::getInstance()->getAnimation("treatAnimation");
	_injuredSprite->setVisible(true);
	_injuredSprite->runAction(Sequence::createWithTwoActions(
		Animate::create(animation),
		CallFunc::create([=]() {
		_injuredSprite->setVisible(false);
	})));
	_hp += power;
	if (_hp > 100) {
		_hp = 100;
	}
}

int RoundRole::getPower()
{
	return _power;
}

bool RoundRole::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	_hp = 0;
	initAttackAnimation();
	initInjuredAnimation();
	initTreatAnimation();
	_injuredSprite = Sprite::create();
	_injuredSprite->setVisible(false);
	addChild(_injuredSprite, 10);
	return true;
}

void RoundRole::initTreatAnimation()
{
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("Others/treat_1.png");
	animation->addSpriteFrameWithFile("Others/treat_2.png");
	animation->addSpriteFrameWithFile("Others/treat_3.png");
	animation->addSpriteFrameWithFile("Others/treat_4.png");
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);
	AnimationCache::getInstance()->addAnimation(animation, "treatAnimation");
}