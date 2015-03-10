#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include "cocos2d.h"

class Tools
{
public:
	enum class Direction
	{
		NONE = 0,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	//方向转化为字符串
	static std::string dirToString(Direction dir);

	//移动一步的距离（地图的一格）
	static cocos2d::Vec2 getStep(Direction dir);

	//把砖块坐标转化为坐标
	static cocos2d::Vec2 tileCoordToPos(const cocos2d::Vec2& tileCoord);

	//把坐标转化为砖块坐标
	static cocos2d::Vec2 posToTileCoord(const cocos2d::Vec2& pos);
};

#endif