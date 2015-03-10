#ifndef __PLAYER_3_H__
#define __PLAYER_3_H__

#include "Player.h"

class Player_3 : public Player
{
public:
	static Player_3* create();
	bool init();
private:
	void initMoveAnimation() override;
	void initFacetoFrame() override;
	void initAttackAnimation() override;
};

#endif