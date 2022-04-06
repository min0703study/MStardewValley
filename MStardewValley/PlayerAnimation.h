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

	void render(HDC hdc, RectF rcF);

	int getPlayCount();

	PlayerAnimation() {};
	~PlayerAnimation() {};

private:
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

	bool bLoopFlag;
};

