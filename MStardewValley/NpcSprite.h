#pragma once

#include "SingletonBase.h"
#include "GameNode.h"

class NpcSprite : public GameNode, public SingletonBase<NpcSprite>
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

	HRESULT init(void);
	void release(void);

	vector<ImageGp*> getVAni(eNpcs npc) { return mVAni[npc]; }
	vector<ImageGp*> getPortraits(eNpcs npc) { return mVPortraits[npc]; };

private:
	ImageGp* mBaseActionImage[eNpcs::NPC_END];
	ImageGp* mBasePortraitImage[eNpcs::NPC_END];

	vector<ImageGp*> mVAni[eNpcs::NPC_END];
	vector<ImageGp*> mVPortraits[eNpcs::NPC_END];
};
