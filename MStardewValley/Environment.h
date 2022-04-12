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
	void init(eCropType type, int tileX, int tileY);
	void update(void) override;
	void render(void) override;
	void render(float centerX, float centerY);
	void release(void) override;
	void upStage();

	bool isMaxStage() { return mCurStage == mMaxStage; }

	Crop() {};
	~Crop() {};

private:
	eCropType mCropType;
	CropAnimation* mAni;

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

