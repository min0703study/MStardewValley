#pragma once
#include "MinesSprite.h"

class MineRockAnimation
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

	void init(eRockType type);
	void release();
	
	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, RectF rcF);

	void render(HDC hdc, float centerX, float centerY);

	MineRockAnimation() {};
	~MineRockAnimation() {};

private:
	tagAniInfo mAniInfo[PS_END];

	float mElapsedSec;
	int mCurFrame;
	int mPlayCount;

	float mUpdateToolFrameSec;
	int					mCurAniStat;

	vector<ImageGp*>	mVCurAni;
};

