#ifndef __TIPSLAYER_H__
#define __TIPSLAYER_H__

#include "cocos2d.h"

class TipsLayer : public cocos2d::Sprite
{
public:
	void makeTips(const std::string& key);
	void reset();
	bool init();
	CREATE_FUNC(TipsLayer);
private:
	cocos2d::Label* _nameLabel;
	cocos2d::Label* _infoLabel;
};

#endif