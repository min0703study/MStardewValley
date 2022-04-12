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

	typedef struct tagSpriteInfoT {
		int StartY;

		int* BaseIndexXList;
		int* BaseIndexYList;
		int ArmIndexInterval;
		int LegIndexInterval;

		int FrameCount;
	} SpriteInfoT;

	typedef map<int, vector<ImageGp*>> mapAni;
public:
	HRESULT init(void) override;
	void uploadJson();
	void release(void) override;

	int getMaxFrameCount(int stat);

	vector<ImageGp*> getVAni(eGameDirection direction, int stat);
	vector<ImageGp*>* getVBaseAni() { return mPlayerBaseImgList; };
	vector<ImageGp*>* getVArmAni() { return mPlayerArmImgList; };
	vector<ImageGp*>* getVLegAni() { return mPlayerLegImgList; };
	vector<float>* getVAniHeight() { return mPlayerAniHeight; };

	vector<ImageGp*> getVHairAni(eGameDirection direction, int stat);

	vector<ImageGp*> mPlayerBaseImgList[ePlayerStat::PS_END];
	vector<ImageGp*> mPlayerArmImgList[ePlayerStat::PS_END];
	vector<ImageGp*> mPlayerLegImgList[ePlayerStat::PS_END];
	vector<float> mPlayerAniHeight[ePlayerStat::PS_END];

	SpriteInfoT mSpriteInfoList[ePlayerStat::PS_END][eGameDirection::GD_END];
	SpriteInfo* getSpriteInfo() { return mSpriteInfo; };

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

	vector<ImageGp*> mVAni[ePlayerStat::PS_END];

	tagSpriteInfo mSpriteInfo[ePlayerStat::PS_END];
	vector<tagSpriteInfoDetail> mVTagSpriteInfo;
};

