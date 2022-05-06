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
	if (npcId == "�ǿ���") {
		npc->init("�ǿ���", eNpcs::NPC_PIERRE, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	} else if (npcId == "����") {
		npc->init("����", eNpcs::NPC_MARLON, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	}
	else {
		npc->init("Ŭ��Ʈ", eNpcs::NPC_CLINT, 0, 0, PLAYER_HEIGHT, PLAYER_HEIGHT, XS_LEFT, YS_TOP);
	}

	return npc;
}

vector<ImageGp*> NpcManager::getVPortraitImage(eNpcs npcs)
{
	return NPCSPRITE->getPortraits(npcs);
}
