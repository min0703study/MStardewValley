#pragma once

class MineRockAnimation
{
public:
	typedef struct tagAniInfo {
		float FrameUpdateSec;
		bool IsLoop;

		int StartIndexX;
		int MaxFrameCount;

		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;

	void init(eRockType type);
	void release();

	void playAniOneTime(eRockAniState oneTimeAni);
	void playAniLoop(eRockAniState loopAni);
	
	void frameUpdate(float elapsedTime);
	void render(HDC hdc, float centerX, float centerY);

	inline bool isPlaying() { return bIsPlaying; }
	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }

	MineRockAnimation() {};
	~MineRockAnimation() {};

private:
	tagAniInfo mAniInfoList[PAS_END];

	float mElapsedSec;
	int mCurFrame;
	int mPlayCount;

	float mUpdateToolFrameSec;
	int					mCurState;

	vector<ImageGp*>	mVCurAni;


	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};

