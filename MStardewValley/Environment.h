#pragma once
#include "TileObject.h"
#include "MineRockAnimation.h"
#include "TreeAnimation.h"

class CropAnimation;

typedef struct tagHarvest {
	string ItemId;
	int Count;
	tagHarvest(string itemId, int count) : ItemId(itemId), Count(count) {}
	tagHarvest() : ItemId(""), Count(-1) {}
} HarvestItem;

class Environment: public TileObject
{
public:
	Environment() {};
	virtual ~Environment() {};

	void init(int tileX, int tileY, int toIndexX, int toIndexY, eXStandard xStandard, eYStandard yStandard);
	void setHarvestItem(HarvestItem harvestItem);

	inline HarvestItem getHarvestItem() { 
		bHarvested = true;
		return mHarvestItem; 
	};
	inline bool isHarvested() const { return bHarvested; }
protected:
	virtual string harvesting();
	bool bHarvested;
private:
	HarvestItem mHarvestItem;
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
	string harvesting() override;

	bool isMaxStage() { return mCurStage == mMaxStage; }
	inline bool isKeepsProducing() const { return bKeepsProducing; }
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

	bool bKeepsProducing;
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

	void hit(int power);
	inline bool isBroken() const { return bIsBroken && !(mAni->isPlaying()); };
	
	Rock() {};
	~Rock() {};

private:
	MineRockAnimation* mAni;
	eRockType mRockType;

	int mHp;
	
	bool bIsBroken;
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

	inline bool isStumpBroken() const { return bIsTopBroken && bIsStumpBroken; };
	inline bool isTopBroken() const { return bIsTopBroken && bIsTopBrokenAniOver; };

	bool collisionCheck();
	void setTrans(bool flag);
	void hit(int power);
	void setIdleAni();
	void setHitAni();

	inline HarvestItem getTopHarvestItem() { return getHarvestItem(); };

	Tree() {};
	~Tree() {};
private:
	TreeAnimation* mAni;
	eTreeType mTreeType;

	RectF mTreeTopRectF;

	int mHp;

	bool bIsTrans;
	bool bIsTopBroken;
	bool bIsTopBrokenAniOver;
	bool bIsStumpBroken;
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

	vector<ImageGp*> mVAni;

	Weed() {};
	~Weed() {};
private:
	TreeAnimation* mAni;
	eWeedType mWeedType;

	bool bIsCutOff;
	bool bIsDead;
};
