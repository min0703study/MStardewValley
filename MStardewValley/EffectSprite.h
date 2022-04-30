#pragma once
#include "SingletonBase.h"
class EffectSprite: public SingletonBase<EffectSprite>
{
public:
	/*
	HRESULT init(void) override;
	void release() override;

	vector<ImageGp*> getVAni(eEffectType effectType) { return mVEffectAni[effectType]; };
	//nline SpriteInfo* getSpriteInfo() { return mSpriteInfoList; };
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVEffectAni[eEffectType::ET_END];
	*/
};

