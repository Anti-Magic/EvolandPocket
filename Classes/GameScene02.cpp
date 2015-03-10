#include "GameScene02.h"
#include "Player_2.h"
#include "MapEnemy_2.h"
#include "Virtualkeys.h"

USING_NS_CC;

Scene* GameScene02::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene02::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene02::init()
{
	if (!GameSceneBase::init()) {
		return false;
	}
	_className = "GameScene02";
	_gameManager = GameManager::getInstance();

	_gameManager->setGameMap(GameMap::create("Maps/map02.tmx"));
	_gameManager->setPlayer(Player_2::create());
	_gameManager->setTipsLayer(TipsLayer::create());
	//_gameManager->setOperator(Virtualkeys::create());
	_gameManager->setGameScene(this);
	initByManager(); //新建以后一定要初始化

	_gameLayer->setScale(80.0f / 16);

	if (GameManager::getInstance()->getIsMusic()) {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg1.OGG", true);
		#else
			CocosDenshion::SimpleAudioEngine::getInstance()
				->playBackgroundMusic("Music/bg1.mp3", true);
		#endif
	}
	return true;
}

//void GameScene02::update(float dlt)
//{
//	moveResponse(dlt);
//	triggerResponse(dlt);
//}

MapEnemy* GameScene02::createMapEnemy()
{
	return MapEnemy_2::create();
}

//void GameScene02::fillData(SceneData& data)
//{
	//GameSceneBase::fillData(data);
	//std::vector<MapEnemy*> enemys;
	//for (int i = 0; i < data.enemyPos.size(); i++) {
	//	auto pos = data.enemyPos[i];
	//	auto tileSize = _gameMap->getTileSize();
	//	auto enemy = MapEnemy_1::create();
	//	enemy->setPositionByTileCoord(
	//		Vec2(int(pos.x / tileSize.width), int(pos.y / tileSize.height)));
	//	enemy->setFaceto(data.enemyFaceto[i]);
	//	enemys.push_back(enemy);
	//	//_gameManager->addMapEnemy(enemy);
	//}
	//_gameManager->setMapEnemys(enemys);
//}
