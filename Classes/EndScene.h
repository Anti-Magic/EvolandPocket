#ifndef __ENDSCENE_H__
#define __ENDSCENE_H__

#include "cocos2d.h"

class EndScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init();
	CREATE_FUNC(EndScene);
private:
};

#endif