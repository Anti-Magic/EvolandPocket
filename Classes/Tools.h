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

	//����ת��Ϊ�ַ���
	static std::string dirToString(Direction dir);

	//�ƶ�һ���ľ��루��ͼ��һ��
	static cocos2d::Vec2 getStep(Direction dir);

	//��ש������ת��Ϊ����
	static cocos2d::Vec2 tileCoordToPos(const cocos2d::Vec2& tileCoord);

	//������ת��Ϊש������
	static cocos2d::Vec2 posToTileCoord(const cocos2d::Vec2& pos);
};

#endif