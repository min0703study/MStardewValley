#include "Stdafx.h"
#include "JsonClass.h"

HRESULT JsonClass::init(void)
{
	LOG::d_blue("=======================JSON FILE �ʱ� ���� ���� ==============================");
	//MENU
	JSONMANAGER->addJsonValue(MapInfo, "Resources/Map/Info/map_info.json");
	LOG::d_blue("=======================JSON FILE �ʱ� ���� ���� ==============================");
	return S_OK;
}

void JsonClass::release(void)
{
}
