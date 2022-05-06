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
	NPC* npc = new NPC;
	if (npcId == "피에르") {
		npc->init("피에르", eNpcs::NPC_PIERRE, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	} else if (npcId == "말론") {
		npc->init("말론", eNpcs::NPC_MARLON, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	}
	else {
		npc->init("클린트", eNpcs::NPC_CLINT, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	}

	return npc;
}

vector<ImageGp*> NpcManager::getVPortraitImage(eNpcs npcs)
{
	return NPCSPRITE->getPortraits(npcs);
}
