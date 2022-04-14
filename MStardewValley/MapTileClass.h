#pragma once
#include "SingletonBase.h"
class MapTileClass: public SingletonBase<MapTileClass>
{
public:
	const char* MINE_1 = "mine_1";
	const char* MINE_2 = "mine_2";
	const char*	FARM = "farm";
	const char*	Shop = "shop";

	HRESULT init(void);
	void release(void);
};

