#include "RoundFightScene.h"
#include "GameManager.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* RoundFightScene::createScene(
	std::vector<RoundRole*> enemys, std::vector<RoundRole*> players, const std::string& bgName)
{
	auto scene = Scene::create();
	auto layer = RoundFightScene::create(enemys, players, bgName);
	scene->addChild(layer);
	return scene;
}

RoundFightScene* RoundFightScene::create(
	std::vector<RoundRole*> enemys, std::vector<RoundRole*> players, const std::string& bgName)
{
	RoundFightScene *ret = new RoundFightScene();
	if (ret && ret->init(enemys, players, bgName)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool RoundFightScene::init(
	std::vector<RoundRole*> enemys, std::vector<RoundRole*> players, const std::string& bgName)
{
	if (!Layer::init()) {
		return false;
	}
	_bgName = bgName;
	_allowEscape = true;
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/fightstart.OGG", false);
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playBackgroundMusic("Music/bg_round.OGG", true);
	#else
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playEffect("Music/fightstart.mp3", false);
		CocosDenshion::SimpleAudioEngine::getInstance()
			->playBackgroundMusic("Music/bg_round.mp3", true);
	#endif

	_strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
	_enemys = enemys;
	_players = players;
	pointer_player = 0;

	initBackground();
	initButton();
	initLabels();
	initEnemysAndPlayers();

	runAction(Sequence::createWithTwoActions(
		CallFunc::create([=]() {
			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = CC_CALLBACK_2(RoundFightScene::enemyTouch, this);
			getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		}),
		CallFunc::create([=]() {
			getEventDispatcher()->pauseEventListenersForTarget(this);
			playerRound();
		})));
	return true;
}

bool RoundFightScene::enemyTouch(cocos2d::Touch* touch, cocos2d::Event* event)
{
	for (int i = 0; i < _enemys.size(); i++) {
		auto e = _enemys[i];
		if (e->getBoundingBox().containsPoint(touch->getLocation())) {
			_players[pointer_player]->attack(Tools::Direction::LEFT);
			showInjuredNumber(e->getPosition(), _players[pointer_player]->getPower());
			if (!e->injured(_players[pointer_player]->getPower())) {
				removeEnemyAndName(i);
				if (_enemys.empty()) {
					fightFinish();
				}
			}
			if (++pointer_player >= _players.size()) {
				enemyRound();
			}
			else {
				playerRound();
			}
			break;
		}
	}
	return true;
}

void RoundFightScene::initBackground()
{
	auto bg = Sprite::create(_bgName);
	bg->setScaleY(330 / bg->getContentSize().height);
	bg->setPosition(400, 315);
	addChild(bg, 1);

	auto block = Sprite::create("Others/roundfight.png");
	block->setPosition(400, 85);
	addChild(block, 10);
}

void RoundFightScene::initButton()
{
	auto attackButton = MenuItemImage::create(
		"GUI/button_n1.png", "GUI/button_d1.png", "GUI/button_d1.png",
		CC_CALLBACK_1(RoundFightScene::attackPressed, this));
	_treatButton = MenuItemImage::create(
		"GUI/button_n1.png", "GUI/button_d1.png", "GUI/button_d1.png",
		CC_CALLBACK_1(RoundFightScene::treatPressed, this));
	auto escapeButton = MenuItemImage::create(
		"GUI/button_n1.png", "GUI/button_d1.png", "GUI/button_d1.png",
		CC_CALLBACK_1(RoundFightScene::escapePressed, this));

	/*_treatButton->setVisible(false);
	_treatButton->setEnabled(false);*/

	attackButton->setPosition(400.0f, 120);
	escapeButton->setPosition(400.0f, 80);
	_treatButton->setPosition(400.0f, 40);
	_buttons = Menu::create(attackButton, escapeButton, _treatButton, nullptr);
	_buttons->setPosition(Vec2::ZERO);
	addChild(_buttons, 100);
	std::string strAtt = _strings["attack"].asString();
	auto lbAtt = Label::createWithSystemFont(strAtt, "Consolas", 30);
	auto attackButtonSize = attackButton->getContentSize();
	lbAtt->setPosition(attackButtonSize.width / 2, attackButtonSize.height / 2);
	attackButton->addChild(lbAtt, 100);

	std::string strEsc = _strings["escape"].asString();
	auto lbEsc = Label::createWithSystemFont(strEsc, "Consolas", 30);
	auto escapeButtonSize = escapeButton->getContentSize();
	lbEsc->setPosition(escapeButtonSize.width / 2, escapeButtonSize.height / 2);
	escapeButton->addChild(lbEsc, 100);

	std::string strTre = _strings["treat"].asString();
	auto lbTre = Label::createWithSystemFont(strTre, "Consolas", 30);
	auto treatButtonSize = _treatButton->getContentSize();
	lbTre->setPosition(treatButtonSize.width / 2, treatButtonSize.height / 2);
	_treatButton->addChild(lbTre, 100);
}

void RoundFightScene::initLabels()
{
	_injuredLabel = Label::createWithSystemFont("", "Consolas", 30);
	addChild(_injuredLabel, 10000);
	_injuredLabel->setColor(Color3B::RED);
	_injuredLabel->setVisible(false);

	_tipLabel = Label::createWithSystemFont("", "Consolas", 25);
	_tipLabel->setPosition(400.0f, 100.0f);
	_tipLabel->setColor(Color3B::GREEN);
	addChild(_tipLabel, 10000);
}

void RoundFightScene::playerRound()
{
	_tipLabel->setString("");
	_buttons->setVisible(true);
	_buttons->setEnabled(true);
	if (_players[pointer_player]->_roleName != "girl") {
		_treatButton->setVisible(false);
		_treatButton->setEnabled(false);
	}
	else {
		_treatButton->setVisible(true);
		_treatButton->setEnabled(true);
	}
	getEventDispatcher()->pauseEventListenersForTarget(this);
}

void RoundFightScene::enemyRound()
{
	_tipLabel->setString("");
	_buttons->setVisible(false);
	_buttons->setEnabled(false);
	getEventDispatcher()->pauseEventListenersForTarget(this);
	pointer_player = -1;

	Vector<FiniteTimeAction*> actions;
	actions.pushBack(DelayTime::create(0.5f));
	for (auto e : _enemys) {
		auto act = CallFunc::create([=]() {
			e->attack(Tools::Direction::RIGHT);
			int target = rand() % (int)_players.size();
			showInjuredNumber(_players[target]->getPosition(), e->getPower());
			if (_players[target]->injured(e->getPower())) {
				_playerHps[target]->setString(Value(_players[target]->_hp).asString());
			}
			else {
				_players.erase(_players.begin() + target);
				_playerHps[target]->setString("0");
				_playerHps.erase(_playerHps.begin() + target);
				if (_players.empty()) {
					stopAllActions();
					runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f),
						CallFunc::create([]() {
						Director::getInstance()->replaceScene(GameOverScene::createScene());
					})));
				}
			}
		});
		actions.pushBack(DelayTime::create(0.3f));
		actions.pushBack(act);
		actions.pushBack(DelayTime::create(0.8f));
	}
	actions.pushBack(CallFunc::create([&]() {
		pointer_player = 0;
		playerRound();
	}));
	runAction(Sequence::create(actions));
}

void RoundFightScene::attackPressed(Ref* sender)
{
	if (pointer_player >= 0) {
		_tipLabel->setColor(Color3B::YELLOW);
		_tipLabel->setString(_strings["roundtip1"].asString());
		_buttons->setVisible(false);
		_buttons->setEnabled(false);
		getEventDispatcher()->resumeEventListenersForTarget(this);
	}
}

void RoundFightScene::escapePressed(Ref* sender)
{
	if (pointer_player >= 0) {
		auto half = RAND_MAX / 2;
		if (_allowEscape && rand() > half && rand() > half && rand() > half) {
			runAction(Sequence::create(
				CallFunc::create([=]() {
					_buttons->setVisible(false);
					_buttons->setEnabled(false);
					_tipLabel->setColor(Color3B::GREEN);
					_tipLabel->setString(_strings["escsuccess"].asString());
				}),
				FadeOut::create(0.5f),
				CallFunc::create([]() {
					CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
						GameManager::getInstance()->_bgmusicName.c_str(), true);
					Director::getInstance()->popScene();
				}),
				nullptr));
		}
		else {
			runAction(Sequence::create(
				CallFunc::create([=]() {
				_buttons->setVisible(false);
				_buttons->setEnabled(false);
				_tipLabel->setColor(Color3B::RED);
				_tipLabel->setString(_strings["escfail"].asString());
			}),
				DelayTime::create(0.5f),
				CallFunc::create([=]() {
				if (pointer_player < _players.size()) {
					_buttons->setVisible(true);
					_buttons->setEnabled(true);
				}
				_tipLabel->setString("");
			}),
				nullptr));
		}
		if (++pointer_player >= _players.size()) {
			pointer_player = -1;
			enemyRound();
		}
		else {
			playerRound();
		}
	}
}

void RoundFightScene::treatPressed(Ref* sender)
{
	if (pointer_player >= 0) {
		for (auto p : _players) {
			p->treat(5);
		}
		_players[pointer_player]->attack(Tools::Direction::LEFT);
		Vector<FiniteTimeAction*> actions;
		actions.pushBack(DelayTime::create(0.3f));
		for (int i = 0; i < _players.size(); i++) {
			auto act = CallFunc::create([=]() {
				showTreatNumber(_players[i]->getPosition(), 5);
				_playerHps[i]->setString(Value(_players[i]->_hp).asString());
			});
			actions.pushBack(act);
			actions.pushBack(DelayTime::create(0.5f));
		}
		actions.pushBack(CallFunc::create([&]() {
			if (++pointer_player >= _players.size()) {
				pointer_player = -1;
				enemyRound();
			}
			else {
				playerRound();
			}
		}));
		runAction(Sequence::create(actions));
	}
}

void RoundFightScene::initEnemysAndPlayers()
{
	for (int i = 0; i < _enemys.size(); i++) {

		auto label = Label::createWithSystemFont("", "Consolas", 28);
		label->setString(_strings[_enemys[i]->_roleName].asString());
		label->setPosition(100, 115 - 30*i);
		_enemyNames.push_back(label);
		addChild(label, 100);

		if (i == 0) {
			_enemys[i]->setPosition(Vec2(100, 350));
		}
		else if (i == 1) {
			_enemys[i]->setPosition(Vec2(100, 220));
		}
		else if (i == 2) {
			_enemys[i]->setPosition(Vec2(230, 275));
		}
		_enemys[i]->setScale(3);
		addChild(_enemys[i], 1000 - i);
	}
	for (int i = 0; i < _players.size(); i++) {

		auto namelabel = Label::createWithSystemFont("", "Consolas", 28);
		namelabel->setString(_strings[_players[i]->_roleName].asString());
		namelabel->setPosition(600, 115 - 30 * i);
		addChild(namelabel, 100);

		auto hplabel = Label::createWithSystemFont("", "Consolas", 28);
		hplabel->setString(Value(_players[i]->_hp).asString());
		hplabel->setPosition(700, 115 - 30 * i);
		_playerHps.push_back(hplabel);
		addChild(hplabel, 100);

		if (i == 0) {
			_players[i]->setPosition(700, 350);
		}
		else {
			_players[i]->setPosition(700, 220);
		}
		_players[i]->setScale(4);
		addChild(_players[i], 1000);
	}
}

void RoundFightScene::removeEnemyAndName(int x)
{
	_enemys.erase(_enemys.begin() + x);
	_enemyNames[x]->removeFromParentAndCleanup(true);
	_enemyNames.erase(_enemyNames.begin() + x);
}

void RoundFightScene::fightFinish()
{
	runAction(Sequence::createWithTwoActions(
		FadeOut::create(0.5f),
		CallFunc::create([]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
			GameManager::getInstance()->_bgmusicName.c_str(), true);
		Director::getInstance()->popScene();
	})));
}

void RoundFightScene::showInjuredNumber(const Vec2& pos, const int injured)
{
	_injuredLabel->setColor(Color3B::RED);
	_injuredLabel->setVisible(false);
	_injuredLabel->setPosition(pos.x, pos.y + 50);
	std::string text = "-" + Value(injured).asString();
	_injuredLabel->setString(text);
	_injuredLabel->setVisible(true);
	_injuredLabel->runAction(Sequence::create(
		MoveBy::create(0.8f, Vec2(0, 50)),
		CallFunc::create([=]() {
			_injuredLabel->setVisible(false);
		}),
		nullptr));
}

void RoundFightScene::showTreatNumber(const Vec2& pos, const int treat)
{
	_injuredLabel->stopActionByTag(123);
	_injuredLabel->setColor(Color3B::GREEN);
	_injuredLabel->setVisible(false);
	_injuredLabel->setPosition(pos.x, pos.y + 50);
	std::string text = "+" + Value(treat).asString();
	_injuredLabel->setString(text);
	_injuredLabel->setVisible(true);
	auto action = Sequence::create(
		MoveBy::create(0.8f, Vec2(0, 30)),
		CallFunc::create([=]() {
		_injuredLabel->setVisible(false);
	}),
		nullptr);
	action->setTag(123);
	_injuredLabel->runAction(action);
}