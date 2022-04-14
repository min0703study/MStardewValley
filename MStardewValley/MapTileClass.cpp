#include "Stdafx.h"
#include "MapTileClass.h"

HRESULT MapTileClass::init(void)
{
	LOG::d_blue("=======================MAP 초기 생성 시작 ==============================");
	MAPTILEMANAGER->addMap(MINE_1, 0);
	MAPTILEMANAGER->addMap(MINE_2, 1);
	MAPTILEMANAGER->addMap(FARM, 2);
	MAPTILEMANAGER->addMap(Shop, 3);
	LOG::d_blue("=======================MAP 초기 생성 종료 ==============================");
	return E_NOTIMPL;
}

void MapTileClass::release(void)
{
}
