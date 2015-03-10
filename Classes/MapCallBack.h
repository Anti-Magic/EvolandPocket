#ifndef __MapCALLBACK_H__
#define __MapCALLBACK_H__

#define ADDCALLBACK(__CALLBACKNAME__) \
_callBackMap.insert(\
std::pair<std::string, MapCallBackFunc>(\
#__CALLBACKNAME__, &MapCallBack::__CALLBACKNAME__));

class MapCallBack;
typedef void (MapCallBack::*MapCallBackFunc)(void);

#include <string>
#include <map>
#include "Tools.h"
#include "cocos2d.h"

class MapCallBack
{
public:
	static MapCallBack* getInstance();
	bool executeBoxCallBack(std::string& callbackName);
	bool executeTransCallBack(std::string& callbackName);
	
private:
	MapCallBack();
	static MapCallBack _instance;
	std::map<std::string, MapCallBackFunc> _callBackMap;

	//box
	void star1();
	void star2();
	void star3();
	void leftEnable();
	void udEnable();
	void scrollEnable();
	void soundEnable();
	void colorAEnable();
	void rollEnable();
	void fightEnable();
	void enemyEnable();
	void musicEnable();
	void saveEnable();
	void colorBEnable();
	void storyEnable();
	void passAUnlock();
	void joystickEnable();

	void roundEnable();
	void mode7Enable();
	void forceEnable();
	void removeHoleRound();
	void something();

	//trans
	cocos2d::Scene* getTransScene(
		const std::string& sceneName, const cocos2d::Vec2& mapTileCoord,
		const cocos2d::Vec2& playerTileCoord, Tools::Direction faceto);
	void sceneToWorldMap();
	void worldMapToScene();
	void transToVillage();
	void transToVillage2();
	void villageToWorld();
	void villageToWorld2();
	void worldToHole();
	void holeToWorld();
	void bossFight();

	void house1();
	void house2();
	void house3();
	void house4();
	void house1ToVillage();
	void house2ToVillage();
	void house3ToVillage();
	void house4ToVillage();

	//dialog
	void readyQuitGame();
	void readyStartNewGame();
	void readyFinishEnd();
};

#endif