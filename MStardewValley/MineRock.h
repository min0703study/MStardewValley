#pragma once
#include "GameObject.h"
#include "MineRockAnimation.h"

class MineRock: public GameObject
{
public:
	void init(string id, eRockType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	MineRock() {};
	~MineRock() {};

private:
	eRockType mStoneType;
	MineRockAnimation* mAni;
};

