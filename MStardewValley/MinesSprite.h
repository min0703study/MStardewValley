#pragma once
#include "GameNode.h"

class MinesSprite: public GameNode
{
public:
	HRESULT init(void);
private:
	ImageGp* mBaseSprite;
};

