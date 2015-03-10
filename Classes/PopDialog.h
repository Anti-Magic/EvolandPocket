#ifndef __POPDIALOG_H__
#define __POPDIALOG_H__

#include "cocos2d.h"

class PopDialog : public cocos2d::Sprite
{
public:
	bool init();
	CREATE_FUNC(PopDialog);
	void pop(const std::string& key, const std::string& callback);
	void push();
private:
	bool _ispop;
	std::string _callback;
	cocos2d::Label* _content;
	cocos2d::ValueMap _strings;
};

#endif