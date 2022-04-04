#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class WeaponSprite: public SingletonBase<WeaponSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		eGameDirection Direction;

		int ToolType;
		int ToolLevel;

		int MaxFrameCount;

		int* SpriteIndexX;
		int* SpriteIndexY;

		bool IsFlipX;
	} SpriteInfo;

	HRESULT init(void) override;
	vector<ImageGp*> getVAni(eWeaponType type);
	ImageGp* getImgGp(eWeaponType type);
private:
	ImageGp* mBaseSprite;
	
	int mWeaponIndexX[eWeaponType::WT_END];
	int mWeaponIndexY[eWeaponType::WT_END];

	vector<ImageGp*> mVWeapon[eWeaponType::WT_END];
	ImageGp* mVOriginalImgTool[eWeaponType::WT_END];
};

