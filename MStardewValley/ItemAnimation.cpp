#include "Stdafx.h"
#include "ItemAnimation.h"

#define WEAPON_UPDATE_SEC	3.0f;
#define TOOL_UPDATE_SEC 	3.0f;

void ItemAnimation::init(string itemId, eItemType type)
{
	mCurFrame = 0;
	mElapsedSec = 1.0f / 5;
}

void ItemAnimation::initWeapon(eWeaponType type)
{
	mCurAniStat = eItemStat::IS_GRAP;

	mCurFrame = 0;
	mElapsedSec = 0;

	mVCurAni = WEAPONSPRITE->getVAni(type);

	for (int i = 0; i < eItemStat::IS_END; i++) {
		mAniInfoList[i].StartIndex = WEAPONSPRITE->getSpriteInfo()[i].StartIndex;
		mAniInfoList[i].EndIndex = WEAPONSPRITE->getSpriteInfo()[i].EndIndex;
		mAniInfoList[i].IsNone = WEAPONSPRITE->getSpriteInfo()[i].IsNone;
		mAniInfoList[i].FrameUpdateSec = 1.0f / WEAPON_UPDATE_SEC;
	}
}

void ItemAnimation::initTool(eToolType toolType, eToolLevel toolLevel)
{
	mCurAniStat = eItemStat::IS_GRAP;

	mCurFrame = 0;
	mElapsedSec = 0;
	
	mVCurAni = TOOLSPRITE->getVAni(toolType, toolLevel);
	for (int i = 0; i < eItemStat::IS_END; i++) {
		mAniInfoList[i].StartIndex = TOOLSPRITE->getSpriteInfo()[i].StartIndex;
		mAniInfoList[i].EndIndex = TOOLSPRITE->getSpriteInfo()[i].EndIndex;
		mAniInfoList[i].IsNone = TOOLSPRITE->getSpriteInfo()[i].IsNone;
		mAniInfoList[i].FrameUpdateSec = 1.0f / TOOL_UPDATE_SEC;
	}
}

void ItemAnimation::release()
{
}

void ItemAnimation::changeStatAni(int changeStat)
{
	mCurAniStat = changeStat;
	if (!mAniInfoList[mCurAniStat].IsNone) {
		mCurFrame = mAniInfoList[mCurAniStat].StartIndex;
	}
}

void ItemAnimation::frameUpdate(float elapsedTime)
{
	if (!mAniInfoList[mCurAniStat].IsNone) {
		if (elapsedTime < 0) return;

		mElapsedSec += elapsedTime;

		if (mElapsedSec > mAniInfoList[mCurAniStat].FrameUpdateSec) {
			mElapsedSec = 0;

			mCurFrame++;
			if (mCurFrame >= mAniInfoList[mCurAniStat].EndIndex) {
				mCurFrame = mAniInfoList[mCurAniStat].StartIndex;
			}
		}
	}
}

void ItemAnimation::render(HDC hdc, RectF rcF)
{
	if (!mAniInfoList[mCurAniStat].IsNone) {
		mVCurAni[mCurFrame]->render(hdc, rcF.GetLeft(), rcF.GetTop());	}
}


void ItemAnimation::render(HDC hdc, float x, float y)
{
	if (!mAniInfoList[mCurAniStat].IsNone) {
		GDIPLUSMANAGER->drawRectF(hdc, mVCurAni[mCurFrame]->getRectF(x, y));
		mVCurAni[mCurFrame]->render(hdc, x, y, XS_CENTER, YS_CENTER);
	}
}