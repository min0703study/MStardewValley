#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init(int initStat, eGameDirection initDirection)
{
	mSprite = new PlayerSprite;
	mSprite->init();

	mShadow = mSprite->getShawdow();

	mElapsedSec = 0;
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = initStat;
	mCurAniDirection = initDirection;

	mAniHeight = PLAYER_HEIGHT;
	mAniWidth = PLAYER_WIDTH;

	mVCurAni = mSprite->getVAni(mCurAniDirection, mCurAniStat);

	mVBaseAni = mSprite->getVBaseAni();
	vector<ImageGp*> img = mVBaseAni[PS_HOLD_WALK];
	mVArmAni = mSprite->getVArmAni();
	mVLegAni = mSprite->getVLegAni();
	mVCurHeight = mSprite->getVAniHeight();
}

void PlayerAnimation::changeStatAni(int changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;
	mCurAniStat = changeStat;
	mVCurAni = mSprite->getVAni(mCurAniDirection, changeStat);
}

void PlayerAnimation::changeDirectionAni(eGameDirection direction)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniDirection = direction;
	mVCurAni = mSprite->getVAni(direction, mCurAniStat);
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		mAniHeight = PLAYER_HEIGHT - mVCurHeight[mCurAniStat][mCurFrame];

		mCurFrame++;
		if (mCurFrame >= mSprite->getMaxFrameCount(mCurAniStat)) {
			mCurFrame = 0;
			mPlayCount++;
		}
	}
}

void PlayerAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
	mAniInfo[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::renderBase(HDC hdc, float centerX, float bottomY)
{
	int directionIndex = mCurAniDirection * mSprite->getMaxFrameCount(mCurAniStat);
	mVBaseAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
}

void PlayerAnimation::renderArm(HDC hdc, float centerX, float bottomY) {
	int directionIndex = mCurAniDirection * mSprite->getMaxFrameCount(mCurAniStat);
	mVArmAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);

};

void PlayerAnimation::renderLeg(HDC hdc, float centerX, float bottomY) {
	int directionIndex = mCurAniDirection * mSprite->getMaxFrameCount(mCurAniStat);
	mVLegAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	mShadow->render(hdc, centerX, bottomY, XS_CENTER, YS_CENTER);
};
int PlayerAnimation::getPlayCount() { return mPlayCount; }