#ifndef __BOSSFIGHTSCENE_H__
#define __BOSSFIGHTSCENE_H__

#include "RoundFightScene.h"
#include "TalkLayer.h"
#include "TipsLayer.h"

class BossFightScene : public RoundFightScene
{
public:
	bool init() override;
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BossFightScene);
private:
	int _roundNum;
	int _bossTarget;
	TalkLayer* _talkLayer;
	TipsLayer* _tipsLayer;
	void changePowers();
	void initEnemysAndPlayers() override;
	void playerRound() override;
	void enemyRound() override;
	void fightFinish() override;
	cocos2d::Action* getEnemyRoundAction();
};

#endif
