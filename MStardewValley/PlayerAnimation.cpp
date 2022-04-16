#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init()
{
	mElapsedSec = 0;
	mCurFrame = 0;
	mDirectionInteval = 0;
	mCurStat = ePlayerAniStat::PAS_END;

	bIsPlaying = false;
	bIsOnetime = false;
	bIsOnetimeOver = false;

	mAniHeight = PLAYER_HEIGHT;
	mAniWidth = PLAYER_WIDTH;

	mShadow = PLAYERSPRITE->getShawdow();
	mVBaseAni = PLAYERSPRITE->getVBaseAni();
	mVArmAni = PLAYERSPRITE->getVArmAni();
	mVLegAni = PLAYERSPRITE->getVLegAni();
	mVCurHeight = PLAYERSPRITE->getVAniHeight();
	mHairImgList = PLAYERSPRITE->getHairImg();

	for (int i = 0; i < ePlayerAniStat::PAS_END; i++) {
		mAniInfoList[i].MaxFameCount = PLAYERSPRITE->getSpriteInfoList()[i].FrameCount;
		mAniInfoList[i].FrameUpdateSec = 1.0f / PLAYER_ANI_FRAME_SEC;
	}
}

void PlayerAnimation::playAniOneTime(ePlayerAniStat oneTimeAni)
{
	if (mCurStat != oneTimeAni) {
		mCurStat = oneTimeAni;
		mCurFrame = 0;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver - false;
		mDirectionInteval = PLAYER->getDirection() * mAniInfoList[mCurStat].MaxFameCount;
	}
}

void PlayerAnimation::playAniLoop(ePlayerAniStat loopAni)
{
	if (mCurStat != loopAni) {
		mCurStat = loopAni;
		mCurFrame = 0;
		bIsOnetime = false;
		bIsOnetimeOver = false;
		bIsPlaying = true;
		mDirectionInteval = PLAYER->getDirection() * mAniInfoList[mCurStat].MaxFameCount;
	}
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurStat].FrameUpdateSec) {
		mElapsedSec = 0;
		mCurFrame++;
		mDirectionInteval = PLAYER->getDirection() * mAniInfoList[mCurStat].MaxFameCount;
		if (mCurFrame >= mAniInfoList[mCurStat].MaxFameCount) {
			mCurFrame = 0;
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			}
		}
	}
}

void PlayerAnimation::setStatFrameSec(ePlayerAniStat stat, float frameUpdateSec)
{
	mAniInfoList[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::renderBase(HDC hdc, float centerX, float bottomY)
{
	PLAYERSPRITE->getVBaseAni()[mCurStat][mCurFrame + mDirectionInteval]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
}

void PlayerAnimation::renderArm(HDC hdc, float centerX, float bottomY) {
	PLAYERSPRITE->getVArmAni()[mCurStat][mCurFrame + mDirectionInteval]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
};

void PlayerAnimation::renderLeg(HDC hdc, float centerX, float bottomY) {
	PLAYERSPRITE->getVLegAni()[mCurStat][mCurFrame + mDirectionInteval]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	mShadow->render(hdc, centerX, bottomY, XS_CENTER, YS_CENTER);
};

void PlayerAnimation::release()
{
}