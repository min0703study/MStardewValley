#include "Stdafx.h"
#include "MapTile.h"


void MapTile::Init(string id,int index, float x, float y, float width, float height, tagTile* tagTile, ImageGp* imageGp)
{
	int indexX = ((index % 30)) * 50.0f;
	int indexY = (index / 30) * 50.0f;

	GameObject::Init(id, indexX, indexY, width, height);
	
	mTagTile = tagTile;
	mImageGp = imageGp;
}

void MapTile::update(void)
{
}

void MapTile::render(void)
{
	//GameObject::render();
	mImageGp->render(getMemDc(), getX(), getY());
}

void MapTile::release(void)
{
}
