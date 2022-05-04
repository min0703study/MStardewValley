#pragma once
#include "TileObject.h"

class FuranceAnimaiton;

class Furance : public TileObject
{
public:
	void init(int tileX, int tileY, eXStandard xStandard, eYStandard yStandard);
	void update();
	void render();
	void release();

	bool reqStartSmelting();
	string pickUpItem();
private:
	string	mSmeltingItem;
	float	mSmeltingCount;

	eFuranceStat mCurStat;
	FuranceAnimaiton* mAni;
};

class Box : public TileObject
{

};

