#ifndef __PLAYER_1_H__
#define __PLAYER_1_H__

#include "Player.h"

class Player_1 : public Player
{
public:
	static Player_1* create();
	bool init();
private:
	void initMoveAnimation() override;
	void initFacetoFrame() override;
	void initAttackAnimation() override;
};

#endif