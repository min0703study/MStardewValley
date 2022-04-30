#pragma once
#include "GameObject.h"

class NpcAnimation;

class NPC : public GameObject
{
public:
	HRESULT init(string id, eNpcs npcType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update() override;
	void render();
	void release() override;
	void renderPortraitImg(eNpcPortraitsType type, float x, float y);
	inline ImageGp* getPortraitImg(eNpcPortraitsType type) { return mVPortraitImg[type]; };
private:
	eNpcs mNpcType;
	NpcAnimation* mAni;
	vector<ImageGp*> mVPortraitImg;
};