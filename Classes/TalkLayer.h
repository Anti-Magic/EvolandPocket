#ifndef __TALKLAYER_H__
#define __TALKLAYER_H__

#include "cocos2d.h"

class TalkLayer : public cocos2d::Sprite
{
public:
	void talk(const std::string& key);
	bool init();
	CREATE_FUNC(TalkLayer);
private:
	cocos2d::Label* _talkLabel;
	cocos2d::ValueMap _strings;
};

#endif