#include "Joystick.h"
#include <vector>

USING_NS_CC;
using namespace std;

bool Joystick::init()
{
	if(!OperatorBase::init()) {
		return false;
	}

	_opName = "Joystick";
	_joystickAlive = false;

	_visSize = Director::getInstance()->getVisibleSize();
	_bigCircle = Sprite::create("Keys/bigcircle.png");
	_smallCircle = Sprite::create("Keys/smallcircle.png");
	_bigCircle->setVisible(false);
	_smallCircle->setVisible(false);
	_radius = _bigCircle->getContentSize().width / 2;

	this->addChild(_bigCircle);
	this->addChild(_smallCircle);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(getTouchListener(), this);

	return true;
}

Tools::Direction Joystick::getDirection()
{
	Point res = Point::ZERO;
	Point pos = _smallCircle->getPosition();
	float dx = pos.x - _joystickPos.x;
	float dy = pos.y - _joystickPos.y;

	if(abs(dx) < 2.0f && abs(dy) < 2.0f) {
		return Tools::Direction::NONE;
	}

	if(dx > dy) {
		if(-dy > dx) {
			return Tools::Direction::DOWN;
		} else {
			return Tools::Direction::RIGHT;
		}
	} else {
		if(-dx > dy) {
			return Tools::Direction::LEFT;
		} else {
			return Tools::Direction::UP;
		}
	}
	return Tools::Direction::NONE;
}

bool Joystick::isTrigger()
{
	return _isTrigger;
}

void Joystick::reset()
{
	_dir = Tools::Direction::NONE;
	_isTrigger = false;
	_joystickAlive = false;
	_smallCircle->setPosition(_bigCircle->getPosition());
	_bigCircle->setVisible(false);
	_smallCircle->setVisible(false);
}

EventListenerTouchOneByOne* Joystick::getTouchListener()
{
	auto touchListen = EventListenerTouchOneByOne::create();
	touchListen->onTouchBegan = [=](Touch* touch, Event* event) {
		_isTrigger = true;
		_touchBeganPos = touch->getLocation();
		return true;
	};

	touchListen->onTouchMoved = [=](Touch* touch, Event* event) {
		auto touchPos = touch->getLocation();

		if (!_joystickAlive && touchPos.getDistance(_touchBeganPos) <= 10.0f) {
			_isTrigger = true;
			return;
		}

		if (!_joystickAlive) {
			_isTrigger = false;
			_joystickAlive = true;
			_joystickPos = touchPos;
			_bigCircle->setPosition(touchPos);
			_smallCircle->setPosition(touchPos);
			_bigCircle->setVisible(true);
			_smallCircle->setVisible(true);
		}
		else {
			float touchDis = touchPos.getDistance(_joystickPos);
			if (touchDis > _radius) {
				float rate = touchDis / _radius;
				_smallCircle->setPosition((touchPos.x - _joystickPos.x) / rate + _joystickPos.x,
					(touchPos.y - _joystickPos.y) / rate + _joystickPos.y);
			}
			else {
				_smallCircle->setPosition(touchPos);
			}
		}
	};

	touchListen->onTouchEnded = [=](Touch* touch, Event* event) {
		reset();
	};
	return touchListen;
}