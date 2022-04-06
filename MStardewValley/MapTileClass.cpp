#include "Stdafx.h"
#include "MapTileClass.h"

HRESULT MapTileClass::init(void)
{
	LOG::d_blue("=======================MAP 초기 생성 시작 ==============================");
	MAPTILEMANAGER->addMap(MINE_2, "Resources/Map/save_map.map", 0);
	LOG::d_blue("=======================MAP 초기 생성 종료 ==============================");
	return E_NOTIMPL;
}

void MapTileClass::release(void)
{
}
