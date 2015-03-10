#include "Virtualkeys.h"

USING_NS_CC;

bool Virtualkeys::init()
{
	if(!OperatorBase::init()) {
		return false;
	}

	_opName = "Virtualkeys";

	leftkey = Sprite::create("Keys/left.png");
	rightkey = Sprite::create("Keys/right.png");
	upkey = Sprite::create("Keys/up.png");
	downkey = Sprite::create("Keys/down.png");
	triggerkey = Sprite::create("Keys/right.png");

	leftkey->setPosition(100, 150);
	rightkey->setPosition(260, 150);
	upkey->setPosition(180, 220);
	downkey->setPosition(180, 80);
	triggerkey->setPosition(680, 150);

	this->addChild(leftkey);
	this->addChild(rightkey);
	this->addChild(upkey);
	this->addChild(downkey);
	this->addChild(triggerkey);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(getTouchListener(), this);

	return true;
}

void Virtualkeys::setKeysEnable(Tools::Direction direction, bool isEnable)
{
	switch(direction) {
	case Tools::Direction::LEFT:
		leftkey->setVisible(isEnable); break;
	case Tools::Direction::RIGHT:
		rightkey->setVisible(isEnable); break;
	case Tools::Direction::UP:
		upkey->setVisible(isEnable); break;
	case Tools::Direction::DOWN:
		downkey->setVisible(isEnable); break;
	case Tools::Direction::NONE: //ÓÃNONE±íÊ¾triggerkey
		triggerkey->setVisible(isEnable); break;
	}
}

EventListenerTouchOneByOne* Virtualkeys::getTouchListener()
{
	auto touchListen = EventListenerTouchOneByOne::create();
	touchListen->onTouchBegan = [=](Touch* touch, Event* event) {
		Vec2 touchPos = touch->getLocation();
		if (leftkey->isVisible() && leftkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::LEFT;
		}
		else if (rightkey->isVisible() && rightkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::RIGHT;
		}
		else if (upkey->isVisible() && upkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::UP;
		}
		else if (downkey->isVisible() && downkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::DOWN;
		}
		else if (triggerkey->isVisible() && triggerkey->getBoundingBox().containsPoint(touchPos)) {
			_isTrigger = true;
		}
		return true;
	};
	touchListen->onTouchMoved = [=](Touch* touch, Event* event) {
		Vec2 touchPos = touch->getLocation();
		if (leftkey->isVisible() && leftkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::LEFT;
		}
		else if (rightkey->isVisible() && rightkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::RIGHT;
		}
		else if (upkey->isVisible() && upkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::UP;
		}
		else if (downkey->isVisible() && downkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::DOWN;
		}
		else {
			_dir = Tools::Direction::NONE;
		}
		if (triggerkey->isVisible() && triggerkey->getBoundingBox().containsPoint(touchPos)) {
			_isTrigger = true;
		}
		/*else {
			_isTrigger = false;
		}*/
	};
	touchListen->onTouchEnded = [=](Touch* touch, Event* event) {
		Vec2 touchPos = touch->getLocation();
		if (triggerkey->getBoundingBox().containsPoint(touchPos)) {
			_isTrigger = false;
		}
		else if (leftkey->getBoundingBox().containsPoint(touchPos) || 
			rightkey->getBoundingBox().containsPoint(touchPos) || 
			upkey->getBoundingBox().containsPoint(touchPos) || 
			downkey->getBoundingBox().containsPoint(touchPos)) {
			_dir = Tools::Direction::NONE;
		}
		else {
			_isTrigger = false;
			_dir = Tools::Direction::NONE;
		}
	};
	return touchListen;
}