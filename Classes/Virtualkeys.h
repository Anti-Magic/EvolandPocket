#ifndef __VIRTUALKEYS_H__
#define __VIRTUALKEYS_H__

#include "OperatorBase.h"

class Virtualkeys : public OperatorBase
{
public:
	void setKeysEnable(Tools::Direction direction, bool isEnable);
	bool init() override;
	virtual cocos2d::EventListenerTouchOneByOne* getTouchListener() override;
	CREATE_FUNC(Virtualkeys);
private:
	cocos2d::Sprite* leftkey;
	cocos2d::Sprite* rightkey;
	cocos2d::Sprite* upkey;
	cocos2d::Sprite* downkey;
	cocos2d::Sprite* triggerkey;
};

#endif