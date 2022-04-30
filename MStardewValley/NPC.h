#pragma once
#include "GameObject.h"

class NpcAnimation;

class NPC : public GameObject
{
public:
	HRESULT init(eNpcs npcType);
	void update() override;
	void render(float x, float y);
	void release() override;
	void renderPortraitImg(eNpcPortraitsType type, float x, float y);
	inline ImageGp* getPortraitImg(eNpcPortraitsType type) { return mVPortraitImg[type]; };
private:
	eNpcs mNpcType;
	NpcAnimation* mAni;
	vector<ImageGp*> mVPortraitImg;
};