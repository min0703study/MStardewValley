#include "Stdafx.h"
#include "Player.h"

#include "PlayerAnimation.h"
#include "Item.h"

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
	//inventory init
	mInventory.Size = INVENTORY_SIZE;
	mInventory.CurItemCount = 0;
	for (int i = 0; i < mInventory.Size; i++) {
		mInventory.Items[i].Count = 0;
		mInventory.Items[i].IsEmpty = true;
	}
}

void Player::changePos(float initAbsX, float initAbsY, eXStandard xStandard, eYStandard yStandard)
{
	setAbsXY(initAbsX, initAbsY);
}

void Player::draw(void)
{
	mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());

	if (!isActing() && !mInventory.isEmpty(mCurHoldItemIndex)) {
		mInventory.Items[mCurHoldItemIndex].Item->render(getRelX(), getRelRectF().GetBottom(), mAni->getAniWidth(), mAni->getAniHeight());
	}

	mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
	mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());
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
	if (mAni->isOneTimeAniOver()) {
		changeActionStat(PS_IDLE);
		mAni->playAniLoop(ePlayerAniStat::PAS_IDLE);
	}
}

void Player::attack(void)
{
	if (mCurStat != ePlayerStat::PS_ATTACK) {
		mCurStat = PS_ATTACK;

		switch (mInventory.getItemType(mCurHoldItemIndex)) {
		case ITP_TOOL: {
			eToolType toolType = mInventory.getItemToType<Tool*>(mCurHoldItemIndex)->getToolType();
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

			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
		}
		case ITP_WEAPON:
			mAni->playAniOneTime(PAS_ATTACK_2);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
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
	eItemType holdItemType = mInventory.getItemType(mCurHoldItemIndex);
	bool isHolding = holdItemType == ITP_SEED && holdItemType != ITP_FRUIT;

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
	if (mInventory.Items[inventoryIndex].IsEmpty) {
		mCurHoldItemIndex = -1;
	} else {
		mCurHoldItemIndex = inventoryIndex;
	}
}

int Player::addItem(string itemId, int count)
{
	//이미 존재하는 아이템인지
	for (int i = 0; i < mInventory.Size; i++) {
		if (mInventory.Items[i].IsEmpty) continue;
		if (mInventory.getItemId(i) == itemId) {
			mInventory.Items[i].Count++;
			return i;
		};
	}

	//없을 시 추가
	if (mInventory.Size >= mInventory.CurItemCount) {
		for (int i = 0; i < mInventory.Size; i++) {
			if (!mInventory.Items[i].IsEmpty) continue;
			mInventory.addItem(i, ITEMMANAGER->findItemReadOnly(itemId));
			return i;
		}
	}

	return 0;
}

void Player::useItem()
{
	eItemType holdItemType = mInventory.getItemType(mCurHoldItemIndex);

	switch (holdItemType) {
		case eItemType::ITP_SEED: {
			mInventory.Items[mCurHoldItemIndex].Count -= 1;
			if (mInventory.Items[mCurHoldItemIndex].Count <= 0) {
				mInventory.deleteItem(mCurHoldItemIndex);
			}
			break;
		}

		case eItemType::ITP_FRUIT: {
			break;
		}
	}

}

void Player::release(void)
{
}

