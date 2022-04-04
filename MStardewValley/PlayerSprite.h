#pragma once
#include "GameNode.h"

class PlayerSprite: public GameNode
{
public:
	typedef struct tagSpriteInfoDetail {
		eGameDirection Direction;
		int Stat;

		int* SpriteIndexX;
		int* SpriteIndexY;

		bool IsFlipX;
		bool IsLoop;
	} SpriteDetailInfo;

	typedef struct tagSpriteInfo {
		int MaxFrameCount;

		float* HairPtX;
		float* HairPtY;

		float* ClothPtX;
		float* ClothPtY;

		int* SpriteInterval;
	} SpriteInfo;

	typedef map<int, vector<ImageGp*>> mapAni;
public:
	HRESULT init(void) override;
	void uploadJson();
	void release(void) override;

	int getMaxFrameCount(int stat);

	vector<ImageGp*> getSpriteAction(eGameDirection direction, int stat);

	ImageGp* getHairImg(eGameDirection direction);
	ImageGp* getClothImg(eGameDirection direction);
	ImageGp* getShawdow() { return mShadow; };

	PlayerSprite() {};
	~PlayerSprite() {};
private:
	int mHairIndex;
	int mClothIndex;

	ImageGp* mHairSprite;
	ImageGp* mClothSprite;
	ImageGp* mBaseSprite;

	ImageGp* mShadow;

	map<eGameDirection, ImageGp*> mHairAni;
	map<eGameDirection, ImageGp*> mClothAni;
	map<eGameDirection, mapAni*> mActionAni;

	tagSpriteInfo mSpriteInfo[ePlayerStat::PS_END];
	vector<tagSpriteInfoDetail> mVTagSpriteInfo;
};

