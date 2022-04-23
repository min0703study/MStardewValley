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

	mCurHoldItemIndex = 0;

	mPower = PLAYER_POWER;
	mMoney = PLAYER_MOENY;

	mInventory = new Inventory;
	mInventory->init(INVENTORY_SIZE);

}

void Player::changePos(float initAbsX, float initAbsY, eXStandard xStandard, eYStandard yStandard)
{
	setAbsXY(initAbsX, initAbsY);
}

void Player::draw(void)
{
	mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
	mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
	mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());

	if (!mInventory->isEmpty(mCurHoldItemIndex)) {
		switch (mInventory->getItemType(mCurHoldItemIndex))
		{
		case eItemType::ITP_TOOL: 
			if (isActing()) {
				mInventory->getItem(mCurHoldItemIndex)->render(getRelX(), getRelRectF().GetBottom(), mAni->getAniWidth(), mAni->getAniHeight(), mCurDirection);
			}
			break;
		case eItemType::ITP_WEAPON:
			if (isActing()) {
				mInventory->getItem(mCurHoldItemIndex)->render(getRelX(), getRelRectF().GetBottom(), mAni->getAniWidth(), mAni->getAniHeight(), mCurDirection);
			}
			break;
		case eItemType::ITP_SEED: case eItemType::ITP_FRUIT:
			if (!isActing()) {
				mInventory->getItem(mCurHoldItemIndex)->render(getRelX(), getRelRectF().GetBottom(), mAni->getAniWidth(), mAni->getAniHeight(), mCurDirection);
			}
			break;
		default:
			break;
		}
	}
}

void Player::animation(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::moveTo(eGameDirection direction)
{
	switch (direction)
	{
	case GD_LEFT:
		offsetX(-PLAYER_MOVE_SPEED);
		CAMERA->offsetX(-PLAYER_MOVE_SPEED);
		break;
	case GD_RIGHT:
		offsetX(+PLAYER_MOVE_SPEED);
		CAMERA->offsetX(+PLAYER_MOVE_SPEED);
		break;
	case GD_UP:
		offsetY(-PLAYER_MOVE_SPEED);
		CAMERA->offsetY(-PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		offsetY(+PLAYER_MOVE_SPEED);
		CAMERA->offsetY(+PLAYER_MOVE_SPEED);
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
	mInventory->getItem(mCurHoldItemIndex)->update();
	if (mAni->isOneTimeAniOver()) {
		changeActionStat(PS_IDLE);
		mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);
	}
}

void Player::attack(void)
{
	if (mCurStat != ePlayerStat::PS_ATTACK) {
		switch (mInventory->getItemType(mCurHoldItemIndex)) {
		case ITP_TOOL: {
			mCurStat = PS_ATTACK;
			eToolType toolType = ((Tool*)mInventory->getItem(mCurHoldItemIndex))->getToolType();
			switch (toolType)
			{
				case TT_PICK:
				case TT_AXE:
				case TT_HOE:
					mAni->playAniOneTime(PAS_ATTACK_1);
					break;
				case TT_WATERING_CAN:
					mAni->playAniOneTime(PAS_WATER_THE_PLANT);
					break;
				case TT_END:
				default:
					//!DO NOTHING!
					break;
			}

			mInventory->getItem(mCurHoldItemIndex)->changeStat(mCurDirection);
			break;
		}
		case ITP_WEAPON:
			mCurStat = PS_ATTACK;
			mAni->playAniOneTime(PAS_ATTACK_2);
			mInventory->getItem(mCurHoldItemIndex)->changeStat(mCurDirection);
			break;
		case ITP_SEED: case ITP_FRUIT: {
			break;
		}
		};
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
	if (mInventory->isEmpty(inventoryIndex)) {
		mCurHoldItemIndex = -1;
	} else {
		mCurHoldItemIndex = inventoryIndex;
	}
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

