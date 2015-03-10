#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include "Tools.h"

class GameConfig
{
public:
	static GameConfig* getInstance();

	float timePerMove;
	float timePerAttack;
	int GID_Box_Open;
	int GID_Box_Close;
	int GID_SaveArea;

	const std::string& getPlayerMoveName(Tools::Direction dir);
	const std::string& getPlayerFacetoName(Tools::Direction dir);
	const std::string& getPlayerAttackName(Tools::Direction dir);

	const std::string& getEnemyMoveName(Tools::Direction dir);
private:
	GameConfig();
	static GameConfig _instance;

	std::string _playerMoveName2;
	std::string _playerFacetoName2;
	std::string _playerAttackName2;
	std::string _enemyMoveName2;

	std::string _playerMoveName;
	std::string _playerFacetoName;
	std::string _playerAttackName;
	std::string _enemyMoveName;
};

#endif