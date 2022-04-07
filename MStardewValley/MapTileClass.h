#pragma once
#include "SingletonBase.h"
class MapTileClass: public SingletonBase<MapTileClass>
{
public:
	const char* MINE_1 = "±¤»ê 1Ãþ";
	const char* MINE_2 = "±¤»ê 2Ãþ";

	HRESULT init(void);
	void release(void);
};

