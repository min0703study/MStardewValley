#pragma once
#include "PlayerSprite.h"
#include "ToolSprite.h"

class PlayerAnimation
{
public:
	typedef struct tagAniInfo {
		float FrameUpdateSec;
		bool IsLoop;

		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;

	void init(int initStat, eGameDirection initDirection);

	void changeStatAni(int changeStat);
	void changeDirectionAni(eGameDirection direction);

	void frameUpdate(float elapsedTime);

	void setStatFrameSec(int stat, float frameUpdateSec);

	void renderBase(HDC hdc, float centerX, float bottomY);
	void renderArm(HDC hdc, float centerX, float bottomY);
	void renderLeg(HDC hdc, float centerX, float bottomY);

	int getPlayCount();

	float getAniHeight() { return mAniHeight; };
	float getAniWidth() { return mAniWidth; };

	PlayerAnimation() {};
	~PlayerAnimation() {};

private:
	float mAniHeight;
	float mAniWidth;


	PlayerSprite* mSprite;


	tagAniInfo mAniInfo[PS_END];
	ImageGp* mShadow;

	float mElapsedSec;
	int mCurFrame;
	int mPlayCount;
	
	int					mCurAniStat;
	eGameDirection		mCurAniDirection;

	vector<ImageGp*>	mVCurAni;
	vector<ImageGp*>	mVCurToolAni;

	vector<ImageGp*>*	mVBaseAni;
	vector<ImageGp*>*	mVArmAni;
	vector<ImageGp*>*	mVLegAni;
	vector<float>*		mVCurHeight;

	bool bLoopFlag;
};

