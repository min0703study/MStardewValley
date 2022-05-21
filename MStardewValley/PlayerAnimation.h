#pragma once

class PlayerAnimation
{
public:
	typedef struct tagAniInfo {
		int MaxFameCount;
		float FrameUpdateSec;
		bool IsLoop;

		tagAniInfo() {
			FrameUpdateSec = 0.0f;
			MaxFameCount = 0;
			IsLoop = false;
		}
	} AniInfo;

	void release();

	void init();

	void playAniOneTime(ePlayerAniState oneTimeAni);
	void playAniLoop(ePlayerAniState loopAni);

	void frameUpdate(float elapsedTime);

	void setStateFrameSec(ePlayerAniState state, float frameUpdateSec);
	void setAlphaMode(bool flag) { bAlphaMode = flag; };

	void renderBase(HDC hdc, float centerX, float bottomY);
	void renderArm(HDC hdc, float centerX, float bottomY);
	void renderLeg(HDC hdc, float centerX, float bottomY);

	inline float getAniHeight() { return PLAYERSPRITE->getVAniHeight()[mCurState][mCurFrame]; };
	inline float getAniWidth() { return mAniWidth; };
	inline float getAniStat() {return mCurState;}
	inline int getCurFrame() { return mCurFrame; }

	inline bool isOneTimeAniOver() const { return bIsOnetime && bIsOnetimeOver; }
	inline bool isPlaying() { return bIsPlaying; }

	PlayerAnimation() {};
	~PlayerAnimation() {};
private:
	float mAniHeight;
	float mAniWidth;

	AniInfo mAniInfoList[ePlayerAniState::PAS_END];

	float				mElapsedSec;
	int					mCurFrame;
	int					mDirectionInteval;

	bool				bAlphaMode;

	ePlayerAniState		mCurState;

	//!참조! -> 원본 sprite에서 삭제
	vector<ImageGp*>*	mVBaseAni;
	vector<ImageGp*>*	mVArmAni;
	vector<ImageGp*>*	mVLegAni;

	vector<float>*		mVCurHeight;

	ImageGp**			mHairImgList;
	ImageGp*			mShadow;

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};

