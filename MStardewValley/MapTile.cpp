#include "Stdafx.h"
#include "MapTile.h"


void MapTile::Init(string id,int index, float x, float y, float width, float height, tagTile* tagTile, ImageGp* imageGp)
{
	int indexX = ((index % 30)) * 50.0f;
	int indexY = (index / 30) * 50.0f;

	GameObject::Init(id, indexX + 400, indexY + 100, width, height, XS_LEFT, YS_TOP);
	
	mTagTile = tagTile;
	mImageGp = imageGp;

	if (tagTile->Object != OBJ_NULL || tagTile->SubObject != OBJ_NULL) {
		bIsCanMove = false;
	}
}

void MapTile::update(void)
{
}

void MapTile::render(void)
{
	//GameObject::render();                                   
	mImageGp->render(getMemDc(), getRelX(), getRelY());
}

void MapTile::release(void)
{
}
