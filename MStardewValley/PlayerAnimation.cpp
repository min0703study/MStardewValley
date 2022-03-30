#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init()
{
	mSprite = new PlayerSprite;
	mSprite->init();

	mElapsedSec = 0;
	mPlayCount = 0;

	tempX = CAMERA_X / 2;
	tempY = CAMERA_Y / 2;
}

void PlayerAnimation::changeAni(eGameDirection direction, int changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;
	bLoopFlag = 1;

	if (mCurDirection != direction) {
		mCurDirection = direction;
		mCurStat = changeStat;
		mVCurAni = mSprite->getSpriteAction(direction, changeStat);
		mVCurOverlayPosition = mSprite->getOverayAction(changeStat);
		mCurOvelayPotion = mVCurOverlayPosition[0];
		mCurHair = mSprite->getHairImg(direction);
		mCurCloth = mSprite->getClothImg(direction);


		auto mKeyAniInfo = mAniInfo.find(changeStat);
		if (mKeyAniInfo != mAniInfo.end())
		{
			mCurAniInfo = mKeyAniInfo->second;
		}
	}
}
void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;
	mElapsedSec += elapsedTime;

	if (mElapsedSec > mCurAniInfo->FrameUpdateSec) {
		mElapsedSec = 0;

		/*
		mCurFrame++;
		if (mCurFrame >= mCurAniInfo->MaxFrameCount) {
			mCurFrame = 0;
			mPlayCount++;
		}
		*/

		if (bLoopFlag) {
			mCurFrame++;
			if (mCurFrame >= mCurAniInfo->MaxFrameCount) {
				mCurFrame = mCurAniInfo->MaxFrameCount - 2;
				bLoopFlag = false;
			}
		}
		else {
			mCurFrame--;
			if (mCurFrame <= 0) {
				mCurFrame = 0;
				bLoopFlag = true;
				mPlayCount++;
			}
		}

		mCurOvelayPotion = mVCurOverlayPosition[mCurFrame];
	}
}

void PlayerAnimation::setAniInfo(int stat, float frameUpdateSec, float maxFrameCount, float allFrameCount)
{
	auto mKeyAniInfo = mAniInfo.find(stat);
	if (mKeyAniInfo == mAniInfo.end())
	{
		mAniInfo.insert(make_pair(stat, new AniInfo(
			frameUpdateSec,
			maxFrameCount,
			allFrameCount
		)));
	}

}

void PlayerAnimation::render(HDC hdc, float x, float y)
{
	if (KEYMANAGER->isOnceKeyDown('A')) {

		MY_UTIL::log(to_string(tempX - x) + "///");
		MY_UTIL::log(to_string(tempY - y) + "///");

		MY_UTIL::log(to_string(mVCurAni[mCurFrame]->getWidth() - mCurHair->getWidth()) + "///");
		MY_UTIL::log(to_string(mVCurAni[mCurFrame]->getHeight() - mCurHair->getHeight()) + "///");
	}

	mVCurAni[mCurFrame]->render(hdc, x, y);
	mVCurAni[mCurFrame + mCurAniInfo->MaxFrameCount]->render(hdc, x, y);
	mVCurAni[mCurFrame + mCurAniInfo->MaxFrameCount * 2]->render(hdc, x, y);

	//mCurHair->render(hdc, tempX + mCurOvelayPotion.HairX, tempY + mCurOvelayPotion.HairY);
	//GDIPLUSMANAGER->drawRectF(hdc, tempX, tempY, mCurHair->getWidth(), mCurHair->getHeight(), Color(0,0,0), Color(100,100,100, 70));

	//mCurCloth->render(hdc, x + mCurOvelayPotion.ClothX + 12, y + mCurOvelayPotion.ClothY + 45);
}

void PlayerAnimation::update()
{
	if (KEYMANAGER->isOnceKeyDown('I')) {
		tempY -= 1;
	}

	if (KEYMANAGER->isOnceKeyDown('K')) {
		tempY += 1;
	}

	if (KEYMANAGER->isOnceKeyDown('J')) {
		tempX -= 1;
	}

	if (KEYMANAGER->isOnceKeyDown('L')) {
		tempX += 1;
	}

	if (KEYMANAGER->isOnceKeyDown('N')) {
		mCurHair->setSizeRatio(0.9);
	}

	if (KEYMANAGER->isOnceKeyDown('M')) {
		mCurHair->setSizeRatio(1.1);
	}	

}
