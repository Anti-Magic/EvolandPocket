#ifndef __DATASERVICE_H__
#define __DATASERVICE_H__

class GameSceneBase;
class OperatorBase;

#include "cocos2d.h"
#include "Tools.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "tinyxml2.h"
#else
#include "tinyxml2/tinyxml2.h"
#endif

class SceneData
{
public:
	GameSceneBase* gameScene;
	cocos2d::Vec2 playerPos;
	cocos2d::Vec2 gameMapPos;
	Tools::Direction playerFaceto;
	std::vector<cocos2d::Vec2> cutgrassPos;
	std::vector<cocos2d::Vec2> openboxPos;
	std::vector<cocos2d::Vec2> destroyPos;
	std::vector<cocos2d::Vec2> enemyPos;
	std::vector<Tools::Direction> enemyFaceto;
};

class DataService
{
public:
	~DataService();
	static DataService* getInstance();
	//初始化，不要写在构造函数中，
	//原因是调用了cocos2d中的单例的API，由于初始化时机的不同，有几率会空指针
	void dataServiceInit();
	void cutGrass(const cocos2d::Vec2& tileCoord);
	void openBox(const cocos2d::Vec2& tileCoord);
	std::vector<cocos2d::Vec2> getOpenBox();
	std::vector<cocos2d::Vec2> getCutGrass();
	void destroy(const cocos2d::Vec2& tileCoord);
	std::vector<cocos2d::Vec2> getDestroy();

	OperatorBase* createCurOperator();
	void reset();
	bool hasRecord();
	SceneData loadRecord();
	void saveRecord(const std::string& curSceneName);
	SceneData getCurSceneData();
	void saveCurSceneData(const std::string& curSceneName);
	bool hasSceneData(const std::string& gameSceneName);
	SceneData loadSceneData(const std::string& gameSceneName);
	void initRecordFile();
	void getTipsWord(const std::string& key, 
		std::string& name, std::string& info);
	GameSceneBase* createGameSceneByName(const std::string& name); //通过存档中的名字建立场景
private:
	DataService();
	static DataService _instance;

	std::string _filePath;
	tinyxml2::XMLDocument* _tipsDoc; //tips.xml
	std::vector<std::string> _sceneList;

	OperatorBase* createOperatorByName(const std::string& name);
	void copyFile(const std::string& src, const std::string& tar);

	std::vector<cocos2d::Vec2> _cutGrass;
	std::vector<cocos2d::Vec2> _openBox;
	std::vector<cocos2d::Vec2> _destroy;
};

#endif