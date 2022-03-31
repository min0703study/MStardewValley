#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init(int initStat, eGameDirection initDirection)
{
	mSprite = new PlayerSprite;
	mSprite->init();

	mElapsedSec = 0;
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = initStat;
	mCurAniDirection = initDirection;

	mVCurAni = mSprite->getSpriteAction(mCurAniDirection, mCurAniStat);
}

void PlayerAnimation::changeStatAni(int changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = changeStat;
	mVCurAni = mSprite->getSpriteAction(mCurAniDirection, changeStat);
}

void PlayerAnimation::changeDirectionAni(eGameDirection direction)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniDirection = direction;
	mVCurAni = mSprite->getSpriteAction(direction, mCurAniStat);
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;
	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		/*
		mCurFrame++;
		if (mCurFrame >= mCurAniInfo->MaxFrameCount) {
			mCurFrame = 0;
			mPlayCount++;
		}
		*/

		if (bLoopFlag) {
			if (mCurFrame < mSprite->getMaxFrameCount(mCurAniStat) - 1) {
				mCurFrame++;
			}
			else {
				bLoopFlag = false;
			}
		}
		else {
			if (mCurFrame > 0) {
				mCurFrame--;
			}
			else {
				bLoopFlag = true;
			}
		}
	}
}

void PlayerAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
	mAniInfo[stat].FrameUpdateSec = 1.0 / frameUpdateSec;
}

void PlayerAnimation::render(HDC hdc, float x, float y)
{
	mVCurAni[mCurFrame]->render(hdc, x, y);
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat)]->render(hdc, x, y);
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat) * 2]->render(hdc, x, y);
}

void PlayerAnimation::update()
{
}
