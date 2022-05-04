#include "Stdafx.h"
#include "CraftObject.h"

void Furance::init(int tileX, int tileY, eXStandard xStandard, eYStandard yStandard)
{
}

void Furance::update()
{
}

void Furance::render()
{
}

void Furance::release()
{
}

bool Furance::reqStartSmelting()
{
	//용광로 상태 확인
	if (mCurStat != eFuranceStat::FS_NONE) return false;

	//플레이어 활성화 아이템, 수량 확인
	const Item* holdItem = PLAYER->getHoldItem();
	const int	itemCount = PLAYER->getHoldItemCount();
	if (itemCount < 5 || holdItem->getItemType() != eItemType::ITP_ORE) return false;

	//석탄 소유 확인
	int index = -1, count = -1;
	if (!PLAYER->getInventory()->findItem(ITEMCLASS->COAL, index, count)) return false;

	switch (((Ore*)holdItem)->getOreType()) {
	case OT_COPPER:
		mCurStat == eFuranceStat::FS_SMELTING;
		mSmeltingItem = ITEMCLASS->COPPER_BAR;
		break;
	case OT_IRON:
		mCurStat == eFuranceStat::FS_SMELTING;
		mSmeltingItem = ITEMCLASS->IRON_BAR;
		break;
	case OT_GOLD:
		mCurStat == eFuranceStat::FS_SMELTING;
		mSmeltingItem = ITEMCLASS->GOLD_BAR;
		break;
	default:
		return false;
		break;
	};

	return true;
}

string Furance::pickUpItem()
{
	if (mCurStat == FS_SMELTING_OVER) {
		return mSmeltingItem;
	}
}
