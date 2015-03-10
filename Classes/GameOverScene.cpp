#include "GameOverScene.h"
#include "TitleScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto bg = Sprite::create("Others/gameover.png");
	auto size = bg->getContentSize();
	bg->setScaleX(800 / size.width);
	bg->setScaleY(800 / size.height);
	bg->setPosition(400, 240);
	addChild(bg);

	runAction(Sequence::createWithTwoActions(
		DelayTime::create(1.0f),
		CallFunc::create([]() {
			auto scene = TitleScene::createScene();
			Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f, scene, false));
		})));
	return true;
}