#pragma once
#include "GameNode.h"

class PlayerSprite: public GameNode
{
public:
	typedef struct tagSpriteDetailInfo {
		int* BaseIndexXList;
		int* BaseIndexYList;
	} SpriteDetail;

	typedef struct tagSpriteInfo {
		int* BaseIndexXList;
		int* BaseIndexYList;
		int ArmIndexInterval;
		int LegIndexInterval;

		SpriteDetail DetailInfo[eGameDirection::GD_END];

		int FrameCount;
		bool FilpX;
	} SpriteInfo;

public:
	HRESULT init(void) override;
	void uploadJson();
	void release(void) override;

	int getMaxFrameCount(int stat);

	vector<ImageGp*>* getVBaseAni() { return mPlayerBaseImgList; };
	vector<ImageGp*>* getVArmAni() { return mPlayerArmImgList; };
	vector<ImageGp*>* getVLegAni() { return mPlayerLegImgList; };
	vector<float>* getVAniHeight() { return mPlayerAniHeight; };

	vector<ImageGp*> getVHairAni(eGameDirection direction, int stat);

	vector<ImageGp*> mPlayerBaseImgList[ePlayerStat::PS_END];
	vector<ImageGp*> mPlayerArmImgList[ePlayerStat::PS_END];
	vector<ImageGp*> mPlayerLegImgList[ePlayerStat::PS_END];

	vector<float> mPlayerAniHeight[ePlayerStat::PS_END];


	ImageGp* getHairImg(eGameDirection direction);
	ImageGp* getClothImg(eGameDirection direction);
	ImageGp* getShawdow() { return mShadow; };

	inline SpriteInfo* getSpriteInfo() { return mSpriteInfoList; };

	PlayerSprite() {};
	~PlayerSprite() {};
private:
	ImageGp* mBaseHairSprite;
	ImageGp* mBaseClothSprite;
	ImageGp* mBaseBaseSprite;

	SpriteInfo mSpriteInfoList[ePlayerStat::PS_END][eGameDirection::GD_END];

	int mHairIndex;
	int mClothIndex;

	ImageGp* mShadow;

	map<eGameDirection, ImageGp*> mHairAni;
	map<eGameDirection, ImageGp*> mClothAni;

	vector<ImageGp*> mVAni[ePlayerStat::PS_END];
	vector<Bitmap*> mVHair[eGameDirection::GD_END];
	vector<Bitmap*> mVCloth[eGameDirection::GD_END];
};

