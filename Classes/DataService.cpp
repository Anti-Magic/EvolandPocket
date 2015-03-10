#include "DataService.h"

#include "GameManager.h"
#include "Player.h"
#include "GameMap.h"
#include "MapEnemy.h"
#include "GameScene01.h"
#include "GameScene02.h"
#include "GameScene03.h"
#include "GameSceneWorld.h"
#include "GameSceneVillage01.h"
#include "GameSceneHouse.h"
#include "GameSceneHole.h"
#include "Virtualkeys.h"
#include "Joystick.h"

USING_NS_CC;

DataService DataService::_instance;

DataService::DataService()
{
	_tipsDoc = nullptr;
	_sceneList.push_back("GameScene01");
	_sceneList.push_back("GameScene02");
	_sceneList.push_back("GameScene03");
	_sceneList.push_back("GameSceneWorld");
	_sceneList.push_back("GameSceneVillage01");
	_sceneList.push_back("GameSceneHouse");
	_sceneList.push_back("GameSceneHole");
}

DataService::~DataService()
{
	if (_tipsDoc != nullptr) {
		delete _tipsDoc;
	}
}

DataService* DataService::getInstance()
{
	return &_instance;
}

void DataService::dataServiceInit()
{
	_filePath = FileUtils::getInstance()->getWritablePath();
	if (_tipsDoc == nullptr) {
		_tipsDoc = new tinyxml2::XMLDocument();
		auto data = FileUtils::getInstance()->getStringFromFile("tips.xml");
		_tipsDoc->Parse(data.c_str());
	}
}

void DataService::cutGrass(const cocos2d::Vec2& tileCoord)
{
	_cutGrass.push_back(tileCoord);
}

void DataService::openBox(const cocos2d::Vec2& tileCoord)
{
	_openBox.push_back(tileCoord);
}

std::vector<Vec2> DataService::getOpenBox()
{
	return _openBox;
}

std::vector<Vec2> DataService::getCutGrass()
{
	return _cutGrass;
}

void DataService::destroy(const cocos2d::Vec2& tileCoord)
{
	_destroy.push_back(tileCoord);
}

std::vector<cocos2d::Vec2> DataService::getDestroy()
{
	return _destroy;
}

OperatorBase* DataService::createCurOperator()
{
	auto name = UserDefault::getInstance()->getStringForKey("operator", "Virtualkeys");
	return createOperatorByName(name);
}

void DataService::reset()
{
	_cutGrass.clear();
	_openBox.clear();
	_destroy.clear();
}

bool DataService::hasRecord()
{
	if (UserDefault::getInstance()->getBoolForKey("record")) {
		return true;
	}
	else {
		initRecordFile();
	}
	return false;
}

SceneData DataService::loadRecord()
{
	GameManager::getInstance()->setIsSound(
		UserDefault::getInstance()->getBoolForKey("sound"));
	GameManager::getInstance()->setIsMusic(
		UserDefault::getInstance()->getBoolForKey("music"));
	GameManager::getInstance()->_boxCount =
		UserDefault::getInstance()->getIntegerForKey("boxcount");
	GameManager::getInstance()->_hasplayer2 = 
		UserDefault::getInstance()->getBoolForKey("player2");
	GameManager::getInstance()->_hasmode7 =
		UserDefault::getInstance()->getBoolForKey("mode7");
	GameManager::getInstance()->_hasround =
		UserDefault::getInstance()->getBoolForKey("round");
	GameManager::getInstance()->_hasholeround =
		UserDefault::getInstance()->getBoolForKey("holeround");
	for (int i = 0; i < _sceneList.size(); i++) {
		auto recordName = _filePath + _sceneList[i] + ".xml";
		auto tmpRecordName = _filePath + _sceneList[i] + "_tmp.xml";
		copyFile(recordName, tmpRecordName);
	}
	auto data = loadSceneData(UserDefault::getInstance()->getStringForKey("scene"));
	//auto step = Tools::getStep(data.playerFaceto);
	//data.playerPos += step; //为了使人物站在存档点上
	//data.gameMapPos -= step;
	return data;
}

void DataService::saveRecord(const std::string& curSceneName)
{
	UserDefault::getInstance()->setBoolForKey("record", true);
	UserDefault::getInstance()->setStringForKey("scene", curSceneName);
	UserDefault::getInstance()->setBoolForKey(
		"sound", GameManager::getInstance()->getIsSound());
	UserDefault::getInstance()->setBoolForKey(
		"music", GameManager::getInstance()->getIsMusic());

	UserDefault::getInstance()->setIntegerForKey(
		"boxcount", GameManager::getInstance()->_boxCount);
	UserDefault::getInstance()->setBoolForKey(
		"player2", GameManager::getInstance()->_hasplayer2);
	UserDefault::getInstance()->setBoolForKey(
		"mode7", GameManager::getInstance()->_hasmode7);
	UserDefault::getInstance()->setBoolForKey(
		"round", GameManager::getInstance()->_hasround);
	UserDefault::getInstance()->setBoolForKey(
		"holeround", GameManager::getInstance()->_hasholeround);

	UserDefault::getInstance()->setStringForKey("operator",
		GameManager::getInstance()->getOperator()->getOpName());
	saveCurSceneData(curSceneName);
	for (int i = 0; i < _sceneList.size(); i++) {
		auto recordName = _filePath + _sceneList[i] + ".xml";
		auto tmpRecordName = _filePath + _sceneList[i] + "_tmp.xml";
		copyFile(tmpRecordName, recordName);
	}
}

void DataService::copyFile(const std::string& src, const std::string& tar)
{
	auto content = FileUtils::getInstance()->getDataFromFile(src);
	FILE* fp_tar = fopen(tar.c_str(), "wb");
	fwrite(content.getBytes(), sizeof(unsigned char), content.getSize(), fp_tar);
	fclose(fp_tar);
}

void DataService::initRecordFile()
{
	UserDefault::getInstance()->setBoolForKey("record", false);
	UserDefault::getInstance()->setBoolForKey("sound", false);
	UserDefault::getInstance()->setBoolForKey("music", false);
	UserDefault::getInstance()->setBoolForKey("mode7", false);
	UserDefault::getInstance()->setBoolForKey("round", false);
	UserDefault::getInstance()->setBoolForKey("holeround", true);
	UserDefault::getInstance()->setIntegerForKey("boxcount", 0);
	UserDefault::getInstance()->setBoolForKey("player2", false);
	UserDefault::getInstance()->setStringForKey("operator", "Virtualkeys");
	for (int i = 0; i < _sceneList.size(); i++) {
		auto sceneDoc = new tinyxml2::XMLDocument();
		auto dec = sceneDoc->NewDeclaration(
			"xml version=\"1.0\" encoding=\"UTF-8\"");
		sceneDoc->LinkEndChild(dec);
		auto recordElement = sceneDoc->NewElement("record");
		sceneDoc->LinkEndChild(recordElement);
		{
			auto existElement = sceneDoc->NewElement("exist");
			existElement->LinkEndChild(sceneDoc->NewText("0"));
			recordElement->LinkEndChild(existElement);
		}
		auto recordName = _filePath + _sceneList[i] + ".xml";
		sceneDoc->SaveFile(recordName.c_str());
		delete sceneDoc;

		auto tmpRecordName = _filePath + _sceneList[i] + "_tmp.xml";
		copyFile(recordName, tmpRecordName);
	}
}

SceneData DataService::getCurSceneData()
{
	SceneData data;
	data.cutgrassPos = _cutGrass;
	data.openboxPos = _openBox;
	data.destroyPos = _destroy;
	data.playerPos = GameManager::getInstance()->getPlayer()->getPosition();
	data.playerFaceto = GameManager::getInstance()->getPlayer()->getFaceto();
	data.gameMapPos = GameManager::getInstance()->getGameMap()->getPosition();
	auto enemys = GameManager::getInstance()->getMapEnemys();
	if (enemys.size() > 0) {
		for (auto e : enemys) {
			data.enemyPos.push_back(e->getPosition());
			data.enemyFaceto.push_back(e->getFaceto());
		}
	}
	return data;
}

void DataService::saveCurSceneData(const std::string& curSceneName)
{
	auto data = getCurSceneData();
	char textTmp[128];
	auto document = new tinyxml2::XMLDocument();
	auto dec = document->NewDeclaration(
		"xml version=\"1.0\" encoding=\"UTF-8\"");
	document->LinkEndChild(dec);
	auto recordElement = document->NewElement("record");
	document->LinkEndChild(recordElement);
	{
		auto existElement = document->NewElement("exist");
		existElement->LinkEndChild(document->NewText("1"));
		recordElement->LinkEndChild(existElement);
		auto mapElement = document->NewElement("map");
		recordElement->LinkEndChild(mapElement);
		{
			auto posElement = document->NewElement("pos");
			sprintf(textTmp, "%.0f %.0f", data.gameMapPos.x, data.gameMapPos.y);
			posElement->LinkEndChild(document->NewText(textTmp));
			mapElement->LinkEndChild(posElement);

			auto grassElement = document->NewElement("grass");
			mapElement->LinkEndChild(grassElement);
			if (data.cutgrassPos.size() > 0) {
				for (auto p : data.cutgrassPos) {
					auto tileElement = document->NewElement("tile");
					grassElement->LinkEndChild(tileElement);
					sprintf(textTmp, "%.0f %.0f", p.x, p.y);
					tileElement->LinkEndChild(document->NewText(textTmp));
				}
			}

			auto boxElement = document->NewElement("box");
			mapElement->LinkEndChild(boxElement);
			if (data.openboxPos.size() > 0) {
				for (auto p : data.openboxPos) {
					auto tileElement = document->NewElement("tile");
					boxElement->LinkEndChild(tileElement);
					sprintf(textTmp, "%.0f %.0f", p.x, p.y);
					tileElement->LinkEndChild(document->NewText(textTmp));
				}
			}

			auto destroyElement = document->NewElement("destroy");
			mapElement->LinkEndChild(destroyElement);
			if (data.destroyPos.size() > 0) {
				for (auto p : data.destroyPos) {
					auto tileElement = document->NewElement("tile");
					destroyElement->LinkEndChild(tileElement);
					sprintf(textTmp, "%.0f %.0f", p.x, p.y);
					tileElement->LinkEndChild(document->NewText(textTmp));
				}
			}
		}
		auto playerElement = document->NewElement("player");
		recordElement->LinkEndChild(playerElement);
		{
			auto posElement = document->NewElement("pos");
			playerElement->LinkEndChild(posElement);
			sprintf(textTmp, "%.0f %.0f", data.playerPos.x, data.playerPos.y);
			posElement->LinkEndChild(document->NewText(textTmp));

			auto facetoElement = document->NewElement("faceto");
			playerElement->LinkEndChild(facetoElement);
			sprintf(textTmp, "%d", static_cast<int>(data.playerFaceto));
			facetoElement->LinkEndChild(document->NewText(textTmp));
		}
		auto enemyElement = document->NewElement("enemy");
		recordElement->LinkEndChild(enemyElement);
		{
			for (int i = 0; i < data.enemyPos.size(); i++) {
				auto posElement = document->NewElement("pos");
				enemyElement->LinkEndChild(posElement);
				sprintf(textTmp, "%.0f %.0f", data.enemyPos[i].x, data.enemyPos[i].y);
				posElement->LinkEndChild(document->NewText(textTmp));

				auto facetoElement = document->NewElement("faceto");
				enemyElement->LinkEndChild(facetoElement);
				sprintf(textTmp, "%d", static_cast<int>(data.enemyFaceto[i]));
				facetoElement->LinkEndChild(document->NewText(textTmp));
			}
		}
	}
	auto fileName = _filePath + curSceneName + "_tmp.xml";
	document->SaveFile(fileName.c_str());
	delete document;
}

bool DataService::hasSceneData(const std::string& gameSceneName)
{
	auto document = new tinyxml2::XMLDocument();
	auto fileName = _filePath + gameSceneName + "_tmp.xml";
	document->LoadFile(fileName.c_str());
	auto recordElement = document->RootElement();
	std::string exist = recordElement->FirstChildElement("exist")->GetText();
	return (exist == "1");
}

SceneData DataService::loadSceneData(const std::string& gameSceneName)
{
	SceneData data;
	data.gameScene = createGameSceneByName(gameSceneName);
	auto document = new tinyxml2::XMLDocument();
	auto fileName = _filePath + gameSceneName + "_tmp.xml";
	document->LoadFile(fileName.c_str());
	auto recordElement = document->RootElement();
	{
		auto mapElement = recordElement->FirstChildElement("map");
		{
			auto posElement = mapElement->FirstChildElement("pos");
			int x = 0, y = 0;
			sscanf(posElement->GetText(), "%d %d", &x, &y);
			data.gameMapPos = Vec2(x, y);
			
			auto grassElement = mapElement->FirstChildElement("grass");
			auto grassTileElement = grassElement->FirstChildElement("tile");
			while (grassTileElement) {
				int x = 0, y = 0;
				sscanf(grassTileElement->GetText(), "%d %d", &x, &y);
				data.cutgrassPos.push_back(Vec2(x, y));
				grassTileElement = grassTileElement->NextSiblingElement();
			}
			
			auto boxElement = mapElement->FirstChildElement("box");
			auto boxTileElement = boxElement->FirstChildElement("tile");
			while (boxTileElement) {
				int x = 0, y = 0;
				sscanf(boxTileElement->GetText(), "%d %d", &x, &y);
				data.openboxPos.push_back(Vec2(x, y));
				boxTileElement = boxTileElement->NextSiblingElement();
			}

			auto destroyElement = mapElement->FirstChildElement("destroy");
			auto destroyTileElement = destroyElement->FirstChildElement("tile");
			while (destroyTileElement) {
				int x = 0, y = 0;
				sscanf(destroyTileElement->GetText(), "%d %d", &x, &y);
				data.destroyPos.push_back(Vec2(x, y));
				destroyTileElement = destroyTileElement->NextSiblingElement();
			}
		}
		auto playerElement = recordElement->FirstChildElement("player");
		{
			auto posElement = playerElement->FirstChildElement("pos");
			int x = 0, y = 0;
			sscanf(posElement->GetText(), "%d %d", &x, &y);
			data.playerPos = Vec2(x, y);

			auto facetoElement = playerElement->FirstChildElement("faceto");
			int faceto;
			sscanf(facetoElement->GetText(), "%d", &faceto);
			data.playerFaceto = static_cast<Tools::Direction>(faceto);
		}
		
		auto enemyElement = recordElement->FirstChildElement("enemy");
		{
			auto posElement = enemyElement->FirstChildElement("pos");
			while(posElement) {
				int x = 0, y = 0;
				sscanf(posElement->GetText(), "%d %d", &x, &y);
				data.enemyPos.push_back(Vec2(x, y));
				posElement = posElement->NextSiblingElement("pos");
			}
			
			auto facetoElement = enemyElement->FirstChildElement("faceto");
			while(facetoElement) {
				int faceto = 0;
				sscanf(facetoElement->GetText(), "%d", &faceto);
				data.enemyFaceto.push_back(static_cast<Tools::Direction>(faceto));
				facetoElement = facetoElement->NextSiblingElement("faceto");
			}
		}
	}
	_cutGrass = data.cutgrassPos;
	_openBox = data.openboxPos;
	_destroy = data.destroyPos;
	return data;
}

void DataService::getTipsWord(const std::string& key, 
	std::string& name, std::string& info)
{
	auto stringElement = _tipsDoc->RootElement();
	auto tarElement = stringElement->FirstChildElement(key.c_str());
	name = tarElement->FirstChildElement("name")->GetText();
	info = tarElement->FirstChildElement("info")->GetText();
}

GameSceneBase* DataService::createGameSceneByName(const std::string& name)
{
	GameSceneBase* res = nullptr;
	if (name == "GameScene01") {
		res = GameScene01::create();
	}
	else if (name == "GameScene02") {
		res = GameScene02::create();
	}
	else if (name == "GameScene03") {
		res = GameScene03::create();
	}
	else if (name == "GameSceneWorld") {
		res = GameSceneWorld::create();
	}
	else if (name == "GameSceneVillage01") {
		res = GameSceneVillage01::create();
	}
	else if (name == "GameSceneHouse") {
		res = GameSceneHouse::create();
	}
	else if (name == "GameSceneHole") {
		res = GameSceneHole::create();
	}
	return res;
}

OperatorBase* DataService::createOperatorByName(const std::string& name)
{
	OperatorBase* res = nullptr;
	if (name == "Virtualkeys") {
		res = Virtualkeys::create();
	}
	else if (name == "Joystick") {
		res = Joystick::create();
	}
	return res;
}