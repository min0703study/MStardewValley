#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class WeaponSprite: public SingletonBase<WeaponSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		int StartIndex;
		int EndIndex;

		bool IsNone;
	} SpriteInfo;

	HRESULT init(void) override;

	vector<ImageGp*> getVAni(eWeaponType type);
	inline SpriteInfo* getSpriteInfo() { return mVSpriteInfo; };
	Bitmap* getIdleBitmap(eWeaponType type);
private:
	ImageGp* mBaseSprite;
	
	int mWeaponIndexX[eWeaponType::WT_END];
	int mWeaponIndexY[eWeaponType::WT_END];

	vector<ImageGp*> mVWeapon[eWeaponType::WT_END];

	SpriteInfo mVSpriteInfo[eItemStat::IS_END];
	
	Bitmap* mIdleBitmapList[eWeaponType::WT_END];
};

