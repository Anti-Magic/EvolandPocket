#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "OperatorBase.h"
#include "Tools.h"

class Joystick : public OperatorBase
{
public:
	Tools::Direction getDirection() override;
	bool isTrigger() override;
	virtual bool init() override;
	void reset() override;
	virtual cocos2d::EventListenerTouchOneByOne* getTouchListener() override;
	CREATE_FUNC(Joystick);
private:
	cocos2d::Sprite* _bigCircle;
	cocos2d::Sprite* _smallCircle;
	cocos2d::Size _visSize;
	cocos2d::Vec2 _joystickPos;
	cocos2d::Vec2 _touchBeganPos;

	bool _joystickAlive;
	float _radius;
};

#endif