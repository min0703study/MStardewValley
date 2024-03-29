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
	bHarvested = true;
	return "";
}

///////////////////////////////////////////////////////////////////////////////////
void Crop::init(eCropType cropType, int tileX, int tileY)
{
	Environment::init(tileX, tileY, 1, 2, XS_LEFT, YS_CENTER);

	bKeepsProducing = false;

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
		bKeepsProducing = true;
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
	if (mCropType == CT_BEEN) {
		if (mCurStage < (mMaxStage - 2)) {
			mCurStage++;
			mAni->chageStage(mCurStage);
		}
	} else {
		if (mCurStage < mMaxStage - 1) {
			mCurStage++;
			mAni->chageStage(mCurStage);
		}
	}
}

string Crop::harvesting() {
	bHarvested = true;
	if (mCropType == CT_BEEN) {
		mAni->chageStage(mCurStage + 1);
	}
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
	mAni->playAniLoop(eRockAniState::RA_IDLE);

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
		mAni->playAniOneTime(eRockAniState::RA_CRASH);
		bIsBroken = true;
	}
	else {
		mAni->playAniOneTime(eRockAniState::RA_HIT);
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
			mAni->playAniLoop(eRockAniState::RA_IDLE);
		}
	}
}

void Rock::draw()
{
}

///////////////////////////////////////////////////////////////////////////////

void Tree::init(eTreeType type, int tileX, int tileY)
{
	Environment::init(tileX, tileY, 3, 6, XS_CENTER, YS_BOTTOM);

	mTreeType = type;

	bIsTopBroken = false;
	bIsStumpBroken = false;
	bIsTopBrokenAniOver = false;
	mAni = new TreeAnimation;
	mAni->init(mTreeType);
	mAni->playAniLoop(eTreeAniState::TAS_IDLE);

	setHarvestItem(HarvestItem(ITEMCLASS->WOOD, 3));

	getAbsRectF().GetBounds(&mTreeTopRectF);
	mTreeTopRectF.Height -= TILE_SIZE;

	bIsTrans = false;

	mHp = 30;
}

void Tree::hit(int power)
{
	mHp -= power;
	if (mHp <= 0) {
		if (!bIsTopBroken) {
			mHp = 30;
			mAni->playAniOneTime(eTreeAniState::TAS_CRASH);
			bIsTopBroken = true;
		}
		else {
			bIsStumpBroken = true;
		}
	} else {
		setHitAni();
	}
}

void Tree::setIdleAni()
{
	if (bIsTrans) {
		mAni->playAniLoop(eTreeAniState::TAS_TRANS);
	} else if (bIsTopBroken) {
		mAni->playAniLoop(eTreeAniState::TAS_STUMP_IDLE);
	} else {
		mAni->playAniLoop(eTreeAniState::TAS_IDLE);
	}
}

void Tree::setHitAni()
{
	if (bIsTopBroken) {
		mAni->playAniOneTime(eTreeAniState::TAS_STUMP_HIT);
	} else {
		mAni->playAniOneTime(eTreeAniState::TAS_HIT);
	}
}

bool Tree::collisionCheck()
{
	return bIsTopBroken || mTreeTopRectF.Contains(PLAYER->getAbsRectF());
}

void Tree::setTrans(bool flag)
{
	if (!bIsTopBroken && bIsTrans != flag) {
		bIsTrans = flag;
		setIdleAni();
	}
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
		if (bIsTopBroken) bIsTopBrokenAniOver = true;
		if (!bIsStumpBroken) {
			setIdleAni();
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
