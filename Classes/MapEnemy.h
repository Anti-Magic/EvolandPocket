#ifndef __MAPENEMY_H__
#define __MAPENEMY_H__

#include "cocos2d.h"
#include "Tools.h"

class MapEnemy : public cocos2d::Sprite
{
public:
	virtual ~MapEnemy() {}
	virtual bool init();
	virtual bool init(const std::string& filename);
	virtual void execute(float dlt);
	virtual void died();
	Tools::Direction getFaceto();
	void setFaceto(Tools::Direction dir);
	void setPositionByTileCoord(const cocos2d::Vec2& tileCoord);
protected:
	virtual void initMoveAnimation() = 0;

	std::string _moveNameHalf;
	float _timePerExecute;
	Tools::Direction _faceto;
};

#endif