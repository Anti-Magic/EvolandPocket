#ifndef __ROUNDPLAYER_1_H__
#define __ROUNDPLAYER_1_H__

#include "RoundRole.h"

class RoundPlayer_1 : public RoundRole
{
public:
	virtual bool init() override;
	CREATE_FUNC(RoundPlayer_1);
private:
	virtual void initAttackAnimation() override;
	virtual void initInjuredAnimation() override;
	virtual cocos2d::Action* getDeathAction() override;
};

#endif