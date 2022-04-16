#pragma once
class TreeAnimation
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

	void init(eTreeType type);
	void release();

	void playAniOneTime(eRockAniStat oneTimeAni);
	void playAniLoop(eRockAniStat loopAni);

	void frameUpdate(float elapsedTime);
	void render(float leftX, float topY);

	inline bool isPlaying() { return bIsPlaying; }
	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }

	TreeAnimation() {};
	~TreeAnimation() {};

private:
	tagAniInfo mAniInfoList[eRockType::RT_END];

	float mElapsedSec;
	int mCurFrame;
	int mPlayCount;

	float mUpdateToolFrameSec;
	int					mCurStat;

	vector<ImageGp*>	mVCurAni;


	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};
