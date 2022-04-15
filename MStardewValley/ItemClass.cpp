#include "Stdafx.h"
#include "ItemClass.h"

HRESULT ItemClass::init(void)
{
	LOG::d_blue("======================= 아이템 초기 생성 시작 ==============================");
	//ITEMMANAGER->addWeapon(WEAPON, eWeaponType::WT_NORMAL, 0);
	//ITEMMANAGER->addTool(PICK, eToolType::TT_PICK, 0);
	//ITEMMANAGER->addTool(HOE, eToolType::TT_HOE, 0);
	//ITEMMANAGER->addTool(AXE, eToolType::TT_AXE, 0);
	//ITEMMANAGER->addTool(WATERING_CAN, eToolType::TT_WATERING_CAN, 0);
	//ITEMMANAGER->addSeed(PARSNIP_SEED, eCropType::CT_PARSNIP, 20);
	//ITEMMANAGER->addFruit(PARSNIP, eCropType::CT_PARSNIP, 35);
	//ITEMMANAGER->addSeed(POTATO_SEED, eCropType::CT_POTATO, 50);
	//ITEMMANAGER->addFruit(POTATO, eCropType::CT_POTATO, 80);
	//ITEMMANAGER->addSeed(BEEN_SEED, eCropType::CT_BEEN, 60);
	//ITEMMANAGER->addFruit(BEEN, eCropType::CT_BEEN, 40);
	//ITEMMANAGER->addSeed(CAULIFLOWER_SEED, eCropType::CT_CAULIFLOWER, 80);
	//ITEMMANAGER->addFruit(CAULIFLOWER, eCropType::CT_CAULIFLOWER, 175);
	LOG::d_blue("======================= 아이템 초기 생성 종료 ==============================");
	return S_OK;
}

void ItemClass::release(void)
{
}
