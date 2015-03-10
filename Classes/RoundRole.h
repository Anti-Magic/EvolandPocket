/*
 * �غ���ս��ʱ����͹���Ļ���
 */
#ifndef __ROUNDROLE_H__
#define __ROUNDROLE_H__

#include "cocos2d.h"
#include "Tools.h"

class RoundRole : public cocos2d::Sprite
{
public:
	virtual ~RoundRole() {}
	void attack(Tools::Direction dir);
	bool injured(int power); //����false��ʾ����
	void treat(int power);
	int getPower();
	virtual bool initWithFile(const std::string& filename) override;

	std::string _roleName;
	int _hp;
	int _power;

protected:
	std::string _attackName;
	std::string _injuredName;
	std::string _deathName;
	cocos2d::Sprite* _injuredSprite; //��ʾ����ʱ�Ķ���

	void initTreatAnimation();
	virtual void initAttackAnimation() = 0;
	virtual void initInjuredAnimation() = 0;
	virtual cocos2d::Action* getDeathAction() = 0;
};

#endif