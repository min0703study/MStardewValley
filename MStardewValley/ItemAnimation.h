#pragma once
class ItemAnimation
{
public:
	typedef struct tagAniInfo {
		bool IsNone;

		int StartIndex;
		int EndIndex;

		float FrameUpdateSec;
		bool IsLoop;

		tagAniInfo() {
			int StartIndex = 0;
			int EndIndex = 0;
			FrameUpdateSec = 0.0f;
			IsLoop = false;
		}
	} AniInfo;

	void init(string itemId, eItemType type);
	void initWeapon(eWeaponType type);
	void initTool(eToolType toolType, eToolLevel toolLevel);

	void release();

	void changeStatAni(int changeStat);
	void frameUpdate(float elapsedTime);

	void render(HDC hdc, RectF rcF);
	void render(HDC hdc, float x, float y);

	ItemAnimation() {};
	~ItemAnimation() {};

private:
	vector<ImageGp*>	mVCurAni;
	AniInfo mAniInfoList[eItemStat::IS_END];

	ImageGp*			mIdleImg;
	int					mCurAniStat;

	float				mCurFrame;
	float				mElapsedSec;
};

