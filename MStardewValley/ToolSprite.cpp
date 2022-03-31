#include "Stdafx.h"
#include "ToolSprite.h"

HRESULT ToolSprite::init(void)
{
	mToolSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->PlayerSpriteCloth);
	return S_OK;
}

vector<ImageGp*> ToolSprite::getSpriteTool(eGameDirection direction, int toolId, int materialId)
{
	return vector<ImageGp*>();
}
