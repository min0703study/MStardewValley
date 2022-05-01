#include "Stdafx.h"
#include "Player.h"
#include "PlayerAnimation.h"

void Player::init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mCurDirection = eGameDirection::GD_DOWN;
	mCurStat = ePlayerStat::PS_IDLE;

	mAni = new PlayerAnimation;
	mAni->init();
	mAni->setStatFrameSec(PAS_HARVESTING, 6.0f);
	mAni->setStatFrameSec(PAS_ATTACK_2, WEAPON_ANI_FRAME_SEC);
	mAni->setStatFrameSec(PAS_ATTACK_1, TOOL_ANI_FRAME_SEC);
	mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);

	mHoldItemStat = eItemStat::IS_GRAP;

	mMaxEnergy = PLAYER_ENERGY;
	mEnergy = PLAYER_ENERGY;
	mPower = PLAYER_POWER;
	mMoney = PLAYER_MOENY;

	mInventory = new Inventory;
	mInventory->init(INVENTORY_SIZE);

	mCurHoldItemIndex = 0;
	mCurHoldItem = mInventory->getItem(0);

	mMoveWidth = mWidth * 0.8f;
	mMoveHeight = mHeight * 0.8f;

	mMoveRectF = RectFMake(getAbsX() - mMoveWidth / 2.0f, getAbsRectF().GetBottom() - mMoveHeight, mMoveWidth, mMoveHeight);
}

void Player::animation(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	if (mCurHoldItem != nullptr) {
		mCurHoldItem->update();
	}
}

void Player::draw(void)
{
	switch (mCurDirection) {
	case GD_DOWN: case GD_LEFT: case GD_RIGHT:
		mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());
		if (mCurHoldItem != nullptr) {
			if (mAni->getAniStat() == PAS_HARVESTING) {
				mCurHoldItem->render(mHoldItemStat, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f * 0.25f * mAni->getCurFrame());
			}
			else {
				mCurHoldItem->render(mHoldItemStat, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f);
			}
		}
		break;
	case GD_UP:
		if (mCurHoldItem != nullptr) {
			if (mAni->getAniStat() == PAS_HARVESTING) {
				mCurHoldItem->render(mHoldItemStat, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f * 0.25f * mAni->getCurFrame());
			}
			else {
				mCurHoldItem->render(mHoldItemStat, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f);
			}
		}

		mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());
		break;
	}

}

void Player::moveTo(eGameDirection direction)
{
	switch (direction)
	{
	case GD_LEFT:
		offsetX(-PLAYER_MOVE_SPEED);
		break;
	case GD_RIGHT:
		offsetX(+PLAYER_MOVE_SPEED);
		break;
	case GD_UP:
		offsetY(-PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		offsetY(+PLAYER_MOVE_SPEED);
		break;
	default:
		//DO NOTHING!
		break;
	}
}

void Player::move(void)
{
}

void Player::action(void)
{
	if (mAni->isOneTimeAniOver()) {
		mHoldItemStat = IS_GRAP;
		changeActionStat(PS_IDLE);
		mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);
	}
}

void Player::attackAni(void)
{
	if (mCurHoldItem == nullptr) return;
	if (mCurStat != ePlayerStat::PS_ATTACK) {
		mHoldItemStat = eItemStat::IS_USE;
		mCurStat = PS_ATTACK;
		mEnergy -= 10.0f;

		if (mCurHoldItem->getItemType() == ITP_TOOL) {
			if (mCurHoldItem->getItemId() == ITEMCLASS->WATERING_CAN) {
				mAni->playAniOneTime(PAS_WATER_THE_PLANT);
			}
			else {
				mAni->playAniOneTime(PAS_ATTACK_1);
			}
		} else if (mCurHoldItem->getItemType() == ITP_WEAPON) {
			mAni->playAniOneTime(PAS_ATTACK_2);
		}
		else {
			mCurStat = PS_IDLE;
			mHoldItemStat = IS_GRAP;
		}

		mCurHoldItem->playUsingAni();
	}
}

void Player::grapAni(void)
{

}

void Player::harvesting(string cropId)
{
	mCurStat = ePlayerStat::PS_GRAP;
	mAni->playAniOneTime(PAS_HARVESTING);

	int index = addItem(cropId);
	changeHoldingItem(index);
}

void Player::hit(int power)
{
	mHp -= power;
}

void Player::changeActionStat(ePlayerStat changeStat)
{
	eItemType holdItemType = mInventory->getItemType(mCurHoldItemIndex);
	bool isHolding = holdItemType == ITP_SEED || holdItemType == ITP_FRUIT;

	if (mCurStat != changeStat) {
		mCurStat = changeStat;
	}

	switch (changeStat) {
	case PS_WALK:
		mAni->playAniLoop(isHolding ? PAS_HOLD_WALK : PAS_WALK);
		break;
	case PS_IDLE:
		mAni->playAniLoop(isHolding ? PAS_HOLD_IDLE : PAS_IDLE);
		break;
	};
}

void Player::changeDirection(eGameDirection changeDirection)
{
	if (mCurDirection != changeDirection) {
		mCurDirection = changeDirection;
	}
}

void Player::changeHoldingItem(int inventoryIndex)
{
	mCurHoldItemIndex = inventoryIndex;
	mCurHoldItem = mInventory->getItem(inventoryIndex);
}

int Player::addItem(string itemId, int count)
{
	int index = mInventory->getIndexToId(itemId);

	if (index == -1) {
		return mInventory->addItem(ITEMMANAGER->findItemReadOnly(itemId));
	} else {
		mInventory->addCount(index, count);
		return index;
	}
}

int Player::buyItem(string itemId, int count)
{
	int index = mInventory->getIndexToId(itemId);
	const Item* item = ITEMMANAGER->findItemReadOnly(itemId);
	mMoney -= item->getPrice() * count;
	if (index == -1) {
		mInventory->addItem(ITEMMANAGER->findItemReadOnly(itemId));
	}
	else {
		mInventory->addCount(index, count);
	}

	return 0;
}

int Player::saleItem(int index, int count)
{
	const Item* item = mInventory->getItem(index);
	mMoney += item->getPrice() * count;
	mInventory->addCount(index, -count);

	return 0;
}

void Player::useItem()
{
	eItemType holdItemType = mInventory->getItemType(mCurHoldItemIndex);
	switch (holdItemType) {
		case eItemType::ITP_SEED: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			if (mInventory->getCount(mCurHoldItemIndex) < 0) {
				mCurHoldItem = nullptr;
				mInventory->deleteItem(mCurHoldItemIndex);
			};
			break;
		}

		case eItemType::ITP_FRUIT: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			if (mInventory->getCount(mCurHoldItemIndex) < 0) {
				mCurHoldItem = nullptr;
				mInventory->deleteItem(mCurHoldItemIndex);
			};
			break;
		}
	}
}

void Player::release(void)
{
}

