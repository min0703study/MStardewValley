#pragma once
#include "GameNode.h"
#include "SingletonBase.h"
class ForageSprite: public GameNode, public SingletonBase<ForageSprite>
{
public:
	typedef struct tagSpriteInfo {
		int XIndex;
		int YIndex;
	} SpriteInfo;
public:
	HRESULT init(void) override;
	void release() override;

	Bitmap* getIdleBitmap(eForageType type) { return mIdleBitmapList[type]; };
private:
	ImageGp* mBaseSprite;
	
	vector<ImageGp*> mVForageImg[eForageType::FT_END];
	SpriteInfo mSpriteInfoList[eForageType::FT_END];

	Bitmap* mIdleBitmapList[eForageType::FT_END];

};

