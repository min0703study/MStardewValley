#include "Stdafx.h"
#include "Environment.h"
#include "MineRockAnimation.h"
#include "CropAnimation.h"

void Environment::init(int tileX, int tileY, int toIndexX, int toIndexY)
{
	TileObject::init(tileX, tileY, toIndexX, toIndexY);
}

///////////////////////////////////////////////////////////////////////////////////
void Crop::init(eCropType cropType, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 0, 0);

	switch (cropType)
	{
	case eCropType::CT_PARSNIP: {
		mSeedId = ITEMCLASS->PARSNIP_SEED;
		mFruitId = ITEMCLASS->PARSNIP;
		break;
	}
	case eCropType::CT_BEEN: {
		mSeedId = ITEMCLASS->BEEN_SEED;
		mFruitId = ITEMCLASS->BEEN;
		break;
	}
	case eCropType::CT_CAULIFLOWER: {
		mSeedId = ITEMCLASS->CAULIFLOWER_SEED;
		mFruitId = ITEMCLASS->CAULIFLOWER;
		break;
	}
	case eCropType::CT_POTATO: {
		mSeedId = ITEMCLASS->POTATO_SEED;
		mFruitId = ITEMCLASS->POTATO;
		break;
	}
	default:
		break;
	}

	mCurStage = 0;
	mMaxStage = CROPSPRITE->getSpriteInfo()[cropType].MaxStage;

	mAni = new CropAnimation;
	mAni->init(cropType);
}
void Crop::upStage()
{
	if (mCurStage < mMaxStage) {
		mAni->chageStage(mCurStage);
		mCurStage++;
	}
}
string Crop::harvesting() {
	return mFruitId;
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
