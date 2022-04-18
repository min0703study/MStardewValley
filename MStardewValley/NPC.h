#pragma once
#include "GameObject.h"

class NPC : public GameObject
{
public:
	HRESULT init(eNpcs npcType);
	void update() override;
	void render() override;
	void release() override;
private:
	eNpcs mNpcType;
	
};

