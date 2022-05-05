#include "Stdafx.h"
#include "CraftObject.h"
#include "FurnaceAnimation.h"

void Furance::init(int tileX, int tileY)
{
	CraftObject::init(tileX, tileY, 1, 2, XS_LEFT, YS_CENTER);

	mCurStat = eFuranceStat::FS_NONE;

	mAni = new FurnaceAnimation;
	mAni->init();

	mOverBubble = GDIPLUSMANAGER->clone(IMGCLASS->FuranceOverEvent);
}

void Furance::update()
{
	if (mCurStat == eFuranceStat::FS_SMELTING) {
		mSmeltingCurSec += TIMEMANAGER->getElapsedTime();
		if (mSmeltingCurSec >= mSmeltingOverSec) {
			mCurStat = eFuranceStat::FS_SMELTING_OVER;
			mOverBubble->overlayImageGp(ITEMMANAGER->findItem(mSmeltingItem)->getInventoryImg());
			mAni->playAniLoop(mCurStat);
		}
	}
}

void Furance::render()
{
	mAni->render(getRelX(), getRelY());
	if (mCurStat == FS_SMELTING_OVER) {
		mOverBubble->render(getRelX(), getRelY());
	}

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
		mCurStat = eFuranceStat::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->COPPER_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;
		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);
		EFFECTMANAGER->playEffectAni(getAbsX(), getAbsY(), EAT_FURANCE_SMELTING);
		break;
	case OT_IRON:
		mCurStat = eFuranceStat::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->IRON_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;
		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);
		break;
	case OT_GOLD:
		mCurStat = eFuranceStat::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->GOLD_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;
		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);
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
		mCurStat = FS_NONE;
		return mSmeltingItem;
	}
}

///////////////////////////

void CraftObject::init(int tileX, int tileY,int xCount,int yCount, eXStandard xStandard, eYStandard yStandard)
{
	TileObject::init(tileX, tileY, xCount, yCount, xStandard, yStandard);
	bPlaced = true;
}

void CraftObject::update()
{
}

void CraftObject::render()
{
}

void CraftObject::release()
{
}

void CraftObject::hit()
{
	bPlaced = false;
}
