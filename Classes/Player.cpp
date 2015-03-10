#include "Player.h"
#include "GameMap.h"
#include "GameConfig.h"
#include "GameManager.h"

USING_NS_CC;

bool Player::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	_gameManager = GameManager::getInstance();
	_faceto = Tools::Direction::NONE;
	return true;
}

void Player::setPositionByTileCoord(const Vec2& tilecoord)
{
	auto gamemap = _gameManager->getGameMap();
	if (gamemap == nullptr) {
		return;
	}
	Vec2 pos = Tools::tileCoordToPos(tilecoord);
	auto tileSize = gamemap->getTileSize();
	setPosition(pos.x + tileSize.width / 2,
		pos.y - tileSize.height / 2);
}

bool Player::move(Tools::Direction dir)
{
	GameManager::getInstance()->checkPlayerDied();
	if (dir == Tools::Direction::NONE) {
		return false;
	}
	Vec2 step = Tools::getStep(dir);
	Vec2 tarPos = getPosition() + step;
	Vec2 tarTileCoord = Tools::posToTileCoord(tarPos);
	if (_gameManager->getGameMap()->isPassage(tarTileCoord)) {
		_gameManager->_isMoving = true;
		_gameManager->checkSaveGame(tarTileCoord); //检查是否存档点，如果是就存档
		_gameManager->checkTransMap(tarTileCoord); //检查是否切换地图
		bool runMoveAnimate = false;
		if (!_gameManager->_isTriggering) {
			runMoveAnimate = true;
		}
		if (dir != _faceto) {
			_faceto = dir;
			runMoveAnimate = true;
			if (_gameManager->_isTriggering) {
				stopActionByTag(Tag_AttackAction);
			}
		}
		auto config = GameConfig::getInstance();
		if (runMoveAnimate) {
			auto animationName = config->getPlayerMoveName(dir);
			auto moveAnimation = AnimationCache::getInstance()
				->getAnimation(animationName);
			auto animate = Animate::create(moveAnimation);
			animate->setTag(Tag_MoveAnimate);
			runAction(animate);
		}
		auto move = MoveBy::create(config->timePerMove, step);
		runAction(move);
		return true;
	}
	if (dir != _faceto) {
		setFaceto(dir);
	}
	if (_gameManager->checkOpenBox(tarTileCoord)) {
		//这里的目的是使角色开箱子后停一会
		_gameManager->_isMoving = true;
	}
	return false;
}

void Player::attack(bool isAttack)
{
	if (!isAttack) {
		return;
	}
	
	/*std::string frameName =
		GameConfig::getInstance()->getPlayerAttackName(_faceto);
	auto frame = SpriteFrameCache::getInstance()
		->getSpriteFrameByName(frameName);*/
	stopActionByTag(Tag_MoveAnimate); //停止移动动画
	_gameManager->_isTriggering = true;
	_gameManager->cutGrass();
	_gameManager->killEnemy();

	/*
	setSpriteFrame(frame);
	auto attackAction = Sequence::create(
		DelayTime::create(0.2f),
		CallFunc::create([=]() {
			setFaceto(_faceto);
		}),
		DelayTime::create(0.1f),
		nullptr);
	*/

	auto config = GameConfig::getInstance();
	auto animation = AnimationCache::getInstance()
		->getAnimation(config->getPlayerAttackName(_faceto));

	auto attackAction = Sequence::createWithTwoActions(
		Animate::create(animation),
		DelayTime::create(config->timePerMove / 4));
	attackAction->setTag(Tag_AttackAction);
	runAction(attackAction);
}

Tools::Direction Player::getFaceto()
{
	return _faceto;
}

void Player::setFaceto(Tools::Direction dir)
{
	if (dir != Tools::Direction::NONE) {
		_faceto = dir;
		std::string frameName =
			GameConfig::getInstance()->getPlayerFacetoName(dir);
		auto frame = SpriteFrameCache::getInstance()
			->getSpriteFrameByName(frameName);
		setSpriteFrame(frame);
	}
}