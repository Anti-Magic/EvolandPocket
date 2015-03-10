#ifndef __ROUNDENEMY_1_H__
#define __ROUNDENEMY_1_H__

#include "RoundRole.h"

class RoundEnemy_1 : public RoundRole
{
public:
	virtual bool init() override;
	CREATE_FUNC(RoundEnemy_1);
private:
	virtual void initAttackAnimation() override;
	virtual void initInjuredAnimation() override;
	virtual cocos2d::Action* getDeathAction() override;
};

#endif