#pragma once
class ItemAnimation
{
public:
	typedef struct tagAniInfo {
		bool IsNone;

		int StartIndex;
		int EndIndex;

		float FrameUpdateSec;
		int MaxFrameCount;
		bool IsLoop;

		tagAniInfo() {
			int StartIndex = 0;
			int EndIndex = 0;
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;

	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }
	inline bool isPlaying() { return bIsPlaying; }

	void initWeapon(eWeaponType type);
	void initTool(eToolType toolType, eToolLevel toolLevel);
	void frameUpdate(float elapsedTime);
	void playAniOneTime();
	void render(HDC hdc, float x, float y, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);

	void release();
	
	ItemAnimation() {};
	~ItemAnimation() {};
private:
	vector<ImageGp*>	mVCurAni;
	AniInfo mAniInfo;

	//ImageGp*			mIdleImg;
	//int				mCurAniStat;

	eGameDirection		mPlayerDirection;

	float				mCurFrame;
	float				mDirectionInterval;
	float				mElapsedSec;

	float				mAniWidth;
	float				mAniHeight;

	bool bIsOnetime;
	bool bIsPlaying;
	bool bIsOnetimeOver;
};

