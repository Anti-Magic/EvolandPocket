#ifndef __MAPENEMY_3_H__
#define __MAPENEMY_3_H__

#include "MapEnemy.h"

class MapEnemy_3 : public MapEnemy
{
public:
	static MapEnemy_3* create();
	bool init(const std::string& fileName) override;
private:
	void initMoveAnimation() override;
};

#endif