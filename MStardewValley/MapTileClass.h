#pragma once
#include "SingletonBase.h"
class MapTileClass: public SingletonBase<MapTileClass>
{
public:
	const char* MINE_1 = "���� 1��";
	const char* MINE_2 = "���� 2��";

	HRESULT init(void);
	void release(void);
};

