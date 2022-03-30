#pragma once
#include "PlayerSprite.h"
class PlayerAnimation
{
public:
	typedef struct tagAniInfo {
		float FrameUpdateSec;
		float MaxFrameCount;
		float AllFrameCount;
		float FrameInterval;

		tagAniInfo(float frameUpdateSec, float maxFrameCount, float allFrameCount) {
			FrameUpdateSec = 1.0f / frameUpdateSec;
			MaxFrameCount = maxFrameCount;
			AllFrameCount = allFrameCount;
			FrameInterval = AllFrameCount / MaxFrameCount;
		}
	} AniInfo;

	typedef map<int, AniInfo*> mapAniInfo; //map <stat, 애니메이션 이미지>
private:
	PlayerSprite* mSprite;
	RectF tempRect;

	float mElapsedSec;

	mapAniInfo mAniInfo;

	int					mCurStat;
	eGameDirection		mCurDirection;
	tagAniInfo*			mCurAniInfo;
	vector<ImageGp*>	mVCurAni;
	vector<tagOverlayPosition> mVCurOverlayPosition;
	tagOverlayPosition mCurOvelayPotion;
	ImageGp* mCurHair;
	ImageGp* mCurCloth;

	int mCurFrame;
	int mPlayCount;


	bool bLoopFlag;

	float tempX;
	float tempY;

public:
	void init();

	void changeAni(eGameDirection direction, int changeStat);
	void frameUpdate(float elapsedTime);

	void setAniInfo(int stat, float frameUpdateSec, float maxFrameCount, float allFrameCount);

	void render(HDC hdc, float x, float y);
	void update();

	PlayerAnimation() {};
	~PlayerAnimation() {};
};

