#ifndef __OPERATORBASE_H__
#define __OPERATORBASE_H__

#include "cocos2d.h"
#include "Tools.h"

class OperatorBase : public cocos2d::Layer
{
public:
	virtual ~OperatorBase() {}
	virtual bool init() override;
	virtual bool isTrigger();
	virtual Tools::Direction getDirection();
	virtual void reset();
	virtual std::string getOpName();
	virtual cocos2d::EventListenerTouchOneByOne* getTouchListener() = 0;
protected:
	Tools::Direction _dir;
	bool _isTrigger;
	std::string _opName;
};

#endif