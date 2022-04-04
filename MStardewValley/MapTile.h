#pragma once
#include "GameObject.h"

class MapTile: public GameObject
{
public:
	void Init(string id, int index, float x, float y, float width, float height, tagTile * tagTile, ImageGp * imageGp);

	void update(void);
	void render(void);
	void release(void);
	
	tagTile* mTagTile;
	ImageGp* mImageGp;

	bool isCanMove() { return bIsCanMove; }
private:
	bool bIsCanMove;
	int mIndex;
};

