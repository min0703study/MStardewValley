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
	void update();

	PlayerAnimation() {};
	~PlayerAnimation() {};

private:
	PlayerSprite* mSprite;
	ToolSprite* mToolSprite;

	tagAniInfo mAniInfo[PS_END];

	ImageGp* mShadow;

	float mElapsedSec;
	float mElapsedToolSec;
	int mCurFrame;
	int mCurToolFrame;
	int mPlayCount;
	float mUpdateToolFrameSec;

	int					mCurAniStat;
	eGameDirection		mCurAniDirection;

	vector<ImageGp*>	mVCurAni;
	vector<ImageGp*>	mVCurToolAni;

	bool bLoopFlag;
};

