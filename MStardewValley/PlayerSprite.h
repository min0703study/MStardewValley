#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class PlayerSprite: public SingletonBase<PlayerSprite>, public GameNode
{
public:
	typedef struct tagSpriteDetailInfo {
		int* BaseIndexXList;
		int* BaseIndexYList;
	} SpriteDetailInfo;

	typedef struct tagSpriteInfo {
		int ArmIndexInterval;
		int LegIndexInterval;

		SpriteDetailInfo DetailInfo[eGameDirection::GD_END];

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

	vector<ImageGp*> mPlayerBaseImgList[ePlayerAniStat::PAS_END];
	vector<ImageGp*> mPlayerArmImgList[ePlayerAniStat::PAS_END];
	vector<ImageGp*> mPlayerLegImgList[ePlayerAniStat::PAS_END];
	vector<float> mPlayerAniHeight[ePlayerAniStat::PAS_END];

	ImageGp** getHairImg();
	ImageGp* getClothImg(eGameDirection direction);
	ImageGp* getShawdow() { return mShadow; };

	SpriteInfo* getSpriteInfoList() { return mSpriteInfoList; };

	PlayerSprite() {};
	~PlayerSprite() {};
private:
	ImageGp* mBaseHairSprite;
	ImageGp* mBaseClothSprite;
	ImageGp* mBaseSprite;

	int mHairIndex;
	int mClothIndex;

	SpriteInfo mSpriteInfoList[ePlayerAniStat::PAS_END];

	map<eGameDirection, ImageGp*> mHairAni;
	map<eGameDirection, ImageGp*> mClothAni;

	vector<ImageGp*> mVAni[ePlayerAniStat::PAS_END];
	ImageGp* mVHair[eGameDirection::GD_END];
	vector<Bitmap*> mVCloth[eGameDirection::GD_END];
	ImageGp* mShadow;
};

