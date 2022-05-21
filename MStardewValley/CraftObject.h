#pragma once
#include "TileObject.h"

class FurnaceAnimation;

class CraftObject : public TileObject {
public:
	virtual void init(int tileX, int tileY, int xCount, int yCount, eXStandard xStandard, eYStandard yStandard);
	virtual void update();
	virtual void render();
	virtual void release();

	virtual void hit();

	bool bPlaced;

	inline bool isPlaced() const {return bPlaced;}

	CraftObject() {};
	virtual ~CraftObject() {};
};

class Furance : public CraftObject
{
public:
	void init(int tileX, int tileY);
	void update();
	void render();
	void release();

	bool reqStartSmelting();
	string pickUpItem();
	inline eFuranceState getCurStat() const { return mCurStat; };

	Furance() {};
	~Furance() {};
private:
	string	mSmeltingItem;
	float	mSmeltingOverSec;
	float	mSmeltingCurSec;

	eFuranceState mCurStat;
	FurnaceAnimation* mAni;

	ImageGp* mOverBubble;
	int mEffectIndex;
};

class Box : public CraftObject
{

};

