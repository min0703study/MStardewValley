#include "Stdafx.h"
#include "Environment.h"
#include "MineRockAnimation.h"
#include "CropAnimation.h"

void Environment::init(int tileX, int tileY, int toIndexX, int toIndexY)
{
	TileObject::init(tileX, tileY, toIndexX, toIndexY);
}

///////////////////////////////////////////////////////////////////////////////////

void Crop::init(eCropType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 0, 0);

	mCropType = type;
	mCurStage = 0;
	mMaxStage = 6;

	mAni = new CropAnimation;
	mAni->init(type);
}

void Crop::update(void)
{
}

void Crop::render(void)
{
}

void Crop::render(float tileX, float tileY)
{
	float centerX = tileX + (TILE_SIZE / 2.0f);
	float bottomY = tileY + TILE_SIZE;

	mAni->render(getMemDc(), centerX, bottomY);
}

void Crop::release(void)
{
}

void Crop::upStage()
{
	if (mCurStage < mMaxStage) {
		mCurStage++;
		mAni->chageStage(mCurStage);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
void Rock::init(eRockType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 0, 0);
	mRockType = type;

	mAni = new MineRockAnimation;
	mAni->init(mRockType);
}

void Rock::update(void)
{
}

void Rock::render(void)
{
}

void Rock::release(void)
{
}

void Rock::render(float centerX, float centerY)
{
	mAni->render(getMemDc(), centerX, centerY);
}
