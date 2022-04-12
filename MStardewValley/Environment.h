#pragma once
#include "TileObject.h"
class Environment: public TileObject
{
public:
	void init(int tileX, int tileY, int toTileX, int toTileY);

	Environment() {};
	virtual ~Environment() {};
private:
	int mTileX;
	int mTileY;
};

class Crop : public Environment 
{
public:
	void init(eCropType type, int tileX, int tileY);
	void update(void) override;
	void render(void) override;
	void render(float centerX, float centerY);
	void release(void) override;

	Crop() {};
	~Crop() {};

private:
	eCropType mCropType;
	//CropAnimation* mCropAni;
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

