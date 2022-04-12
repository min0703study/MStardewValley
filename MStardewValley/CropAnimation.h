#pragma once
class CropAnimation
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

	void init(eCropType type);
	void release();

	void chageStage(int changeStage);

	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);
	void setStatFrameSec(int stat, float frameUpdateSec);

	void render(HDC hdc, float centerX, float bottomY);

	CropAnimation() {};
	~CropAnimation() {};

private:
	int					mCurAniStat;
	int					mCurStage;
	int					mMaxStage;
	float				mCurFrame;
	float				mFrameUpdateSec;
	float				mElapsedSec;

	vector<ImageGp*>	mVAni;
};

