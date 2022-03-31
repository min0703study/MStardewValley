#pragma once
#include "GameNode.h"

typedef struct tagSpriteInfoDetail {
	eGameDirection Direction;
	int Stat;

	int* SpriteIndexX;
	int* SpriteIndexY;

	bool IsFlipX;
	bool IsLoop;
};


typedef struct tagSpriteInfo {
	int MaxFrameCount;

	float* HairPtX;
	float* HairPtY;

	float* ClothPtX;
	float* ClothPtY;

	int* SpriteInterval;
};

class PlayerSprite: public GameNode
{
public:
	typedef map<int, vector<ImageGp*>> mapAni;
public:
	HRESULT init(void) override;
	void uploadJson();
	void release(void) override;

	vector<ImageGp*> getSpriteAction(eGameDirection direction, int stat);
	inline tagSpriteInfo getSpriteInfo(int stat);

	int getMaxFrameCount(int stat);

	ImageGp* getHairImg(eGameDirection direction);
	ImageGp* getClothImg(eGameDirection direction);

	PlayerSprite() {};
	~PlayerSprite() {};
private:
	int mHairIndex;
	int mClothIndex;

	ImageGp* mHairSprite;
	ImageGp* mClothSprite;
	ImageGp* mBaseSprite;

	map<eGameDirection, ImageGp*> mHairAni;
	map<eGameDirection, ImageGp*> mClothAni;
	map<eGameDirection, mapAni*> mActionAni;

	tagSpriteInfo mSpriteInfo[ePlayerStat::PS_END];
	vector<tagSpriteInfoDetail> mVTagSpriteInfo;
};

