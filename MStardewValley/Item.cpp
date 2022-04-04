#include "Stdafx.h"
#include "Item.h"

void Item::Init(string id,int itemId, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);
	mItemId = itemId;

	if (itemId == 1) {
		mImgGp = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->Cursor);
	}
}

void Item::useItem()
{

}
