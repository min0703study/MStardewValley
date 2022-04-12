#include "Stdafx.h"
#include "ItemClass.h"

HRESULT ItemClass::init(void)
{
	LOG::d_blue("======================= 아이템 초기 생성 시작 ==============================");
	ITEMMANAGER->addWeapon(WEAPON, eWeaponType::WT_NORMAL);
	ITEMMANAGER->addTool(PICK, eToolType::TT_PICK);
	ITEMMANAGER->addTool(HOE, eToolType::TT_HOE);
	ITEMMANAGER->addTool(AXE, eToolType::TT_AXE);
	ITEMMANAGER->addTool(WATERING_CAN, eToolType::TT_WATERING_CAN);
	ITEMMANAGER->addItem(PARSNIP_SEED, eItemType::ITP_SEED);
	ITEMMANAGER->addItem(PARSNIP, eItemType::ITP_CROP);
	LOG::d_blue("======================= 아이템 초기 생성 종료 ==============================");
	return S_OK;
}

void ItemClass::release(void)
{
}
