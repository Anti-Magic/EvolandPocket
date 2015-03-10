#ifndef __MAPENEMY_2_H__
#define __MAPENEMY_2_H__

#include "MapEnemy.h"

class MapEnemy_2 : public MapEnemy
{
public:
	static MapEnemy_2* create();
	bool init(const std::string& fileName) override;
private:
	void initMoveAnimation() override;
};

#endif