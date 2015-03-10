#include "MapCallBack.h"
#include "cocos2d.h"
#include "Virtualkeys.h"
#include "GameManager.h"
#include "GameConfig.h"

#include "GameScene01.h"
#include "GameScene02.h"
#include "GameScene03.h"
#include "GameSceneWorld.h"
#include "MapEnemy_1.h"
#include "GameSceneVillage01.h"
#include "RoundFight.h"
#include "Joystick.h"
#include "RoundPlayer_1.h"
#include "RoundPlayer_2.h"
#include "RoundEnemy_2.h"
#include "RoundFightScene.h"
#include "TalkLayer.h"
#include "GameSceneHole.h"
#include "TitleScene.h"
#include "GameSceneHouse.h"
#include "BossFightScene.h"
#include "RoundEnemyBoss.h"
#include "EndScene.h"

USING_NS_CC;

MapCallBack MapCallBack::_instance;

MapCallBack::MapCallBack()
{
	ADDCALLBACK(star1);
	ADDCALLBACK(star2);
	ADDCALLBACK(star3);
	ADDCALLBACK(leftEnable);
	ADDCALLBACK(udEnable);
	ADDCALLBACK(scrollEnable);
	ADDCALLBACK(soundEnable);
	ADDCALLBACK(colorAEnable);
	ADDCALLBACK(rollEnable);
	ADDCALLBACK(fightEnable);
	ADDCALLBACK(enemyEnable);
	ADDCALLBACK(musicEnable);
	ADDCALLBACK(saveEnable);
	ADDCALLBACK(colorBEnable);
	ADDCALLBACK(storyEnable);
	ADDCALLBACK(passAUnlock);
	ADDCALLBACK(joystickEnable);
	ADDCALLBACK(roundEnable);
	ADDCALLBACK(mode7Enable);
	ADDCALLBACK(forceEnable);
	ADDCALLBACK(removeHoleRound);
	ADDCALLBACK(something);

	ADDCALLBACK(sceneToWorldMap);
	ADDCALLBACK(worldMapToScene);
	ADDCALLBACK(transToVillage);
	ADDCALLBACK(transToVillage2);
	ADDCALLBACK(villageToWorld);
	ADDCALLBACK(villageToWorld2);
	ADDCALLBACK(worldToHole);
	ADDCALLBACK(holeToWorld);
	ADDCALLBACK(bossFight);

	ADDCALLBACK(house1);
	ADDCALLBACK(house2);
	ADDCALLBACK(house3);
	ADDCALLBACK(house4);
	ADDCALLBACK(house1ToVillage);
	ADDCALLBACK(house2ToVillage);
	ADDCALLBACK(house3ToVillage);
	ADDCALLBACK(house4ToVillage);

	ADDCALLBACK(readyQuitGame);
	ADDCALLBACK(readyStartNewGame);
	ADDCALLBACK(readyFinishEnd);
}

MapCallBack* MapCallBack::getInstance()
{
	return &_instance;
}

bool MapCallBack::executeBoxCallBack(std::string& callbackName)
{
	if (callbackName == "" || _callBackMap.find(callbackName) == _callBackMap.end()) {
		return false;
	}
	GameManager::getInstance()->
		getTipsLayer()->makeTips(callbackName);
	(this->*_callBackMap[callbackName])();
	return true;
}

bool MapCallBack::executeTransCallBack(std::string& callbackName)
{
	if (callbackName == "" || _callBackMap.find(callbackName) == _callBackMap.end()) {
		return false;
	}
	//GameManager::getInstance()->
	//	getTipsLayer()->makeTips(callbackName);
	(this->*_callBackMap[callbackName])();
	return true;
}

void MapCallBack::star1()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.mp3", false);
	#endif
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->pauseEventListenersForTarget(op);
	auto player = GameManager::getInstance()->getPlayer();
	auto getFrame = SpriteFrame::create("Roles/get_a.png", Rect(0, 0, 13, 15));
	player->setSpriteFrame(getFrame);
	auto pos = player->getPosition() + Tools::getStep(Tools::Direction::UP);
	Sprite* sword = Sprite::create("Others/star_a1.png");
	sword->setPosition(pos);
	GameManager::getInstance()->getGameMap()->addChild(sword, 1000);
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFile("Others/star_a1.png");
	animation->addSpriteFrameWithFile("Others/star_a2.png");
	animation->addSpriteFrameWithFile("Others/star_a3.png");
	animation->addSpriteFrameWithFile("Others/star_a4.png");
	animation->setLoops(3);
	animation->setDelayPerUnit(0.1f);
	sword->runAction(Animate::create(animation));
	GameManager::getInstance()->getGameScene()->runAction(
		Sequence::createWithTwoActions(
		DelayTime::create(1.2f),
		CallFunc::create([=]() {
		sword->removeFromParentAndCleanup(true);
		auto frameName = GameConfig::getInstance()->getPlayerFacetoName(player->getFaceto());
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		player->setSpriteFrame(frame);
		op->getEventDispatcher()->resumeEventListenersForTarget(op);
	})));
}

void MapCallBack::star2()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.mp3", false);
	#endif
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->pauseEventListenersForTarget(op);
	auto player = GameManager::getInstance()->getPlayer();
	auto getFrame = SpriteFrame::create("Roles/get_b.png", Rect(0, 0, 13, 15));
	player->setSpriteFrame(getFrame);
	auto pos = player->getPosition() + Tools::getStep(Tools::Direction::UP);
	Sprite* sword = Sprite::create("Others/star_b1.png");
	sword->setPosition(pos);
	GameManager::getInstance()->getGameMap()->addChild(sword, 1000);
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFile("Others/star_b1.png");
	animation->addSpriteFrameWithFile("Others/star_b2.png");
	animation->addSpriteFrameWithFile("Others/star_b3.png");
	animation->addSpriteFrameWithFile("Others/star_b4.png");
	animation->setLoops(3);
	animation->setDelayPerUnit(0.1f);
	sword->runAction(Animate::create(animation));
	GameManager::getInstance()->getGameScene()->runAction(
		Sequence::createWithTwoActions(
		DelayTime::create(1.2f),
		CallFunc::create([=]() {
		sword->removeFromParentAndCleanup(true);
		auto frameName = GameConfig::getInstance()->getPlayerFacetoName(player->getFaceto());
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		player->setSpriteFrame(frame);
		op->getEventDispatcher()->resumeEventListenersForTarget(op);
	})));
}

void MapCallBack::star3()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.mp3", false);
	#endif
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->pauseEventListenersForTarget(op);
	auto player = GameManager::getInstance()->getPlayer();
	auto getFrame = SpriteFrame::create("Roles/get_c.png", Rect(0, 0, 13, 15));
	player->setSpriteFrame(getFrame);
	auto pos = player->getPosition() + Tools::getStep(Tools::Direction::UP);
	Sprite* sword = Sprite::create("Others/star_c1.png");
	sword->setPosition(pos);
	GameManager::getInstance()->getGameMap()->addChild(sword, 1000);
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFile("Others/star_c1.png");
	animation->addSpriteFrameWithFile("Others/star_c2.png");
	animation->addSpriteFrameWithFile("Others/star_c3.png");
	animation->addSpriteFrameWithFile("Others/star_c4.png");
	animation->setLoops(3);
	animation->setDelayPerUnit(0.1f);
	sword->runAction(Animate::create(animation));
	GameManager::getInstance()->getGameScene()->runAction(
		Sequence::createWithTwoActions(
		DelayTime::create(1.2f),
		CallFunc::create([=]() {
		sword->removeFromParentAndCleanup(true);
		auto frameName = GameConfig::getInstance()->getPlayerFacetoName(player->getFaceto());
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		player->setSpriteFrame(frame);
		op->getEventDispatcher()->resumeEventListenersForTarget(op);
	})));
}

void MapCallBack::leftEnable()
{
	auto virtualkeys = dynamic_cast<Virtualkeys*>
		(GameManager::getInstance()->getOperator());
	if (virtualkeys != nullptr) {
		virtualkeys->setKeysEnable(Tools::Direction::LEFT, true);
	}
}

void MapCallBack::udEnable()
{
	auto virtualkeys = dynamic_cast<Virtualkeys*>
		(GameManager::getInstance()->getOperator());
	if (virtualkeys != nullptr) {
		virtualkeys->setKeysEnable(Tools::Direction::UP, true);
		virtualkeys->setKeysEnable(Tools::Direction::DOWN, true);
	}
	auto gamescene = dynamic_cast<GameScene01*>
		(GameManager::getInstance()->getGameScene());
	if (gamescene != nullptr) {
		gamescene->_black1->runAction(MoveBy::create(1.0f, Vec2(0, -400)));
		gamescene->_black2->runAction(MoveBy::create(1.0f, Vec2(0, 400)));
	}
}

void MapCallBack::scrollEnable()
{
	auto gamescene = dynamic_cast<GameScene01*>
		(GameManager::getInstance()->getGameScene());
	gamescene->_isroll = false;
}

void MapCallBack::soundEnable()
{
	GameManager::getInstance()->setIsSound(true);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/openbox.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/openbox.mp3", false);
	#endif
}

void MapCallBack::colorAEnable()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/change.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/change.mp3", false);
	#endif
	auto manager = GameManager::getInstance();
	manager->getGameScene()->unscheduleUpdate();
	manager->getGameScene()->getEventDispatcher()
		->removeEventListenersForTarget(manager->getOperator());

	DataService::getInstance()->saveCurSceneData(manager->getGameScene()->getClassName());
	auto data = DataService::getInstance()->getCurSceneData();

	manager->gameReset(false);
	auto layer = GameScene02::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	layer->fillData(data);
	GameManager::getInstance()->getTipsLayer()->makeTips("colorAEnable");

	Director::getInstance()->replaceScene(
		TransitionProgressHorizontal::create(1.0f, scene));
}

void MapCallBack::rollEnable()
{
	auto gamescene = dynamic_cast<GameScene01*>
		(GameManager::getInstance()->getGameScene());
	gamescene->_isroll = true;
}

void MapCallBack::fightEnable()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/get.mp3", false);
	#endif
	auto virtualkeys = dynamic_cast<Virtualkeys*>
		(GameManager::getInstance()->getOperator());
	if (virtualkeys != nullptr) {
		virtualkeys->reset();
		virtualkeys->getEventDispatcher()->pauseEventListenersForTarget(virtualkeys);
		virtualkeys->setKeysEnable(Tools::Direction::NONE, true);
		auto player = GameManager::getInstance()->getPlayer();
		auto getFrame = SpriteFrame::create("Roles/get_a.png", Rect(0, 0, 13, 15));
		player->setSpriteFrame(getFrame);
		auto pos = player->getPosition() + Tools::getStep(Tools::Direction::UP);
		Sprite* sword = Sprite::create("Others/sword1.png");
		sword->setPosition(pos);
		GameManager::getInstance()->getGameMap()->addChild(sword, 1000);
		Animation* animation = Animation::create();
		animation->addSpriteFrameWithFile("Others/sword1.png");
		animation->addSpriteFrameWithFile("Others/sword2.png");
		animation->addSpriteFrameWithFile("Others/sword3.png");
		animation->addSpriteFrameWithFile("Others/sword4.png");
		animation->setLoops(3);
		animation->setDelayPerUnit(0.1f);
		sword->runAction(Animate::create(animation));
		GameManager::getInstance()->getGameScene()->runAction(
			Sequence::createWithTwoActions(
			DelayTime::create(1.2f),
			CallFunc::create([=]() {
				sword->removeFromParentAndCleanup(true);
				auto frameName = GameConfig::getInstance()->getPlayerFacetoName(player->getFaceto());
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
				player->setSpriteFrame(frame);
				virtualkeys->getEventDispatcher()->resumeEventListenersForTarget(virtualkeys);
			})));
	}
}

void MapCallBack::enemyEnable()
{
	auto enemy1 = MapEnemy_1::create();
	enemy1->setPositionByTileCoord(Vec2(38, 34));
	GameManager::getInstance()->addMapEnemy(enemy1);
	auto enemy2 = MapEnemy_1::create();
	enemy2->setPositionByTileCoord(Vec2(39, 38));
	GameManager::getInstance()->addMapEnemy(enemy2);
	auto enemy3 = MapEnemy_1::create();
	enemy3->setPositionByTileCoord(Vec2(51, 28));
	GameManager::getInstance()->addMapEnemy(enemy3);

	auto enemy4 = MapEnemy_1::create();
	enemy4->setPositionByTileCoord(Vec2(46, 33));
	GameManager::getInstance()->addMapEnemy(enemy4);

	auto enemy5 = MapEnemy_1::create();
	enemy5->setPositionByTileCoord(Vec2(44, 38));
	GameManager::getInstance()->addMapEnemy(enemy5);

	auto enemy6 = MapEnemy_1::create();
	enemy6->setPositionByTileCoord(Vec2(67, 35));
	GameManager::getInstance()->addMapEnemy(enemy6);

	auto enemy7 = MapEnemy_1::create();
	enemy7->setPositionByTileCoord(Vec2(61, 29));
	GameManager::getInstance()->addMapEnemy(enemy7);

	auto enemy8 = MapEnemy_1::create();
	enemy8->setPositionByTileCoord(Vec2(62, 18));
	GameManager::getInstance()->addMapEnemy(enemy8);

	auto enemy9 = MapEnemy_1::create();
	enemy9->setPositionByTileCoord(Vec2(54, 19));
	GameManager::getInstance()->addMapEnemy(enemy9);

	auto enemy10 = MapEnemy_1::create();
	enemy10->setPositionByTileCoord(Vec2(44, 19));
	GameManager::getInstance()->addMapEnemy(enemy10);

	auto enemy11 = MapEnemy_1::create();
	enemy11->setPositionByTileCoord(Vec2(37, 16));
	GameManager::getInstance()->addMapEnemy(enemy11);

	auto enemy12 = MapEnemy_1::create();
	enemy12->setPositionByTileCoord(Vec2(45, 12));
	GameManager::getInstance()->addMapEnemy(enemy12);
}

void MapCallBack::musicEnable()
{
	GameManager::getInstance()->setIsMusic(true);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playBackgroundMusic("Music/bg1.OGG", true);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playBackgroundMusic("Music/bg1.mp3", true);
	#endif
}

void MapCallBack::saveEnable()
{

}

void MapCallBack::storyEnable()
{
	if (GameManager::getInstance()->getIsMusic()) {
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			audio->preloadBackgroundMusic("Mucis/story.OGG");
			audio->playBackgroundMusic("Music/story.OGG", true);
		#else
			audio->preloadBackgroundMusic("Mucis/story.mp3");
			audio->playBackgroundMusic("Music/story.mp3", true);
		#endif
	}

	auto scene = GameManager::getInstance()->getGameScene();
	
	auto enemys = GameManager::getInstance()->getMapEnemys();
	if (enemys.size() > 0) {
		for (auto e : enemys) {
			e->pause();
		}
	}
	
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->pauseEventListenersForTarget(op);

	auto storybg = Sprite::create("Others/storybg.png");
	storybg->setPosition(400, 240);
	storybg->setScale(4);
	scene->addChild(storybg, 5);

	auto story = Sprite::create("Others/story.png");
	story->setScale(2);
	scene->addChild(story, 6);
	story->setPosition(400, -100);
	const float rollTime = 20.0f;
	story->runAction(MoveBy::create(rollTime, Vec2(0, 1000)));

	scene->runAction(Sequence::createWithTwoActions(
		DelayTime::create(rollTime),
		CallFunc::create([=]() {
			if (enemys.size() > 0) {
				for (auto e : enemys) {
					e->resume();
				}
			}
			story->removeFromParentAndCleanup(true);
			storybg->removeFromParentAndCleanup(true);
			op->getEventDispatcher()->resumeEventListenersForTarget(op);
			if (GameManager::getInstance()->getIsMusic()) {
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CocosDenshion::SimpleAudioEngine::getInstance()
						->playBackgroundMusic("Music/bg1.OGG", true);
				#else
					CocosDenshion::SimpleAudioEngine::getInstance()
						->playBackgroundMusic("Music/bg1.mp3", true);
				#endif
			}
		})));
}

void MapCallBack::colorBEnable()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/change.OGG", false);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/change.mp3", false);
	#endif
	auto manager = GameManager::getInstance();
	manager->getGameScene()->unscheduleUpdate();
	manager->getGameScene()->getEventDispatcher()
		->removeEventListenersForTarget(manager->getOperator());

	DataService::getInstance()->saveCurSceneData(manager->getGameScene()->getClassName());
	auto data = DataService::getInstance()->getCurSceneData();

	manager->gameReset(false);
	auto layer = GameScene03::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	layer->fillData(data);
	GameManager::getInstance()->getTipsLayer()->makeTips("colorBEnable");

	Director::getInstance()->replaceScene(
		TransitionProgressHorizontal::create(1.0f, scene));
}

void MapCallBack::passAUnlock()
{
	auto enemys = GameManager::getInstance()->getMapEnemys();
	if (enemys.size() > 0) {
		for (auto e : enemys) {
			e->pause();
		}
	}
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->pauseEventListenersForTarget(op);

	auto gameMap = GameManager::getInstance()->getGameMap();
	auto move = MoveBy::create(0.5f, 16 * Vec2(-16, 1));
	auto unlock = CallFunc::create([=]() {
		Vec2 tileCoord(53, 16);
		DataService::getInstance()->destroy(tileCoord);
		gameMap->getLayer("other")->removeTileAt(tileCoord);
		gameMap->getLayer("stop")->removeTileAt(tileCoord);
		ParticleSystem* particle =
			ParticleSystemQuad::create("Particle/cut_grass_1.plist");
		particle->setPosition(Tools::tileCoordToPos(tileCoord));
		particle->setAutoRemoveOnFinish(true);
		gameMap->addChild(particle, 100);
	});
	auto delay = DelayTime::create(0.5f);
	gameMap->runAction(Sequence::create(
		move, delay, unlock, delay->clone(), move->reverse(), 
		CallFunc::create([=]() {
			if (enemys.size() > 0) {
				for (auto e : enemys) {
					e->resume();
				}
			}
			op->getEventDispatcher()->resumeEventListenersForTarget(op);
		}), nullptr));
}

void MapCallBack::joystickEnable()
{
	GameManager::getInstance()->getGameScene()
		->getEventDispatcher()->removeEventListenersForTarget(
		dynamic_cast<Virtualkeys*>(GameManager::getInstance()->getOperator()));
	auto opOld = GameManager::getInstance()->getOperator();
	opOld->reset();
	opOld->removeFromParentAndCleanup(true);
	GameManager::getInstance()->setOperator(Joystick::create());
	GameManager::getInstance()->getGameScene()->setOperator(
		GameManager::getInstance()->getOperator());
}

void MapCallBack::roundEnable()
{
	GameManager::getInstance()->_hasround = true;
	auto round = RoundFight::create("Others/bg_round1.png");
	round->setNoEnemyLayer(GameManager::getInstance()->getGameMap()->getLayer("noenemy"));
	GameManager::getInstance()->getGameScene()->addChild(round);
}

void MapCallBack::mode7Enable()
{
	GameManager::getInstance()->_hasmode7 = true;
	auto layer = GameManager::getInstance()->getGameScene()->getGameLayer();
	layer->runAction(RotateBy::create(0.5f, Vec3(-20, 0, 0)));
}

void MapCallBack::forceEnable()
{
	auto op = GameManager::getInstance()->getOperator();
	op->reset();
	op->getEventDispatcher()->removeEventListenersForTarget(op);
	
	GameManager::getInstance()->_hasplayer2 = true;
	std::vector<RoundRole*> enemys;
	for (int i = 0; i < 3; i++) {
		enemys.push_back(RoundEnemy_2::create());
	}
	std::vector<RoundRole*> players;
	auto player1 = RoundPlayer_1::create();
	players.push_back(player1);
	auto player2 = RoundPlayer_2::create();
	player2->_hp = 1;
	players.push_back(player2);
	auto layer = RoundFightScene::create(enemys, players, "Others/bg_round1.png");
	layer->_allowEscape = false;
	auto scene = Scene::create();
	scene->addChild(layer);
	GameManager::getInstance()->getOperator()->reset();
	GameManager::getInstance()->getTipsLayer()->reset();
	auto tips = TipsLayer::create();
	scene->addChild(tips, 100);
	tips->makeTips("forceEnable");
	Director::getInstance()->pushScene(
		TransitionSplitCols::create(0.5f, scene));
	
	auto talkLayer = GameManager::getInstance()->getTalkLayer();
	Sprite* girl = Sprite::create("Roles/girl_1.png");
	girl->setScale(16.0f / 25);
	auto player = GameManager::getInstance()->getPlayer();
	girl->setPosition(player->getPosition() + Tools::getStep(player->getFaceto()));
	GameManager::getInstance()->getGameMap()->addChild(girl, 1000);

	GameManager::getInstance()->getGameScene()->runAction(Sequence::create(
		CallFunc::create([=]() {
			talkLayer->talk("talk1");
		}),
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			talkLayer->talk("talk2");
		}),
		DelayTime::create(2.0f),
		CallFunc::create([=]() {
			talkLayer->talk("talk3");
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]() {

			Sprite* button_ok = Sprite::create("GUI/button_n1.png");
			button_ok->setPosition(700, 400);
			Sprite* button_no = Sprite::create("GUI/button_d1.png");
			button_no->setPosition(700, 350);

			auto _strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
			auto buttonSize = button_ok->getContentSize();
			auto lbl_ok = Label::createWithSystemFont("", "Consolas", 30);
			lbl_ok->setColor(Color3B::WHITE);
			lbl_ok->setString(_strings["ok"].asString());
			lbl_ok->setPosition(buttonSize.width / 2, buttonSize.height / 2);
			button_ok->addChild(lbl_ok, 100);

			auto lbl_no = Label::createWithSystemFont("", "Consolas", 30);
			lbl_no->setColor(Color3B::GRAY);
			lbl_no->setString(_strings["not"].asString());
			lbl_no->setPosition(buttonSize.width / 2, buttonSize.height / 2);
			button_no->addChild(lbl_no, 100);

			auto curscene = GameManager::getInstance()->getGameScene();
			auto listen = EventListenerTouchOneByOne::create();
			listen->onTouchBegan = [=](Touch* touch, Event* event) {
				if (button_ok->getBoundingBox().containsPoint(touch->getLocation())) {
					op->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
						op->getTouchListener(), op);
					button_ok->removeFromParentAndCleanup(true);
					button_no->removeFromParentAndCleanup(true);
					talkLayer->talk("talk4");
					girl->removeFromParentAndCleanup(true);
					GameManager::getInstance()->getTipsLayer()->makeTips("forceChoose");
				}
				return true;
			};
			curscene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, button_ok);
			curscene->addChild(button_ok, 1000);
			curscene->addChild(button_no, 1000);
		}),
		nullptr));
}

void MapCallBack::removeHoleRound()
{
	auto manager = GameManager::getInstance();
	manager->_hasholeround = false;
	auto oldscene = dynamic_cast<GameSceneHole*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
			oldscene->_roundfight = nullptr;
		}
	}
}

void MapCallBack::something()
{
	Vec2 tile1(38, 16);
	Vec2 tile2(38, 17);
	Vec2 tile3(39, 16);
	Vec2 tile4(39, 17);
	auto gamemap = GameManager::getInstance()->getGameMap();
	auto dataservice = DataService::getInstance();
	gamemap->destroy(tile1);
	dataservice->destroy(tile1);
	gamemap->destroy(tile2);
	dataservice->destroy(tile2);
	gamemap->destroy(tile3);
	dataservice->destroy(tile3);
	gamemap->destroy(tile4);
	dataservice->destroy(tile4);
}

Scene* MapCallBack::getTransScene(
	const std::string& sceneName, const Vec2& mapTileCoord,
	const Vec2& playerTileCoord, Tools::Direction faceto)
{
	auto manager = GameManager::getInstance();
	DataService::getInstance()->saveCurSceneData(
		manager->getGameScene()->getClassName());
	manager->getGameScene()->unscheduleUpdate();
	manager->getGameScene()->getEventDispatcher()
		->removeEventListenersForTarget(manager->getOperator());
	manager->gameReset();
	DataService::getInstance()->reset();
	GameSceneBase* layer = nullptr;
	if (DataService::getInstance()->hasSceneData(sceneName)) {
		auto data = DataService::getInstance()->loadSceneData(sceneName);
		layer = data.gameScene;
		layer->fillData(data);
	}
	else {
		layer = DataService::getInstance()->createGameSceneByName(sceneName);
	}
	auto scene = Scene::create();
	scene->addChild(layer);
	
	manager->getGameMap()->setPositionByTileCoord(mapTileCoord);
	manager->getPlayer()->setPositionByTileCoord(playerTileCoord);
	manager->getPlayer()->setFaceto(faceto);
	return scene;
}

void MapCallBack::sceneToWorldMap()
{
	std::string sceneName("GameSceneWorld");
	Vec2 mapTileCoord(-7, 62);
	Vec2 playerTileCoord(11, 54);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	GameManager::getInstance()->getTipsLayer()->makeTips("worldMap");
	Director::getInstance()->replaceScene(
		TransitionFadeDown::create(1.0f, scene));
}

void MapCallBack::worldMapToScene()
{
	auto manager = GameManager::getInstance();
	auto oldscene = dynamic_cast<GameSceneWorld*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
		}
	}
	std::string sceneName("GameScene03");
	Vec2 mapTileCoord(-50, 85);
	Vec2 playerTileCoord(54, 11);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, scene));
}

void MapCallBack::transToVillage()
{
	auto manager = GameManager::getInstance();
	auto oldscene = dynamic_cast<GameSceneWorld*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
		}
	}
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-19, 53);
	Vec2 playerTileCoord(23, 43);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionFlipAngular::create(1.0f, scene));
}

void MapCallBack::transToVillage2()
{
	auto manager = GameManager::getInstance();
	auto oldscene = dynamic_cast<GameSceneWorld*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
		}
	}
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-82, 76);
	Vec2 playerTileCoord(86, 20);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionFlipAngular::create(1.0f, scene));
}

void MapCallBack::villageToWorld()
{
	std::string sceneName("GameSceneWorld");
	Vec2 mapTileCoord(-30, 100);
	Vec2 playerTileCoord(34, 16);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionFadeDown::create(1.0f, scene));
}

void MapCallBack::villageToWorld2()
{
	std::string sceneName("GameSceneWorld");
	Vec2 mapTileCoord(-28, 103);
	Vec2 playerTileCoord(32, 13);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionFadeBL::create(1.0f, scene));
}

void MapCallBack::worldToHole()
{
	auto manager = GameManager::getInstance();
	auto oldscene = dynamic_cast<GameSceneWorld*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
		}
	}
	std::string sceneName("GameSceneHole");
	Vec2 mapTileCoord(-7, 55);
	Vec2 playerTileCoord(11, 41);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionRotoZoom::create(1.0f, scene));
}

void MapCallBack::holeToWorld()
{
	auto manager = GameManager::getInstance();
	auto oldscene = dynamic_cast<GameSceneHole*>(manager->getGameScene());
	if (oldscene != nullptr) {
		auto round = oldscene->_roundfight;
		if (round != nullptr) {
			round->removeFromParentAndCleanup(true);
			oldscene->_roundfight = nullptr;
		}
	}
	std::string sceneName("GameSceneWorld");
	Vec2 mapTileCoord(-8, 112);
	Vec2 playerTileCoord(12, 4);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionFadeTR::create(1.0f, scene));
}

void MapCallBack::bossFight()
{
	auto manager = GameManager::getInstance();
	auto op = manager->getOperator();
	op->reset();
	op->getEventDispatcher()->removeEventListenersForTarget(op);
	auto talkLayer = TalkLayer::create();
	manager->getGameScene()->addChild(talkLayer, 1000);
	manager->getGameScene()->runAction(
		Sequence::create(
		CallFunc::create([=]() {
			talkLayer->talk("girl1");
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]() {
			talkLayer->talk("girl2");
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]() {
			talkLayer->talk("girl3");
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]() {
			Director::getInstance()->pushScene(
				TransitionSplitCols::create(1.0f, BossFightScene::createScene()));
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]() {
			manager->getTipsLayer()->makeTips("hero");
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]() {
			Director::getInstance()->replaceScene(
				TransitionFade::create(1.0f, EndScene::createScene()));
		}),
		nullptr));
}

void MapCallBack::house1()
{
	std::string sceneName("GameSceneHouse");
	Vec2 mapTileCoord(-8, 73);
	Vec2 playerTileCoord(12, 63);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipX::create(1.5f, scene));
}

void MapCallBack::house2()
{
	std::string sceneName("GameSceneHouse");
	Vec2 mapTileCoord(-8, 88);
	Vec2 playerTileCoord(12, 48);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipX::create(1.5f, scene));
}

void MapCallBack::house3()
{
	std::string sceneName("GameSceneHouse");
	Vec2 mapTileCoord(-8, 103);
	Vec2 playerTileCoord(12, 33);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipX::create(1.5f, scene));
}

void MapCallBack::house4()
{
	std::string sceneName("GameSceneHouse");
	Vec2 mapTileCoord(-8, 118);
	Vec2 playerTileCoord(12, 18);
	auto faceto = Tools::Direction::UP;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipX::create(1.5f, scene));
}

void MapCallBack::house1ToVillage()
{
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-12, 59);
	Vec2 playerTileCoord(16, 37); 
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipY::create(1.0f, scene));
}

void MapCallBack::house2ToVillage()
{
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-32, 62);
	Vec2 playerTileCoord(36, 34);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipY::create(1.0f, scene));
}

void MapCallBack::house3ToVillage()
{
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-54, 59);
	Vec2 playerTileCoord(58, 37);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipY::create(1.0f, scene));
}

void MapCallBack::house4ToVillage()
{
	std::string sceneName("GameSceneVillage01");
	Vec2 mapTileCoord(-28, 72);
	Vec2 playerTileCoord(32, 24);
	auto faceto = Tools::Direction::DOWN;
	auto scene = getTransScene(sceneName, mapTileCoord, playerTileCoord, faceto);
	Director::getInstance()->replaceScene(
		TransitionZoomFlipY::create(1.0f, scene));
}

void MapCallBack::readyQuitGame()
{
	auto manager = GameManager::getInstance();
	manager->getGameScene()->unscheduleUpdate();
	manager->getGameScene()->getEventDispatcher()
		->removeEventListenersForTarget(manager->getOperator());
	manager->gameReset();
	DataService::getInstance()->reset();

	auto scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, scene, false));
}

void MapCallBack::readyStartNewGame()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	DataService::getInstance()->initRecordFile();

	auto scene = Scene::create();
	auto game = GameScene01::create();
	game->_black1 = Sprite::create("Others/blackblock.png");
	game->_black2 = Sprite::create("Others/blackblock.png");
	auto blackSize = game->_black1->getContentSize();
	game->_black1->setScale(800.0f / blackSize.width, 240.0f / blackSize.height);
	game->_black2->setScale(800.0f / blackSize.width, 240.0f / blackSize.height);
	game->_black1->setPosition(400, 120);
	game->_black2->setPosition(400, 440);
	game->addChild(game->_black1, 5);
	game->addChild(game->_black2, 5);
	scene->addChild(game);
	GameManager::getInstance()->getGameMap()
		->setPositionByTileCoord(Vec2(-10, 63));
	GameManager::getInstance()->getPlayer()
		->setPositionByTileCoord(Vec2(15, 33));
	GameManager::getInstance()->getPlayer()
		->setFaceto(Tools::Direction::RIGHT);
	GameManager::getInstance()->getTipsLayer()
		->makeTips("rightEnable");
	auto virtualkeys = dynamic_cast<Virtualkeys*>(
		GameManager::getInstance()->getOperator());
	if (virtualkeys != nullptr) {
		virtualkeys->setKeysEnable(Tools::Direction::DOWN, false);
		virtualkeys->setKeysEnable(Tools::Direction::UP, false);
		virtualkeys->setKeysEnable(Tools::Direction::LEFT, false);
		virtualkeys->setKeysEnable(Tools::Direction::NONE, false);
	}
	game->_isroll = false;

	Director::getInstance()->replaceScene(
		TransitionTurnOffTiles::create(1.0f, scene));
}

void MapCallBack::readyFinishEnd()
{
	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, TitleScene::createScene(), false));
}