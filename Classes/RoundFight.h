#ifndef __ROUNDFIGHT_H__
#define __ROUNDFIGHT_H__

class GameManager;
class RoundRole;

#include "cocos2d.h"

class RoundFight : public cocos2d::Node
{
public:
	bool init(const std::string& bgName);
	void update(float dlt);
	void setNoEnemyLayer(cocos2d::TMXLayer* layer);
	static RoundFight* create(const std::string& bgName);
private:
	bool checkFight();
	std::vector<RoundRole*> getEnemys();
	std::vector<RoundRole*> getPlayers();

	cocos2d::TMXLayer* _noEnemyLayer;
	bool _ready;
	GameManager* _gameManager;
	std::string _bgName;
};

#endif
