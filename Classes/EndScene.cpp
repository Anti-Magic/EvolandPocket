#include "EndScene.h"
#include "PopDialog.h"
#include "GameManager.h"

USING_NS_CC;

Scene* EndScene::createScene()
{
	auto layer = EndScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto bg = Sprite::create("Others/end.png");
	bg->setPosition(400, 240);
	addChild(bg, 1);
	auto dialog = PopDialog::create();
	addChild(dialog, 1000);
	GameManager::getInstance()->setOperator(nullptr);
	auto strings = FileUtils::getInstance()->getValueMapFromFile("string.xml");
	for (int i = 1; i <= 9; i++) {
		auto name = "end" + Value(i).asString();
		auto string = strings[name].asString();
		auto label = Label::createWithSystemFont(string, "Consolas", 30);
		label->setColor(Color3B(32, 191, 219));
		auto size = label->getContentSize();
		label->setOpacity(0);
		addChild(label, 10);
		label->setPosition(size.width / 2 + 50, 430 - i * 35);
		float delay = 2.0f * i;
		label->runAction(Sequence::create(
			DelayTime::create(delay), 
			FadeIn::create(1.5f), 
			DelayTime::create(20.0f - delay),
			FadeOut::create(1.5f),
			nullptr));
	}
	for (int i = 10; i <= 14; i++) {
		auto name = "end" + Value(i).asString();
		auto string = strings[name].asString();
		auto label = Label::createWithSystemFont(string, "Consolas", 30);
		label->setColor(Color3B::RED);
		auto size = label->getContentSize();
		label->setOpacity(0);
		addChild(label, 10);

		label->setPosition(size.width / 2 + 400, 550 - i * 35);
		float delay = 3.0f + 2.0f * i;
		if (i >= 13) {
			delay -= 1.5f;
		}

		if (i == 14) {
			auto finishStr = strings["finishrate"].asString();
			label->runAction(Sequence::create(
				DelayTime::create(delay),
				FadeIn::create(1.5f),
				CallFunc::create([=]() {
					auto finishContent = finishStr + Value(GameManager::getInstance()->_boxCount).asString();
					auto finishRate = Label::createWithSystemFont(finishContent, "Consolas", 30);
					finishRate->setColor(Color3B::GREEN);
					finishRate->setPosition(150, 350);
					addChild(finishRate, 10);

					auto keyListener = EventListenerKeyboard::create();
					keyListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
						if (code == EventKeyboard::KeyCode::KEY_BACKSPACE
							|| code == EventKeyboard::KeyCode::KEY_ESCAPE) {
							dialog->pop("readyFinishEnd", "readyFinishEnd");
						}
					};
					getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
				}),
				DelayTime::create(2.0f),
				CallFunc::create([=]() {
					dialog->pop("readyFinishEnd", "readyFinishEnd");
				}),
				nullptr));
		}
		else {
			label->runAction(Sequence::create(
				DelayTime::create(delay),
				FadeIn::create(1.5f),
				nullptr));
		}
	}
	return true;
}