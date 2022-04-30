#pragma once
#include "TileObject.h"
#include "MineRockAnimation.h"
#include "TreeAnimation.h"

class CropAnimation;

typedef struct tagHarvest {
	string ItemId;
	int Count;
} HarvestItem;

class Environment: public TileObject
{
public:
	Environment() {};
	virtual ~Environment() {};

	void init(int tileX, int tileY, int toIndexX, int toIndexY, eXStandard xStandard, eYStandard yStandard);
	virtual HarvestItem getHarvestItem();
protected:
	HarvestItem mHarvestItem;
private:
	bool bHarvested;
};

class Crop : public Environment 
{
public:
	void init(eCropType cropType, int tileX, int tileY);

	void render(void) override {
		animation();
		draw();
	};

	void draw(void) override;
	void animation(void) override;
	
	void release(void) override;
	
	void upStage();

	string harvesting();

	inline bool isHarvested() const { return bHarvested; }

	bool isMaxStage() { return mCurStage == mMaxStage; }
	
	eCropType getCropType() { return mCropType; }
	string getFruitItemId() { return mFruitId; }

	Crop() {};
	~Crop() {};

private:
	eCropType mCropType;
	CropAnimation* mAni;

	string mSeedId;
	string mFruitId;

	int mCurStage;
	int mMaxStage;

	bool bHarvested;
};

class Rock : public Environment
{
public:
	void init(eRockType type, int tileX, int tileY);
	void update(void) override;
	void render(void) override;
	void animation();
	void draw();
	void release(void) override;

	bool isBroken();
	void hit(int power);

	HarvestItem getHarvestItem() override { return mHarvestItem; };

	Rock() {};
	~Rock() {};

private:
	MineRockAnimation* mAni;
	eRockType mRockType;

	int mHp;
	
	bool bIsBroken;
	bool bIsDead;
};

class Tree : public Environment
{
public:
	void init(eTreeType type, int tileX, int tileY);
	void release(void) override;
	void render();
	void update(void) override;
	void animation();
	void draw();

	bool isBroken();
	void setTrans(bool flag);
	void hit(int power);

	HarvestItem getHarvestItem() override { return mHarvestItem; };

	Tree() {};
	~Tree() {};
private:
	TreeAnimation* mAni;
	eTreeType mTreeType;

	int mHp;

	bool bIsBroken;
	bool bIsDead;
};

class Weed : public Environment
{
public:
	void init(eWeedType type, int tileX, int tileY);
	void release(void) override;
	void render();
	void update(void) override;
	void animation();
	void draw();

	bool isCutOff();
	void hit();

	HarvestItem getHarvestItem() override { return mHarvestItem; };
	vector<ImageGp*> mVAni;

	Weed() {};
	~Weed() {};
private:
	TreeAnimation* mAni;
	eWeedType mWeedType;

	bool bIsCutOff;
	bool bIsDead;
};
