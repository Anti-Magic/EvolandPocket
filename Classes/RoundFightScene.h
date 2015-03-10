#ifndef __ROUNDFIGHTSCENE_H__
#define __ROUNDFIGHTSCENE_H__

#include "cocos2d.h"
#include "RoundRole.h"

class RoundFightScene : public cocos2d::Layer
{
public:
	virtual ~RoundFightScene() {}
	virtual bool init(
		std::vector<RoundRole*> enemys,
		std::vector<RoundRole*> players,
		const std::string& bgName);
	static cocos2d::Scene* createScene(
		std::vector<RoundRole*> enemys,
		std::vector<RoundRole*> players,
		const std::string& bgName);
	static RoundFightScene* create(
		std::vector<RoundRole*> enemys,
		std::vector<RoundRole*> players,
		const std::string& bgName);
	bool _allowEscape;
protected:
	cocos2d::ValueMap _strings;
	cocos2d::Label* _injuredLabel;
	cocos2d::Label* _tipLabel;

	std::string _bgName;
	std::vector<RoundRole*> _enemys;
	std::vector<RoundRole*> _players;
	std::vector<cocos2d::Label*> _enemyNames;
	std::vector<cocos2d::Label*> _playerHps;
	cocos2d::Menu* _buttons;
	cocos2d::MenuItemImage* _treatButton;

	int pointer_player;

	void initBackground();
	void initButton();
	void initLabels();
	virtual void initEnemysAndPlayers();
	void removeEnemyAndName(int x);

	virtual void fightFinish();
	virtual void playerRound();
	virtual void enemyRound();
	virtual bool enemyTouch(cocos2d::Touch* touch, cocos2d::Event* event);

	void attackPressed(cocos2d::Ref* sender);
	void escapePressed(cocos2d::Ref* sender);
	void treatPressed(cocos2d::Ref* sender);

	void showInjuredNumber(const cocos2d::Vec2& pos, const int injured);
	void showTreatNumber(const cocos2d::Vec2& pos, const int treat);
};

#endif
