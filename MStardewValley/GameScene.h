#pragma once

#include "GameNode.h"
#include "GameUI.h"

class GameScene: public GameNode
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

private:
	
};

