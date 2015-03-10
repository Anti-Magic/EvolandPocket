#include "TipsLayer.h"
#include "DataService.h"

USING_NS_CC;

bool TipsLayer::init()
{
	if (!Sprite::initWithFile("Others/tips.png")) {
		return false;
	}
	
	auto lock = Sprite::create("Others/lock.png");
	lock->setPosition(100, 50);
	addChild(lock, 1);

	auto getLabel = Label::createWithSystemFont("", "Consolas", 30);
	getLabel->setString(FileUtils::getInstance()->getValueMapFromFile("string.xml")["get"].asString());
	getLabel->setPosition(200, 65);
	addChild(getLabel, 1);

	_nameLabel = Label::createWithSystemFont("", "Consolas", 30);
	//_nameLabel->enableOutline(Color4B::RED);
	_nameLabel->setColor(Color3B::RED);
	_nameLabel->setPosition(0, 65);
	addChild(_nameLabel, 1);

	_infoLabel = Label::createWithSystemFont("", "Consolas", 25);
	//_infoLabel->enableOutline(Color4B::RED);
	_infoLabel->setColor(Color3B::YELLOW);
	_infoLabel->setPosition(0, 35);
	addChild(_infoLabel, 1);
	setPosition(400, -100);
	return true;
}

void TipsLayer::reset()
{
	stopAllActions();
	setPosition(400, -100);
}

void TipsLayer::makeTips(const std::string& key)
{
	reset();
	std::string name;
	std::string info;
	DataService::getInstance()->getTipsWord(key, name, info);
	_nameLabel->setString(name);
	_infoLabel->setString(info);

	_nameLabel->setPositionX(270 + _nameLabel->getContentSize().width / 2);
	_infoLabel->setPositionX(140 + _infoLabel->getContentSize().width / 2);

	auto action = Sequence::create(
		MoveTo::create(0.2f, Vec2(400, 50)),
		DelayTime::create(4.0f),
		MoveTo::create(0.2f, Vec2(400, -100)),
		nullptr);
	runAction(action);
}