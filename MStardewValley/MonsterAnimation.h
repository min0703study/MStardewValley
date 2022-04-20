#pragma once
#include "MonsterSprite.h"

class MonsterAnimation
{
public:
	typedef struct tagAniInfo {
		bool IsLoop;
		float FrameUpdateSec;
		int MaxFrameCount;
		int DirectionInterval;
		int StartIndex;
		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;
	
	void init(eMonsterType type, eGameDirection* direction);
	void release();

	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, RectF rcF);

	MonsterAnimation(): mRefDirection() {};
	~MonsterAnimation() {};

private:
	int					mCurAniStat;
	float				mCurFrame;
	float				mCurRealFrame;
	float				mFrameUpdateSec;
	float				mElapsedSec;
	
	eGameDirection*		mRefDirection;
	vector<ImageGp*>	mVCurAni;
	tagAniInfo			mAniInfo[1];
};

