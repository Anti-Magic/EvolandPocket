#include "BossFightScene.h"
#include "RoundPlayer_1.h"
#include "RoundPlayer_2.h"
#include "RoundEnemyBoss.h"
#include "RoundEnemy_1.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* BossFightScene::createScene()
{
	auto layer = BossFightScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

bool BossFightScene::init()
{
	_roundNum = 1;
	std::vector<RoundRole*> enemys;
	enemys.push_back(RoundEnemyBoss::create());
	std::vector<RoundRole*> players;
	auto player1 = RoundPlayer_1::create();
	players.push_back(player1);
	auto player2 = RoundPlayer_2::create();
	players.push_back(player2);
	if (!RoundFightScene::init(enemys, players, "Others/bg_round2.png")) {
		return false;
	}
	_allowEscape = false;
	_talkLayer = TalkLayer::create();
	addChild(_talkLayer, 10001);
	_tipsLayer = TipsLayer::create();
	addChild(_tipsLayer, 10001);

	_tipsLayer->makeTips("boss");

	_players[0]->_power = 2;
	_players[1]->_power = 1;
	return true;
}

void BossFightScene::changePowers()
{
	switch (_roundNum) {
	case 1:
		_bossTarget = 0;
		_players[0]->_power = 2;
		_enemys[0]->_power = 45;
		break;

	case 2: {
		_tipsLayer->makeTips("bossAnimation");
		auto animation = AnimationCache::getInstance()->getAnimation("bossAnimation");
		_enemys[0]->runAction(Animate::create(animation));
		_bossTarget = 0;
		_players[0]->_power = 2;
		_enemys[0]->_power = 45;
		break;
	}
		
	case 3:
		_bossTarget = 1;
		_players[0]->_power = 2;
		_enemys[0]->_power = 999;
		break;
	case 4:
		_bossTarget = 0;
		_players[0]->_power = 20;
		_enemys[0]->_power = 15;
		break;
	default:
		break;
	}
	_roundNum++;
}

void BossFightScene::initEnemysAndPlayers()
{
	auto label = Label::createWithSystemFont("", "Consolas", 28);
	label->setString(_strings[_enemys[0]->_roleName].asString());
	label->setPosition(100, 115);
	_enemyNames.push_back(label);
	addChild(label, 100);
		
	_enemys[0]->setPosition(Vec2(150, 300));
	_enemys[0]->setScale(3);
	addChild(_enemys[0], 1000);
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

void BossFightScene::playerRound()
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

void BossFightScene::enemyRound()
{
	_tipLabel->setString("");
	_buttons->setVisible(false);
	_buttons->setEnabled(false);
	getEventDispatcher()->pauseEventListenersForTarget(this);
	pointer_player = -1;
	auto action = getEnemyRoundAction();
	runAction(action);
	changePowers();
}

void BossFightScene::fightFinish()
{
	runAction(Sequence::createWithTwoActions(
		FadeOut::create(0.5f),
		CallFunc::create([]() {
			Director::getInstance()->popScene();
	})));
}

Action* BossFightScene::getEnemyRoundAction()
{
	Vector<FiniteTimeAction*> actions;

	if (_roundNum == 3) {
		actions.pushBack(CallFunc::create([=]() {
			_talkLayer->talk("boss1");
		}));
		actions.pushBack(DelayTime::create(2.0f));
	}

	actions.pushBack(DelayTime::create(0.5f));
	auto act = CallFunc::create([=]() {
		_enemys[0]->attack(Tools::Direction::RIGHT);
		showInjuredNumber(_players[_bossTarget]->getPosition(), _enemys[0]->_power);
		if (_players[_bossTarget]->injured(_enemys[0]->_power)) {
			_playerHps[_bossTarget]->setString(Value(_players[_bossTarget]->_hp).asString());
		}
		else {
			_players.erase(_players.begin() + _bossTarget);
			_playerHps[_bossTarget]->setString("0");
			_playerHps.erase(_playerHps.begin() + _bossTarget);
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

	if (_roundNum == 3) {
		actions.pushBack(DelayTime::create(3.0f));
		actions.pushBack(CallFunc::create([=]() {
			_talkLayer->talk("girl4");
		}));
		actions.pushBack(DelayTime::create(3.0f));
		actions.pushBack(CallFunc::create([=]() {
			_talkLayer->talk("girl5");
		}));
		actions.pushBack(DelayTime::create(3.5f));
		auto act = CallFunc::create([=]() {
			_players[0]->treat(100);
			showTreatNumber(_players[0]->getPosition(), 100);
			_playerHps[0]->setString(Value(_players[0]->_hp).asString());
		});
		actions.pushBack(act);
		actions.pushBack(DelayTime::create(3.0f));
		actions.pushBack(CallFunc::create([=]() {
			_talkLayer->talk("girl6");
		}));
		actions.pushBack(DelayTime::create(2.5f));
		actions.pushBack(CallFunc::create([=]() {
			_tipsLayer->makeTips("badMusic");
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				audio->preloadBackgroundMusic("Music/llzg.OGG");
				audio->playBackgroundMusic("Music/llzg.OGG", true);
			#else
				audio->preloadBackgroundMusic("Music/llzg.mp3");
				audio->playBackgroundMusic("Music/llzg.mp3", true);
			#endif
		}));
	}

	if (_roundNum == 4) {
		actions.pushBack(CallFunc::create([=]() {
			_tipsLayer->makeTips("awaken");
		}));
		actions.pushBack(DelayTime::create(1.0f));
	}

	actions.pushBack(CallFunc::create([&]() {
		pointer_player = 0;
		playerRound();
	}));
	
	auto result = Sequence::create(actions);
	return result;
}