#include "Stdafx.h"
#include "MapTileClass.h"

HRESULT MapTileClass::init(void)
{
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");
	MAPTILEMANAGER->addMap(MINE_2, "Resources/Map/save_map.map", 0);
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");
	return E_NOTIMPL;
}

void MapTileClass::release(void)
{
}
