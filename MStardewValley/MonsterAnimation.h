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

	void changeAniState(eMonsterState changeState);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void playAniOneTime(eMonsterState oneTimeAni);
	void playAniLoop(eMonsterState loopAni);

	bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }
	inline bool isPlaying() { return bIsPlaying; }

	void render(HDC hdc, RectF rcF);

	MonsterAnimation(): mRefDirection() {};
	~MonsterAnimation() {};

private:
	float				mCurFrame;
	float				mCurRealFrame;
	float				mFrameUpdateSec;
	float				mElapsedSec;
	
	eGameDirection*		mRefDirection;	//참조
	vector<ImageGp*>	mVCurAni;		//참조
	AniInfo				mAniInfo[1];
	eMonsterState		mCurState;

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};

