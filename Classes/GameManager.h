#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

class Player;
class GameMap;
class MapEnemy;
class TipsLayer;
class TalkLayer;
class OperatorBase;
class GameSceneBase;

#include "cocos2d.h"
#include <vector>
#include <string>

class GameManager
{
public:
	static GameManager* getInstance();

	Player* getPlayer();
	void setPlayer(Player* player);
	GameMap* getGameMap();
	void setGameMap(GameMap* gamemap);

	const std::vector<MapEnemy*>& getMapEnemys() const;
	void setMapEnemys(std::vector<MapEnemy*>& enemys);
	void addMapEnemy(MapEnemy* mapEnemys);

	OperatorBase* getOperator();
	void setOperator(OperatorBase* op);
	std::string getCallBack();
	void setCallBack(const std::string& callback);
	GameSceneBase* getGameScene();
	void setGameScene(GameSceneBase* gameScene);
	TipsLayer* getTipsLayer();
	void setTipsLayer(TipsLayer* tipsLayer);
	TalkLayer* getTalkLayer();
	void setTalkLayer(TalkLayer* talkLayer);

	bool getIsSound();
	void setIsSound(bool sound);
	bool getIsMusic();
	void setIsMusic(bool music);

	void gamePause(cocos2d::Node* target);
	void gameResume(cocos2d::Node* target);
	void gameReset(bool cleanupEnemys = true);
	void gameInit();
	
	void addMoveTimer(float dlt);
	void addTriggerTimer(float dlt);

	void killEnemy();
	void cutGrass();
	bool checkOpenBox(const cocos2d::Vec2& tileCoord);
	void checkSaveGame(const cocos2d::Vec2& tileCoord);
	void checkTransMap(const cocos2d::Vec2& tileCoord);

	void checkPlayerDied();
	
	bool _isMoving;
	bool _isTriggering;
	std::string _bgmusicName;

	int _boxCount;
	bool _hasplayer2;
	bool _hasmode7;
	bool _hasround;
	bool _hasholeround;

	int _hp1;
	int _hp2;
private:
	GameManager();
	static GameManager _instance;

	Player* _player;
	GameMap* _gamemap;
	std::vector<MapEnemy*> _mapEnemys;
	OperatorBase* _operator;
	GameSceneBase* _gameScene;
	TipsLayer* _tipsLayer;
	TalkLayer* _talkLayer;

	std::string _callBack;

	float _moveTimer; //移动计时器
	float _triggerTimer; //事件计时器

	bool _isSound; //音效
	bool _isMusic; //音乐
};

#endif
