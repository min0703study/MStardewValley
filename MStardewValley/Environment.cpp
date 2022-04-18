#include "Stdafx.h"
#include "Environment.h"
#include "CropAnimation.h"
#include "TreeAnimation.h"

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
	
	bIsBroken = false;
	bIsDead = false;

	mAni = new MineRockAnimation;
	mAni->init(mRockType);
	mAni->playAniLoop(eRockAniStat::RA_IDLE);

	mHp = 30;
}

void Rock::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		mAni->playAniOneTime(eRockAniStat::RA_CRASH);
		bIsBroken = true;
	}
	else {
		mAni->playAniOneTime(eRockAniStat::RA_HIT);
	}
}

bool Rock::isBroken()
{
	return bIsBroken && !(mAni->isPlaying());
}

void Rock::update(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Rock::release(void)
{
}

void Rock::render()
{
	animation();
	mAni->render(getMemDc(), getRelX(), getRelY());
}

void Rock::animation()
{
	if (mAni->isOneTimeAniOver()) {
		if (bIsBroken) {
			bIsDead = true;
		}
		else {
			mAni->playAniLoop(eRockAniStat::RA_IDLE);
		}
	}
}

void Rock::draw()
{
}

void Tree::init(eTreeType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 3, 6, XS_CENTER, YS_BOTTOM);
	mTreeType = type;

	bIsBroken = false;
	bIsDead = false;

	mAni = new TreeAnimation;
	mAni->init(mTreeType);
	mAni->playAniLoop(eRockAniStat::RA_IDLE);

	mHp = 30;
}

void Tree::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		mAni->playAniOneTime(eRockAniStat::RA_CRASH);
		bIsBroken = true;
	}
	else {
		mAni->playAniOneTime(eRockAniStat::RA_HIT);
	}
}

bool Tree::isBroken()
{
	return bIsBroken && !(mAni->isPlaying());
}

void Tree::update(void)
{
}

void Tree::release(void)
{
}

void Tree::render()
{
	animation();
	draw();
}

void Tree::animation()
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	if (mAni->isOneTimeAniOver()) {
		if (bIsBroken) {
			bIsDead = true;
		}
		else {
			mAni->playAniLoop(eRockAniStat::RA_IDLE);
		}
	}
}

void Tree::draw()
{
	mAni->render(getRelX(), getRelY());
}