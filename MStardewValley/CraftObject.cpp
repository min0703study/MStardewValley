#include "Stdafx.h"
#include "CraftObject.h"
#include "FurnaceAnimation.h"

void Furance::init(int tileX, int tileY)
{
	CraftObject::init(tileX, tileY, 1, 2, XS_LEFT, YS_CENTER);

	mCurStat = eFuranceState::FS_NONE;

	mAni = new FurnaceAnimation;
	mAni->init();

	mOverBubble = GDIPLUSMANAGER->clone(IMGCLASS->FuranceOverEvent);
	mEffectIndex = EFFECTMANAGER->playEffectLoop(getAbsX(), getAbsY() + TILE_SIZE * 0.8f, EAT_FURANCE_SMELTING);
	EFFECTMANAGER->pauseEffectLoop(mEffectIndex);
}

void Furance::update()
{
	if (mCurStat == eFuranceState::FS_SMELTING) {
		mSmeltingCurSec += TIMEMANAGER->getElapsedTime();
		if (EFFECTMANAGER->isPauseAni(mEffectIndex)) {
			EFFECTMANAGER->resumeEffectLoop(mEffectIndex);
		}
		if (mSmeltingCurSec >= mSmeltingOverSec) {
			EFFECTMANAGER->pauseEffectLoop(mEffectIndex);
			mCurStat = eFuranceState::FS_SMELTING_OVER;
			mAni->playAniLoop(eFuranceState::FS_SMELTING_OVER);
			mOverBubble->overlayImageGp(ITEMMANAGER->findItemReadOnly(mSmeltingItem)->getInventoryImg(), XS_CENTER, YS_TOP);
		}
	}
}

void Furance::render()
{
	mAni->render(getRelX(), getRelY());
	if (mCurStat == FS_SMELTING_OVER) {
		mOverBubble->render(getRelX(), getRelY(), XS_LEFT, YS_BOTTOM);
	}
}

void Furance::release()
{
	EFFECTMANAGER->stopEffectLoop(mEffectIndex);
}

bool Furance::reqStartSmelting()
{
	//용광로 상태 확인
	if (mCurStat != eFuranceState::FS_NONE) return false;

	//플레이어 활성화 아이템, 수량 확인
	const Item* holdItem = PLAYER->getHoldItem();
	const int	itemCount = PLAYER->getHoldItemCount();

	if (itemCount < 5 || holdItem->getItemType() != eItemType::ITP_ORE) return false;

	//석탄 소유 확인
	int index = -1, count = -1;
	if (!PLAYER->getInventory()->findItem(ITEMCLASS->COAL, index, count)) return false;

	switch (((Ore*)holdItem)->getOreType()) {
	case OT_COPPER:
		mCurStat = eFuranceState::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->COPPER_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;

		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);

		EFFECTMANAGER->playEffectSound(EST_FURNACE);
	
		break;
	case OT_IRON:
		mCurStat = eFuranceState::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->IRON_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;
		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);

		EFFECTMANAGER->playEffectSound(EST_FURNACE);
		break;
	case OT_GOLD:
		mCurStat = eFuranceState::FS_SMELTING;
		mAni->playAniLoop(mCurStat);
		mSmeltingItem = ITEMCLASS->GOLD_BAR;
		mSmeltingOverSec = 5.0f;
		mSmeltingCurSec = 0.0f;
		PLAYER->useInventoryItem(index, 1);
		PLAYER->useInventoryItem(PLAYER->getHoldItemIndex(), 5);

		EFFECTMANAGER->playEffectSound(EST_FURNACE);
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
