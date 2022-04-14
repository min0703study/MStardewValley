#pragma once
#include "TileObject.h"

class MineRockAnimation;
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

	RectF mTileRectF;
};

class Crop : public Environment 
{
public:
	void init(eCropType cropType, int tileX, int tileY);
	void update(void) override {};
	void render(void) override {};
	void render(float centerX, float centerY);
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
	string mCropId;
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
	void render(float centerX, float centerY);
	void release(void) override;

	Rock() {};
	~Rock() {};

private:
	eRockType mRockType;
	MineRockAnimation* mAni;
};

