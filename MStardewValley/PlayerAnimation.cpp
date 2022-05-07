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
		mAniInfoList[i].MaxFameCount = PLAYERSPRITE->getSpriteInfoList()[i].MaxFrameCount;
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
		bIsOnetimeOver = false;
		mElapsedSec = 0;

		mDirectionInteval = PLAYER->getDirection() * mAniInfoList[oneTimeAni].MaxFameCount;
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

		mElapsedSec = 0;
		mDirectionInteval = PLAYER->getDirection() * mAniInfoList[loopAni].MaxFameCount;
	}
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	if (mAniInfoList[mCurStat].MaxFameCount == 1) return;
	mElapsedSec += elapsedTime;
	
	if (mElapsedSec > mAniInfoList[mCurStat].FrameUpdateSec) {
		mElapsedSec = 0;

		if (mCurFrame == mAniInfoList[mCurStat].MaxFameCount - 1) {
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			} else {
				mCurFrame = 0;
			}
		}
		else {
			mCurFrame++;
		}
	}
}

void PlayerAnimation::setStatFrameSec(ePlayerAniStat stat, float frameUpdateSec)
{
	mAniInfoList[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::renderBase(HDC hdc, float centerX, float bottomY)
{
	mDirectionInteval = PLAYER->getDirection() * mAniInfoList[mCurStat].MaxFameCount;
	PLAYERSPRITE->getVBaseAni()[mCurStat][mCurFrame + mDirectionInteval]->render(centerX, bottomY, XS_CENTER, YS_BOTTOM);
}

void PlayerAnimation::renderArm(HDC hdc, float centerX, float bottomY) {
	PLAYERSPRITE->getVArmAni()[mCurStat][mCurFrame + mDirectionInteval]->render(centerX, bottomY, XS_CENTER, YS_BOTTOM);
};

void PlayerAnimation::renderLeg(HDC hdc, float centerX, float bottomY) {
	PLAYERSPRITE->getVLegAni()[mCurStat][mCurFrame + mDirectionInteval]->render(centerX, bottomY, XS_CENTER, YS_BOTTOM);
	mShadow->render(centerX, bottomY, XS_CENTER, YS_CENTER);
};

void PlayerAnimation::release()
{
}