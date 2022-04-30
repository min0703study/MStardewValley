#include "Stdafx.h"
#include "NpcManager.h"

HRESULT NpcManager::init(void)
{
	return S_OK;
}

void NpcManager::release(void)
{
}

NPC * NpcManager::addNPC(string key, eNpcPortraitsType eNpcType)
{
	return nullptr;
}

NPC * NpcManager::findNpc(string npcId, bool isCreate)
{
	/*
	auto key = mVNpc.find(npcId);

	if (key != mVNpc.end())
	{
		return key->second;
	}
	else if (!isCreate) {
		LOG::e(LOG_ITEM, "npc 검색 실패 : " + npcId);
	}
	*/
	NPC* npc = new NPC;
	npc->init("Poerre", eNpcs::NPC_PIERRE, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	return npc;
}

vector<ImageGp*> NpcManager::getVPortraitImage(eNpcs npcs)
{
	return NPCSPRITE->getPortraits(npcs);
}
