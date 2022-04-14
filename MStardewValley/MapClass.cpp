#include "Stdafx.h"
#include "MapClass.h"

HRESULT MapClass::init(void)
{
	LOG::d_blue("=======================MAP 초기 생성 시작 ==============================");
	MAPTILEMANAGER->addMap(MINE_1, 0);
	MAPTILEMANAGER->addMap(MINE_2, 1);
	MAPTILEMANAGER->addMap(FARM, 2);
	MAPTILEMANAGER->addMap(Shop, 3);
	MAPTILEMANAGER->addMap(HOME, 4);
	LOG::d_blue("=======================MAP 초기 생성 종료 ==============================");
	LOG::d_blue("=======================MAP 팔레트 초기 생성 시작 ==============================");
	MAPPALETTEMANAGER->addMapPalette(MINE_P, "Resources/Map/Palette/mine.map", IMGCLASS->MapMines1To30);
	MAPPALETTEMANAGER->addMapPalette(OUTDOOR_P, "Resources/Map/Palette/spring_outdoor.map", IMGCLASS->MapOutdoorSpring);
	MAPPALETTEMANAGER->addMapPalette(TOWN_INTERIOR_P, "Resources/Map/Palette/town_interior.map", IMGCLASS->MapTownInterior);
	LOG::d_blue("=======================MAP 팔레트 초기 생성 종료 ==============================");
	return E_NOTIMPL;
}

void MapClass::release(void)
{
}
