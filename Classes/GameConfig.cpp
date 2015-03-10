#include "GameConfig.h"

using std::string;

GameConfig GameConfig::_instance;

GameConfig::GameConfig()
{
	timePerMove = 0.3f;
	timePerAttack = 0.3f;
	_playerMoveName2 = "playerMove";
	_playerFacetoName2 = "playerFaceto";
	_playerAttackName2 = "playerAttack";
	_enemyMoveName2 = "enemyMove";
	GID_Box_Open = 318;
	GID_Box_Close = 317;
	GID_SaveArea = 73;
}

GameConfig* GameConfig::getInstance()
{
	return &_instance;
}

const string& GameConfig::getPlayerMoveName(Tools::Direction dir)
{
	_playerMoveName = Tools::dirToString(dir) + _playerMoveName2;
	return _playerMoveName;
}

const string& GameConfig::getPlayerFacetoName(Tools::Direction dir)
{
	_playerFacetoName = Tools::dirToString(dir) + _playerFacetoName2;
	return _playerFacetoName;
}

const string& GameConfig::getPlayerAttackName(Tools::Direction dir)
{
	_playerAttackName = Tools::dirToString(dir) + _playerAttackName2;
	return _playerAttackName;
}

const string& GameConfig::getEnemyMoveName(Tools::Direction dir)
{
	_enemyMoveName = Tools::dirToString(dir) + _enemyMoveName2;
	return _enemyMoveName;
}