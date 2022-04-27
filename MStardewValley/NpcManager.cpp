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

NPC * NpcManager::findNpc(string itemId, bool isCreate)
{
	return nullptr;
}

ImageGp * NpcManager::getPortraitImage(eNpcs npcs)
{
	return NPCSPRITE->getPortraits(npcs)[eNpcPortraitsType::NPT_IDLE];
}
