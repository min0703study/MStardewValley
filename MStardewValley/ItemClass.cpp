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
	ITEMMANAGER->addSeed(PARSNIP_SEED, eCropType::CT_PARSNIP);
	ITEMMANAGER->addFruit(PARSNIP, eCropType::CT_PARSNIP);
	ITEMMANAGER->addSeed(POTATO_SEED, eCropType::CT_POTATO);
	ITEMMANAGER->addFruit(PATATO, eCropType::CT_POTATO);
	ITEMMANAGER->addSeed(BEEN_SEED, eCropType::CT_BEEN);
	ITEMMANAGER->addFruit(BEEN, eCropType::CT_BEEN);
	ITEMMANAGER->addSeed(CAULIFLOWER_SEED, eCropType::CT_CAULIFLOWER);
	ITEMMANAGER->addFruit(CAULIFLOWER, eCropType::CT_CAULIFLOWER);
	LOG::d_blue("======================= 아이템 초기 생성 종료 ==============================");
	return S_OK;
}

void ItemClass::release(void)
{
}
