#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Tools.h"

class GameManager;

class Player : public cocos2d::Sprite
{
public:
	Player() {}
	virtual ~Player() {}
	virtual bool init(const std::string& filename);

	void setPositionByTileCoord(const cocos2d::Vec2& tilecoord);
	bool move(Tools::Direction dir);
	void attack(bool isAttack);
	Tools::Direction getFaceto();
	void setFaceto(Tools::Direction dir);
protected:
	GameManager* _gameManager;
	Tools::Direction _faceto;
	const static int Tag_MoveAnimate = 100;
	const static int Tag_AttackAction = 200;

	virtual void initMoveAnimation() = 0;
	virtual void initFacetoFrame() = 0;
	virtual void initAttackAnimation() = 0;
};

#endif