#pragma once
class CraftablesSprite: public SingletonBase<CraftablesSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
	} SpriteInfo;

	HRESULT init(void) override;
	void release() override;

	inline vector<ImageGp*> getVAni(eCraftablesType type) { return mVAni[type]; };
	inline Bitmap* getIdleBitmap(eCraftablesType type) { return mVAni[type][0]->getBitmap(); };
	inline SpriteInfo getSpriteInfo(eCraftablesType type) { return mSpriteInfoList[type]; };
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVAni[eCraftablesType::CBT_END];
	SpriteInfo mSpriteInfoList[eCraftablesType::CBT_END];

};

