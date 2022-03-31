#pragma once
#include "PlayerSprite.h"
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
	};

	void init(int initStat, eGameDirection initDirection);

	void changeStatAni(int changeStat);
	void changeDirectionAni(eGameDirection direction);

	void frameUpdate(float elapsedTime);

	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, float x, float y);
	void update();

	PlayerAnimation() {};
	~PlayerAnimation() {};

private:
	PlayerSprite* mSprite;

	tagAniInfo mAniInfo[PS_END];

	float mElapsedSec;
	int mCurFrame;
	int mPlayCount;

	int					mCurAniStat;
	eGameDirection		mCurAniDirection;
	vector<ImageGp*>	mVCurAni;

	bool bLoopFlag;
};

