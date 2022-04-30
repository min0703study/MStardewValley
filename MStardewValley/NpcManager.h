#pragma once

class NpcManager : public SingletonBase<NpcManager>
{
private:
	typedef map<string, NPC*> mapNPC;
	typedef map<string, NPC*>::iterator mapNPCIter;

	mapNPC mVNpc;
	mapNPCIter miVNpc;
public:
	HRESULT init(void);
	void release(void);

	NPC* addNPC(string key, eNpcPortraitsType eNpcType);
	NPC* findNpc(string npcId, bool isCreate = false);

	vector<ImageGp*> getVPortraitImage(eNpcs npcs);
};