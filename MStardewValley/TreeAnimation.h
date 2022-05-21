#pragma once
class TreeAnimation
{
public:
	typedef struct tagAniInfo {
		float FrameUpdateSec;
		bool IsLoop;

		int StartIndex;
		int MaxFrameCount;

		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;

	void init(eTreeType type);
	void release();

	void playAniOneTime(eTreeAniState oneTimeAni);
	void playAniLoop(eTreeAniState loopAni);

	void frameUpdate(float elapsedTime);
	void render(float leftX, float topY);

	inline bool isPlaying() { return bIsPlaying; }
	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }

	TreeAnimation() {};
	~TreeAnimation() {};

private:
	tagAniInfo mAniInfoList[eTreeAniState::TAS_END];

	float mElapsedSec;
	int mCurFrame;
	int mFrameStatIndex;
	int mPlayCount;

	int					mCurAniState;
	vector<ImageGp*>	mVCurAni;

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};
