#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:
	void Init(string id, int itemId, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	virtual void useItem();
private:
	int mItemId;
	eItemType mType;

	ImageGp* mImgGp;
	string mImgId;
};

