#include "Stdafx.h"
#include "ItemClass.h"

HRESULT ItemClass::init(void)
{
	LOG::d_blue("======================= 아이템 초기 생성 시작 ==============================");
	ITEMMANAGER->addWeapon(WEAPON, eWeaponType::WT_NORMAL);
	ITEMMANAGER->addTool(PICK, eToolType::TT_PICK);
	LOG::d_blue("======================= 아이템 초기 생성 종료 ==============================");
	return S_OK;
}

void ItemClass::release(void)
{
}
