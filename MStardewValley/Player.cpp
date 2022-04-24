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
	mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);

	mPower = PLAYER_POWER;
	mMoney = PLAYER_MOENY;

	mInventory = new Inventory;
	mInventory->init(INVENTORY_SIZE);

	mCurHoldItemIndex = 0;
	mCurHoldItem = mInventory->getItem(0);
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
	mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
	mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
	mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());

	if (!mInventory->isEmpty(mCurHoldItemIndex)) {
		mInventory->getItem(mCurHoldItemIndex)->render(getRelX(), getRelRectF().GetTop());
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
		changeActionStat(PS_IDLE);
		mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);
	}
}

void Player::attack(void)
{
	if (mCurHoldItem == nullptr) return;
	if (mCurStat != ePlayerStat::PS_ATTACK) {
		mCurHoldItem->playUsingAni();
		mCurStat = PS_ATTACK;

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
	}
}

void Player::grap(void)
{
	mCurStat = ePlayerStat::PS_GRAP;
	mAni->playAniOneTime(PAS_HARVESTING);
}

RectF Player::getTempMoveAbsRectF(eGameDirection changeDirection)
{
	RectF tempMoveRectF = RectFMakeCenter(getAbsX(), getAbsY(), mWidth * 0.8f, mHeight * 0.8f);
	switch (changeDirection)
	{
	case GD_LEFT:
		tempMoveRectF.Offset(-PLAYER_MOVE_SPEED, 0.0f);
		break;
	case GD_RIGHT:
		tempMoveRectF.Offset(+PLAYER_MOVE_SPEED, 0.0f);
		break;
	case GD_UP:
		tempMoveRectF.Offset(0.0f, -PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		tempMoveRectF.Offset(0.0f, +PLAYER_MOVE_SPEED);
		break;

	default:
		//DO NOTHING!
		break;
	}

	return tempMoveRectF;
}

RectF Player::getTempMoveRelRectF(eGameDirection changeDirection)
{
	RectF tempMoveRectF = RectFMakeCenter(getRelX(), getRelY(), mWidth * 0.8f, mHeight * 0.8f);
	switch (changeDirection)
	{
	case GD_LEFT:
		tempMoveRectF.Offset(-PLAYER_MOVE_SPEED, 0.0f);
		break;
	case GD_RIGHT:
		tempMoveRectF.Offset(+PLAYER_MOVE_SPEED, 0.0f);
		break;
	case GD_UP:
		tempMoveRectF.Offset(0.0f, -PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		tempMoveRectF.Offset(0.0f, +PLAYER_MOVE_SPEED);
		break;

	default:
		//DO NOTHING!
		break;
	}

	return tempMoveRectF;
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
		mInventory->addItem(ITEMMANAGER->findItemReadOnly(itemId));
	} else {
		mInventory->addCount(index, count);
	}

	return 0;
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

void Player::movePosByPortal(float x, float y)
{
	setAbsXY(x, y);
}

void Player::useItem()
{
	eItemType holdItemType = mInventory->getItemType(mCurHoldItemIndex);
	switch (holdItemType) {
		case eItemType::ITP_SEED: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			break;
		}

		case eItemType::ITP_FRUIT: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			break;
		}
	}

}

void Player::release(void)
{
}

