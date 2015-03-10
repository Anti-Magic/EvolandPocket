#ifndef __MAPENEMY_1_H__
#define __MAPENEMY_1_H__

#include "MapEnemy.h"

class MapEnemy_1 : public MapEnemy
{
public:
	static MapEnemy_1* create();
	bool init(const std::string& fileName) override;
private:
	void initMoveAnimation() override;
};

#endif