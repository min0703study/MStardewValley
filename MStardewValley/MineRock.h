#pragma once
#include "GameObject.h"
#include "MineRockAnimation.h"

class MineRock: public GameObject
{
public:
	void Init(string id, eMineStoneType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	MineRock() {};
	~MineRock() {};

private:
	eMineStoneType mStoneType;
	MineRockAnimation* mAni;
};

