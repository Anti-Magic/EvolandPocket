#ifndef __ROUNDPLAYER_2_H__
#define __ROUNDPLAYER_2_H__

#include "RoundRole.h"

class RoundPlayer_2 : public RoundRole
{
public:
	virtual bool init() override;
	CREATE_FUNC(RoundPlayer_2);
private:
	virtual void initAttackAnimation() override;
	virtual void initInjuredAnimation() override;
	virtual cocos2d::Action* getDeathAction() override;
};

#endif