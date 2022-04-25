#pragma once
#include "TileObject.h"
#include "MineRockAnimation.h"
#include "TreeAnimation.h"

class CropAnimation;

class Environment: public TileObject
{
public:
	void init(int tileX, int tileY, int toTileX, int toTileY);

	Environment() {};
	virtual ~Environment() {};
private:
	int mTileX;
	int mTileY;

protected:
	int mStartRelX;
	int mStartRelY;

	inline float getRelX() { return mStartRelX - CAMERA->getX(); };
	inline float getRelY() { return mStartRelY - CAMERA->getY(); };

	RectF mTileRectF;
};

class Crop : public Environment 
{
public:
	void init(eCropType cropType, int tileX, int tileY);
	void update(void) override {};
	void render(void) override;
	void release(void) override;
	void upStage();

	string harvesting();

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
};

class Rock : public TileObject
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

	Rock() {};
	~Rock() {};

private:
	MineRockAnimation* mAni;
	eRockType mRockType;
	int mHp;
	
	bool bIsBroken;
	bool bIsDead;
};

class Tree : public TileObject
{
public:
	void init(eTreeType type, int tileX, int tileY);
	void release(void) override;
	void render();
	void update(void) override;
	void animation();
	void draw();

	bool isBroken();
	void hit(int power);

	Tree() {};
	~Tree() {};
private:
	TreeAnimation* mAni;
	eTreeType mTreeType;
	int mHp;

	bool bIsBroken;
	bool bIsDead;
};

