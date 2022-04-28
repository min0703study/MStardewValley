#include "Stdafx.h"
#include "MapClass.h"

HRESULT MapClass::init(void)
{
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");
	MAPTILEMANAGER->addMap(MINE_1, 0);
	MAPTILEMANAGER->addMap(MINE_2, 1);
	MAPTILEMANAGER->addMap(SHOP_WEAPON, 7);
	MAPTILEMANAGER->addMap(FARM, 2);
	MAPTILEMANAGER->addMap(SHOP_SEED, 3);
	MAPTILEMANAGER->addMap(HOME, 4);
	MAPTILEMANAGER->addMap(TOWN, 5);
	MAPTILEMANAGER->addMap(LOAD, 6);
	MAPTILEMANAGER->addMap(SHOP_WEAPON, 7);
	MAPTILEMANAGER->addMap(MINE_3, 8);
	LOG::d_blue("=======================MAP �ʱ� ���� ���� ==============================");

	LOG::d_blue("=======================MAP ��Ż ���� ���� ==============================");
	MAPTILEMANAGER->addPortal(LOAD,0,TINDEX(0, 8), SCENECLASS->FARM, FARM, 1);
	MAPTILEMANAGER->addPortal(LOAD,1,TINDEX(11, 6), SCENECLASS->MINE, MINE_1, 0);
	MAPTILEMANAGER->addPortal(LOAD,2,TINDEX(32, 6), SCENECLASS->SHOP, SHOP_WEAPON, 0);
	MAPTILEMANAGER->addPortal(LOAD,3,TINDEX(7, 10), SCENECLASS->TOWN, TOWN, 0);

	MAPTILEMANAGER->addPortal(SHOP_WEAPON, 0, TINDEX(6,12), SCENECLASS->LOAD, LOAD, 2);

	MAPTILEMANAGER->addPortal(HOME, 0, TINDEX(4, 12), SCENECLASS->FARM, FARM, 0);

	MAPTILEMANAGER->addPortal(FARM, 0, TINDEX(25, 14), SCENECLASS->HOME, HOME, 0);
	MAPTILEMANAGER->addPortal(FARM, 1, TINDEX(3, 0), SCENECLASS->LOAD, LOAD, 0);
	MAPTILEMANAGER->addPortal(FARM, 2, TINDEX(38, 16), SCENECLASS->TOWN, TOWN, 0);

	MAPTILEMANAGER->addPortal(MINE_1, 0, TINDEX(4, 14), SCENECLASS->LOAD, LOAD, 1);

	MAPTILEMANAGER->addPortal(TOWN, 0, TINDEX(0, 5), SCENECLASS->FARM, FARM, 2);
	MAPTILEMANAGER->addPortal(TOWN, 1, TINDEX(11, 0), SCENECLASS->LOAD, LOAD, 3);
	MAPTILEMANAGER->addPortal(TOWN, 2, TINDEX(36, 9), SCENECLASS->SHOP, SHOP_SEED, 0);

	MAPTILEMANAGER->addPortal(SHOP_SEED, 0, TINDEX(6, 15), SCENECLASS->TOWN, TOWN, 2);
	LOG::d_blue("=======================MAP ��Ż ���� ���� ==============================");

	LOG::d_blue("=======================MAP �ȷ�Ʈ �ʱ� ���� ���� ==============================");
	MAPPALETTEMANAGER->addMapPalette(MINE_P, "Resources/Map/Palette/mine.map", IMGCLASS->MapMines1To30);
	MAPPALETTEMANAGER->addMapPalette(OUTDOOR_P, "Resources/Map/Palette/spring_outdoor.map", IMGCLASS->MapOutdoorSpring);
	MAPPALETTEMANAGER->addMapPalette(TOWN_INTERIOR_P, "Resources/Map/Palette/town_interior.map", IMGCLASS->MapTownInterior);
	LOG::d_blue("=======================MAP �ȷ�Ʈ �ʱ� ���� ���� ==============================");
	
	return S_OK;
}

void MapClass::release(void)
{
}
