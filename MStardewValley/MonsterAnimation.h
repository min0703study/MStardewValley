#pragma once
#include "MonsterSprite.h"

class MonsterAnimation
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
	
	void init(eMonsterType type);
	void release();

	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, RectF rcF);

	MonsterAnimation() {};
	~MonsterAnimation() {};

private:
	int					mCurAniStat;
	float				mCurFrame;
	float				mFrameUpdateSec;
	float				mElapsedSec;
	
	vector<ImageGp*>	mVCurAni;
};

