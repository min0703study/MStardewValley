#pragma once
class NpcAnimation
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

	void init(eNpcs type);
	void release();

	void frameUpdate(float elapsedTime);
	void render(HDC hdc, float centerX, float bottomY);

	NpcAnimation() {};
	~NpcAnimation() {};

private:
	AniInfo* mAniInfoList[eNpcAniState::NAT_END];
	eNpcAniState		mCurState;

	float				mElapsedSec;
	int					mCurFrame;
	int					mDirectionInteval;

	//!참조! -> 원본 sprite에서 삭제
	vector<ImageGp*>	mVAni;

	bool				bIsPlaying;
	bool				bIsOnetime;
	bool				bIsOnetimeOver;
};

