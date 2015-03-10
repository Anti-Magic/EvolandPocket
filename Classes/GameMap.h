#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "cocos2d.h"
#include "Tools.h"

class GameMap : public cocos2d::TMXTiledMap
{
public:
	static GameMap* create(const std::string& tmxFile);
	bool init(const std::string& tmxFile);
	void setPositionByTileCoord(const cocos2d::Vec2& tilecoord);
	void move(Tools::Direction dir);
	bool isPassage(const cocos2d::Vec2& tileCoord);
	bool isSaveArea(const cocos2d::Vec2& tileCoord);
	bool checkTrans(const cocos2d::Vec2& tileCoord);
	bool checkCutGrass(const cocos2d::Vec2& tileCoord);
	bool checkOpenBox(const cocos2d::Vec2& tileCoord);
	void removeBox(const cocos2d::Vec2& tileCoord);//ֻ�Ƴ���ͼ�ϵ����ӣ�������������
	void destroy(const cocos2d::Vec2& tileCoord); //�Ƴ���ͼ��ĳһ��
private:
	cocos2d::TMXLayer* _stopLayer;
	cocos2d::TMXLayer* _grassLayer;
	cocos2d::TMXLayer* _boxLayer;
	cocos2d::TMXLayer* _otherLayer; //�����㣬��������Ϊ���жϴ浵���ã�����Ҫ��
	cocos2d::TMXLayer* _transLayer;
	cocos2d::TMXObjectGroup* _objectGroup;
};

#endif