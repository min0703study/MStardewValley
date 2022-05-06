#include "Stdafx.h"
#include "Environment.h"
#include "CropAnimation.h"
#include "TreeAnimation.h"

void Environment::init(int tileX, int tileY, int toIndexX, int toIndexY, eXStandard xStandard, eYStandard yStandard)
{
	TileObject::init(tileX, tileY, toIndexX, toIndexY, xStandard, yStandard);
	bHarvested = false;
}

void Environment::setHarvestItem(HarvestItem harvestItem)
{
	mHarvestItem = harvestItem;
}

string Environment::harvesting()
{
	return "";
}

///////////////////////////////////////////////////////////////////////////////////
void Crop::init(eCropType cropType, int tileX, int tileY)
{
	Environment::init(tileX, tileY, 1, 2, XS_LEFT, YS_CENTER);

	bHarvested = false;

	mCropType = cropType;
	switch (mCropType)
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
	} default:
		break;
	}

	mCurStage = 0;
	mMaxStage = CROPSPRITE->getSpriteInfo()[cropType].MaxStage;

	mAni = new CropAnimation;
	mAni->init(cropType);
}

void Crop::draw(void)
{
	mAni->render(getMemDc(), getRelX(), getRelY());
}

void Crop::animation(void)
{

}

void Crop::upStage()
{
	if (mCurStage < mMaxStage) {
		mAni->chageStage(mCurStage);
		mCurStage++;
	}
}

string Crop::harvesting() {
	bHarvested = true;
	return mFruitId;
}

void Crop::release(void)
{
	Environment::release();
}

//////////////////////////////////////////////////////////////////////////////////////

void Rock::init(eRockType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 0, 0);
	mRockType = type;
	
	bIsBroken = false;

	mAni = new MineRockAnimation;
	mAni->init(mRockType);
	mAni->playAniLoop(eRockAniStat::RA_IDLE);

	switch (type) {
	case RT_NORMAL_1:
	case RT_NORMAL_2:
	case RT_NORMAL_3:
	case RT_NORMAL_4:
	case RT_NORMAL_5:
	case RT_NORMAL_6:
		setHarvestItem(HarvestItem(ITEMCLASS->STONE_NORMAL, 1));
		break;
	case RT_COPPER:
		setHarvestItem(HarvestItem(ITEMCLASS->COPPER, 1));
		break;
	case RT_IRON:
		setHarvestItem(HarvestItem(ITEMCLASS->IRON, 1));
		break;
	case RT_GOLD:
		setHarvestItem(HarvestItem(ITEMCLASS->GOLD, 1));
		break;
	}


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
	mAni->render(getMemDc(), getRelRectF().GetLeft(), getRelRectF().GetTop());
}

void Rock::animation()
{
	if (mAni->isOneTimeAniOver()) {
		if (!bIsBroken) {
			mAni->playAniLoop(eRockAniStat::RA_IDLE);
		}
	}
}

void Rock::draw()
{
}

///////////////////////////////////////////////////////////////////////////////

void Tree::init(eTreeType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 3, 6, XS_CENTER, YS_BOTTOM);
	mTreeType = type;

	bIsTopBroken = false;
	bIsStumpBroken = false;

	mAni = new TreeAnimation;
	mAni->init(mTreeType);
	mAni->playAniLoop(eTreeAniStat::TAS_IDLE);

	setHarvestItem(HarvestItem(ITEMCLASS->WOOD, 3));

	mHp = 30;
}

void Tree::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		mAni->playAniOneTime(eTreeAniStat::TAS_CRASH);
		bIsTopBroken = true;
	}
	else {
		mAni->playAniOneTime(eTreeAniStat::TAS_HIT);
	}
}

bool Tree::collisionCheck()
{
	return PLAYER->getAbsRectF().Intersect(PLAYER->getAbsRectF());
}

void Tree::setTrans(bool flag)
{
	//mAni->playAniLoop(flag ? eTreeAniStat::TAS_IDLE : eTreeAniStat::TAS_TRANS);
}

void Tree::update(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
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
		if (bIsTopBroken) {
			mAni->playAniLoop(eTreeAniStat::TAS_STUMP_IDLE);
		}
		else {
			mAni->playAniLoop(eTreeAniStat::TAS_IDLE);
		}
	}
}

void Tree::draw()
{
	mAni->render(getRelCenterX(), getRelRectF().GetBottom());
}

/////////////////////////////////

void Weed::init(eWeedType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 1, 1, XS_CENTER, YS_BOTTOM);
	mWeedType = type;

	mVAni = MINESSPRITE->getVWeedAni(type);

	setHarvestItem(HarvestItem(ITEMCLASS->FIBER, 1));
	bIsCutOff = false;

}

void Weed::release(void)
{
}

void Weed::render()
{
	mVAni[0]->render(getRelRectF().GetLeft(), getRelRectF().GetTop());
}

void Weed::update(void)
{
}

void Weed::animation()
{
}

void Weed::draw()
{
}

bool Weed::isCutOff()
{
	return bIsCutOff;
}

void Weed::hit()
{
	bIsCutOff = true;
}
