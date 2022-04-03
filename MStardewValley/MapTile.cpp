#include "Stdafx.h"
#include "MapTile.h"

void MapTile::Init(string id,int index, float x, float y, float width, float height, tagTile* tagTile, ImageGp* imageGp)
{
	GameObject::Init(id, x, y, width, height, XS_LEFT, YS_TOP);

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
	mImageGp->render(getMemDc(), getRelRectF().GetLeft(), getRelRectF().GetTop());
}

void MapTile::release(void)
{
}
