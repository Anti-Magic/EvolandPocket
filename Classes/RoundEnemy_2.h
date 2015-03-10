#ifndef __ROUNDENEMY_2_H__
#define __ROUNDENEMY_2_H__

#include "RoundRole.h"

class RoundEnemy_2 : public RoundRole
{
public:
	virtual bool init() override;
	CREATE_FUNC(RoundEnemy_2);
private:
	virtual void initAttackAnimation() override;
	virtual void initInjuredAnimation() override;
	virtual cocos2d::Action* getDeathAction() override;
};

#endif