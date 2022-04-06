#include "Stdafx.h"
#include "ItemClass.h"

HRESULT ItemClass::init(void)
{
	LOG::d_blue("======================= ������ �ʱ� ���� ���� ==============================");
	ITEMMANAGER->addWeapon(WEAPON, eWeaponType::WT_NORMAL);
	ITEMMANAGER->addTool(PICK, eToolType::TT_PICK);
	LOG::d_blue("======================= ������ �ʱ� ���� ���� ==============================");
	return S_OK;
}

void ItemClass::release(void)
{
}
