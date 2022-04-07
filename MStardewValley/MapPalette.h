#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MapPalette : public GameNode, public SingletonBase<MapPalette>
{
public:
	HRESULT init(void);
	void release(void);

	ImageGp * getBaseSprite();

	ImageGp** getPalette();
	Bitmap * getBitmap(int startX, int startY, int xCount, int yCount);
private:
	ImageGp** mMinePalette;
	ImageGp* mines1To30Palette;
};
