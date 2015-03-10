#include "TalkLayer.h"
#include "DataService.h"

USING_NS_CC;

bool TalkLayer::init()
{
	if (!Sprite::initWithFile("Others/block.png")) {
		return false;
	}
	_strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
	
	_talkLabel = Label::createWithSystemFont("", "Consolas", 30);
	_talkLabel->setColor(Color3B::WHITE);
	_talkLabel->setPosition(400, 128 / 2);
	addChild(_talkLabel);

	setPosition(400, 600);
	setVisible(false);
	return true;
}

void TalkLayer::talk(const std::string& key)
{
	stopAllActions();
	setPosition(400, 600);
	setVisible(true);
	auto value = _strings[key].asString();
	_talkLabel->setString(value);
	auto move = MoveBy::create(0.2f, Vec2(0, -184));
	auto action = Sequence::create(
		move,
		DelayTime::create(3.0f),
		move->reverse(),
		CallFunc::create([=]() {
			setVisible(false);
		}),
		nullptr);
	runAction(action);
}