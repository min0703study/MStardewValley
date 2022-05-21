#pragma once
class FurnaceAnimation
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

	void init();
	void release();
	void playAniOneTime(eFuranceState oneTimeAni);
	void playAniLoop(eFuranceState oneTimeAni);
	void frameUpdate(float elapsedTime);
	void render(float centerX, float centerY);

	inline bool isPlaying() { return bIsPlaying; }
	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;

	vector<ImageGp*>	mVCurAni;
	int mCurFrame;

	FurnaceAnimation() {};
	~FurnaceAnimation() {};
};

