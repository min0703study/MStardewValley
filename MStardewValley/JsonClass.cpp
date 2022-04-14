#include "Stdafx.h"
#include "JsonClass.h"

HRESULT JsonClass::init(void)
{
	LOG::d_blue("=======================JSON FILE 초기 생성 시작 ==============================");
	//MENU
	JSONMANAGER->addJsonValue(MapInfo, "Resources/Map/Info/map_info.json");
	LOG::d_blue("=======================JSON FILE 초기 생성 종료 ==============================");
	return S_OK;
}

void JsonClass::release(void)
{
}
