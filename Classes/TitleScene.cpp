#include "TitleScene.h"
#include "GameScene01.h"
#include "DataService.h"

#include "SimpleAudioEngine.h"
#include "Virtualkeys.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	srand(time(NULL));
	GameManager::getInstance()->gameInit();
	DataService::getInstance()->dataServiceInit();

	preloadMusic();
	initTitle();
	initButtons();

	scheduleUpdate();

	_popdialog = PopDialog::create();
	addChild(_popdialog, 10000);
	return true;
}

void TitleScene::update(float dlt)
{
	_cloud1->setPositionX(_cloud1->getPositionX() - 1);
	_cloud2->setPositionX(_cloud2->getPositionX() - 1);
	if (_cloud1->getPositionX() <= -851 / 2) {
		_cloud1->setPositionX(_cloud2->getPositionX() + 851);
	}
	else if (_cloud2->getPositionX() <= -851 / 2) {
		_cloud2->setPositionX(_cloud1->getPositionX() + 851);
	}
}

void TitleScene::preloadMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		audio->preloadEffect("Music/killenemy.OGG");
		audio->preloadEffect("Music/cutgrass.OGG");
		audio->preloadEffect("Music/openbox.OGG");
		audio->preloadEffect("Music/change.OGG");
		audio->preloadEffect("Music/save.OGG");
		audio->preloadEffect("Music/get.OGG");
		audio->preloadEffect("Music/fightstart.OGG");

		audio->preloadBackgroundMusic("Music/bg1.OGG");
		audio->preloadBackgroundMusic("Music/bg_world.OGG");
		audio->preloadBackgroundMusic("Music/bg_village.OGG");
		audio->preloadBackgroundMusic("Music/bg_round.OGG");
		audio->preloadBackgroundMusic("Music/title.OGG");
		audio->playBackgroundMusic("Music/title.OGG", true);
	#else
		audio->preloadEffect("Music/killenemy.mp3");
		audio->preloadEffect("Music/cutgrass.mp3");
		audio->preloadEffect("Music/openbox.mp3");
		audio->preloadEffect("Music/change.mp3");
		audio->preloadEffect("Music/save.mp3");
		audio->preloadEffect("Music/get.mp3");
		audio->preloadEffect("Music/fightstart.mp3");

		audio->preloadBackgroundMusic("Music/bg1.mp3");
		audio->preloadBackgroundMusic("Music/bg_world.mp3");
		audio->preloadBackgroundMusic("Music/bg_village.mp3");
		audio->preloadBackgroundMusic("Music/bg_round.mp3");
		audio->preloadBackgroundMusic("Music/title.mp3");
		audio->playBackgroundMusic("Music/title.mp3", true);
	#endif
}

void TitleScene::initTitle()
{
	auto* bg = Sprite::create("Others/blueblock.png");
	bg->setScaleX(800 / bg->getContentSize().width);
	bg->setScaleY(480 / bg->getContentSize().height);
	bg->setPosition(400, 240);
	addChild(bg, 1);

	auto* title_b = Sprite::create("Others/title_b.png");
	title_b->setPosition(400, -52);
	addChild(title_b, 5);

	auto* title_m = Sprite::create("Others/title_m.png");
	title_m->setPosition(400, 30);
	addChild(title_m, 4);

	_cloud1 = Sprite::create("Others/title_c.png");
	auto width = _cloud1->getContentSize().width;
	_cloud1->setPosition(480 + width / 2, 250);
	addChild(_cloud1, 3);

	_cloud2 = Sprite::create("Others/title_c.png");
	_cloud2->setPosition(_cloud1->getPositionX() + width, 250);
	addChild(_cloud2, 3);

	auto* title_t = Sprite::create("Others/title_t.png");
	title_t->setScale(2);
	title_t->setPosition(23, 550);
	addChild(title_t, 5);

	auto* title = Sprite::create("Others/title.png");
	title->setScale(1.4f);
	title->setPosition(400, 300);
	addChild(title, 10);

	runAction(Sequence::create(
		CallFunc::create([=]() {
		title_b->runAction(MoveBy::create(1.0f, Vec2(0, 150)));
	}),
		DelayTime::create(1.0f),
		CallFunc::create([=]() {
		title_m->runAction(EaseBounceOut::create(MoveBy::create(1.0f, Vec2(0, 150))));
	}),
		CallFunc::create([=]() {
		title_t->runAction(MoveBy::create(1.5f, Vec2(200, -200)));
	}),
		nullptr));
}

void TitleScene::initButtons()
{
	auto bt_new = MenuItemImage::create(
		"GUI/button_n.png",
		"GUI/button_d.png",
		"GUI/button_d.png",
		CC_CALLBACK_1(TitleScene::startButtonPress, this));

	auto bt_continue = MenuItemImage::create(
		"GUI/button_n.png",
		"GUI/button_d.png",
		"GUI/button_d.png",
		CC_CALLBACK_1(TitleScene::continueButtonPress, this));

	auto bt_exit = MenuItemImage::create(
		"GUI/button_n.png",
		"GUI/button_d.png",
		"GUI/button_d.png",
		CC_CALLBACK_1(TitleScene::exitButtonPress, this));

	bt_new->setPosition(880, 100);
	bt_continue->setPosition(-100, 100);
	bt_exit->setPosition(-120, 100);

	bt_new->setScale(0.7f);
	bt_continue->setScale(0.7f);
	bt_exit->setScale(0.7f);
	if (!DataService::getInstance()->hasRecord()) {
		bt_continue->setEnabled(false);
	}
	auto menu = Menu::create(bt_new, bt_continue, bt_exit, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 100);

	auto strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
	auto buttonSize = bt_new->getContentSize();
	Vec2 labelPos(buttonSize.width / 2 + 20, buttonSize.height / 2);

	std::string strNew = strings["new"].asString();
	auto lbNew = Label::createWithSystemFont(strNew, "Consolas", 30);
	lbNew->setPosition(labelPos);
	bt_new->addChild(lbNew, 1);

	std::string strContinue = strings["continue"].asString();
	auto lbContinue = Label::createWithSystemFont(strContinue, "Consolas", 30);
	lbContinue->setPosition(labelPos);
	bt_continue->addChild(lbContinue, 1);

	std::string strExit = strings["exit"].asString();
	auto lbExit = Label::createWithSystemFont(strExit, "Consolas", 30);
	lbExit->setPosition(labelPos);
	bt_exit->addChild(lbExit, 1);

	bt_new->runAction(JumpTo::create(0.8f, Vec2(180, 100), 80, 3));
	bt_continue->runAction(MoveTo::create(0.8f, Vec2(400, 100)));
	bt_exit->runAction(JumpTo::create(0.8f, Vec2(620, 100), 80, 3));
}

void TitleScene::startButtonPress(Ref* sender)
{
	if (DataService::getInstance()->hasRecord()) {
		_popdialog->pop("readystartnewgame", "readyStartNewGame");
	}
	else {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		DataService::getInstance()->initRecordFile();
		auto scene = getNewGameScene();
		Director::getInstance()->replaceScene(
			TransitionTurnOffTiles::create(1.0f, scene));
	}
}

void TitleScene::continueButtonPress(Ref* sender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene* scene = nullptr;
	if (DataService::getInstance()->hasRecord()) {
		scene = getContinueGameScene();
	}
	else {
		scene = getNewGameScene();
	}
	Director::getInstance()->replaceScene(
		TransitionTurnOffTiles::create(1.0f, scene));
}

void TitleScene::exitButtonPress(Ref* sender)
{
	Director::getInstance()->end();
}

Scene* TitleScene::getNewGameScene()
{
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
	return scene;
}

Scene* TitleScene::getContinueGameScene()
{
	auto scene = Scene::create();
	auto data = DataService::getInstance()->loadRecord();
	data.gameScene->fillData(data);
	scene->addChild(data.gameScene);
	return scene;
	//Director::getInstance()->replaceScene(
	//	TransitionRotoZoom::create(1.0f, scene));
}