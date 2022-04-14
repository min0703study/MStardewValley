#include "Stdafx.h"
#include "MapTileClass.h"

HRESULT MapTileClass::init(void)
{
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");
	MAPTILEMANAGER->addMap(MINE_1, 0);
	MAPTILEMANAGER->addMap(MINE_2, 1);
	MAPTILEMANAGER->addMap(FARM, 2);
	MAPTILEMANAGER->addMap(Shop, 3);
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");
	return E_NOTIMPL;
}

void MapTileClass::release(void)
{
}
