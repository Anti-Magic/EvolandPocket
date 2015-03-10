#ifndef __ROUNDENEMYBOSS_H__
#define __ROUNDENEMYBOSS_H__

#include "RoundRole.h"

class RoundEnemyBoss : public RoundRole
{
public:
	virtual bool init() override;
	CREATE_FUNC(RoundEnemyBoss);
private:
	void initBossAnimation();
	void initAttackAnimation() override;
	void initInjuredAnimation() override;
	cocos2d::Action* getDeathAction() override;
};

#endif