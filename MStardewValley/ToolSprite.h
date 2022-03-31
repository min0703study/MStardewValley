#pragma once
#include "GameNode.h"

class ToolSprite : public GameNode
{
public:
	HRESULT init(void);
private:
	ImageGp* mToolSprite;
	vector<ImageGp*> getSpriteTool(eGameDirection direction, int toolId, int materialId);
};

