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

		mCurFrame++;
		if (mCurAniStat == PS_HOLD_WALK) {
			mAniHeight = PLAYER_HEIGHT - mVCurHeight[mCurAniStat][mCurFrame];
		}
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
	if (mCurAniStat == PS_HOLD_WALK) {
		if (mCurAniDirection == GD_RIGHT) {
			mVBaseAni[mCurAniStat][mCurFrame + 5]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if (mCurAniDirection == GD_LEFT) {
			mVBaseAni[mCurAniStat][mCurFrame + 10]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if(mCurAniDirection == GD_DOWN) { 
			mVBaseAni[mCurAniStat][mCurFrame + 15]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else {
			mVBaseAni[mCurAniStat][mCurFrame]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
	}
	else {
		mVCurAni[mCurFrame]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	}
}

void PlayerAnimation::renderArm(HDC hdc, float centerX, float bottomY) {
	if (mCurAniStat == PS_HOLD_WALK) {
		if (mCurAniDirection == GD_RIGHT) {
			mVArmAni[mCurAniStat][mCurFrame + 5]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if (mCurAniDirection == GD_LEFT) {
			mVArmAni[mCurAniStat][mCurFrame + 10]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if (mCurAniDirection == GD_DOWN) {
			mVArmAni[mCurAniStat][mCurFrame + 15]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else {
			mVArmAni[mCurAniStat][mCurFrame]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
	}
	else {
		mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat)]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	}

};

void PlayerAnimation::renderLeg(HDC hdc, float centerX, float bottomY) {
	if (mCurAniStat == PS_HOLD_WALK) {
		if (mCurAniDirection == GD_RIGHT) {
			mVLegAni[mCurAniStat][mCurFrame + 5]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if (mCurAniDirection == GD_LEFT) {
			mVLegAni[mCurAniStat][mCurFrame + 10]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else if (mCurAniDirection == GD_DOWN) {
			mVLegAni[mCurAniStat][mCurFrame + 15]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
		else {
			mVLegAni[mCurAniStat][mCurFrame]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
		}
	}
	else {
		mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat) * 2]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	}


	mShadow->render(hdc, centerX, bottomY, XS_CENTER, YS_CENTER);
};
int PlayerAnimation::getPlayCount() { return mPlayCount; }