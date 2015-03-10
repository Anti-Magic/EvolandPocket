#include "PopDialog.h"
#include "MapCallBack.h"
#include "GameManager.h"
#include "GameSceneBase.h"

USING_NS_CC;

bool PopDialog::init()
{
	if (!Sprite::initWithFile("GUI/pop_bg.png")) {
		return false;
	}
	_ispop = false;
	setPosition(400, 600);
	setVisible(false);
	_strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
	_content = Label::createWithSystemFont("", "Consolas", 30);
	_content->setColor(Color3B::YELLOW);
	_content->setPosition(200, 130);
	addChild(_content, 1);

	auto bt_yes = MenuItemImage::create(
		"GUI/button_n1.png",
		"GUI/button_d1.png",
		"GUI/button_d1.png",
		[=](Ref* sender) {
			//this->push();
			if (_callback != "") {
				MapCallBack::getInstance()->executeTransCallBack(_callback);
				_callback = "";
			}
		});

	auto bt_no = MenuItemImage::create(
		"GUI/button_n1.png",
		"GUI/button_d1.png",
		"GUI/button_d1.png",
		[=](Ref* sender) {
			this->push();
		});

	auto buttonSize = bt_yes->getContentSize();
	Vec2 labelPos(buttonSize.width / 2, buttonSize.height / 2);

	std::string strYes = _strings["yes"].asString();
	auto lbYes = Label::createWithSystemFont(strYes, "Consolas", 30);
	lbYes->setPosition(labelPos);
	bt_yes->addChild(lbYes, 1);

	std::string strNo = _strings["no"].asString();
	auto lbNo = Label::createWithSystemFont(strNo, "Consolas", 30);
	lbNo->setPosition(labelPos);
	bt_no->addChild(lbNo, 1);

	bt_yes->setPosition(100, 50);
	bt_no->setPosition(300, 50);

	auto menu = Menu::create(bt_yes, bt_no, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 10);

	return true;
}

void PopDialog::pop(const std::string& key, const std::string& callback)
{
	if (!_ispop) {
		auto enemys = GameManager::getInstance()->getMapEnemys();
		for (auto e : enemys) {
			e->pause();
		}
		auto op = GameManager::getInstance()->getOperator();
		if (op != nullptr) {
			op->reset();
			op->getEventDispatcher()->pauseEventListenersForTarget(op);
		}

		_callback = callback;
		_content->setString(_strings[key].asString());
		setVisible(true);
		runAction(Sequence::createWithTwoActions(
			EaseBounceOut::create(MoveTo::create(1.0f, Vec2(400, 240))),
			CallFunc::create([&]() {
				_ispop = true;
		})));
	}
}

void PopDialog::push()
{
	if (_ispop) {
		auto enemys = GameManager::getInstance()->getMapEnemys();
		for (auto e : enemys) {
			e->resume();
		}
		auto op = GameManager::getInstance()->getOperator();
		if (op != nullptr) {
			op->getEventDispatcher()->resumeEventListenersForTarget(op);
		}
		runAction(Sequence::createWithTwoActions(
			EaseBackInOut::create(MoveTo::create(0.8f, Vec2(400, 600))),
			CallFunc::create([&]() {
				_ispop = false;
		})));
	}
}