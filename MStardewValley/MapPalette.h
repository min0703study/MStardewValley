#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MapPalette : public GameNode, public SingletonBase<MapPalette>
{
public:
	HRESULT init(void);
	void release(void);

	ImageGp** getPalette();
private:
	ImageGp** mMinePalette;
};
