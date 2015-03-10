#ifndef __PLAYER_2_H__
#define __PLAYER_2_H__

#include "Player.h"

class Player_2 : public Player
{
public:
	static Player_2* create();
	bool init();
private:
	void initMoveAnimation() override;
	void initFacetoFrame() override;
	void initAttackAnimation() override;
};

#endif