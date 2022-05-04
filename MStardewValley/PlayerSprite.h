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

		int MaxFrameCount;
		bool FilpX;
	} SpriteInfo;

public:
	HRESULT init(void) override;
	void release(void) override;

	//inline ImageGp** getHairImg() const { return mVHair; };
	inline ImageGp** getHairImg() const { return nullptr; };
	inline ImageGp* getShawdow() const { return mShadow; };

	inline SpriteInfo* getSpriteInfoList() { return mSpriteInfoList; };

	inline vector<ImageGp*>* getVBaseAni() { return mPlayerBaseImgList; };
	inline vector<ImageGp*>* getVArmAni() { return mPlayerArmImgList; };
	inline vector<ImageGp*>* getVLegAni() { return mPlayerLegImgList; };

	inline vector<float>* getVAniHeight() { return mPlayerAniHeight; };

	PlayerSprite() {};
	~PlayerSprite() {};
private:
	ImageGp* mBaseHairSprite;
	ImageGp* mBaseClothSprite;
	ImageGp* mBaseSprite;

	int mHairIndex;
	int mClothIndex;

	SpriteInfo mSpriteInfoList[ePlayerAniStat::PAS_END];

	vector<ImageGp*> mPlayerBaseImgList[ePlayerAniStat::PAS_END];
	vector<ImageGp*> mPlayerArmImgList[ePlayerAniStat::PAS_END];
	vector<ImageGp*> mPlayerLegImgList[ePlayerAniStat::PAS_END];

	vector<float> mPlayerAniHeight[ePlayerAniStat::PAS_END];

	ImageGp* mVHair[eGameDirection::GD_END];
	vector<Bitmap*> mVCloth[eGameDirection::GD_END];
	ImageGp* mShadow;
};

