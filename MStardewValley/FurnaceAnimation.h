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

	inline bool isPlaying() { return bIsPlaying; }
	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;

	FurnaceAnimation() {};
	~FurnaceAnimation() {};
};

