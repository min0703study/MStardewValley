#include "Stdafx.h"
#include "Player.h"

void Player::init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mAni = new PlayerAnimation;
	mAni->init(PAS_IDLE, eGameDirection::GD_DOWN);
	mAni->setStatFrameSec(PAS_HARVESTING, 6.0f);
	mCurDirection = eGameDirection::GD_DOWN;
	mCurActionStat = PAS_IDLE;

	mCurHoldItemIndex = 0;

	//inventory init
	mInventory.Size = INVENTORY_SIZE;
	mInventory.CurItemCount = 0;
	for (int i = 0; i < mInventory.Size; i++) {
		mInventory.Items[i].Count = 0;
		mInventory.Items[i].IsEmpty = true;
		mInventory.Items[i].Item = nullptr;
	}
}

void Player::changePos(float initAbsX, float initAbsY, eXStandard xStandard, eYStandard yStandard)
{
	setAbsXY(initAbsX, initAbsY);
}

void Player::draw(void)
{
	mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
	if (!this->getHoldItemBox().IsEmpty) {
		if (!isActing()) {
		this->getHoldItemBox().Item->render(getRelX(), getRelRectF().GetBottom(), mAni->getAniWidth(), mAni->getAniHeight());
		}
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
	switch (mCurActionStat)
	{
	case PAS_ATTACK_1: case PAS_ATTACK_2: case PAS_HARVESTING: case PAS_WATER_THE_PLANT:
		if (mAni->getPlayCount() >= 1) {
			changeAniStat(PAS_IDLE);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(eItemStat::IS_GRAP);
		};
		break;
	default:
		break;
	}
}

void Player::attack(void)
{
	if (!this->getHoldItemBox().IsEmpty) {
		switch (mInventory.Items[mCurHoldItemIndex].Item->getItemType()) {
		case ITP_TOOL: {
			string id = mInventory.Items[mCurHoldItemIndex].Item->getItemId();
			if (id == ITEMCLASS->WATERING_CAN) {
				changeAniStat(PAS_WATER_THE_PLANT);
			}
			else {
				changeAniStat(PAS_ATTACK_1);
			}
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
		}
		case ITP_WEAPON:
			changeAniStat(PAS_ATTACK_2);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
		};
	}
}

void Player::grap(void)
{
	changeAniStat(PAS_HARVESTING);
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
	eItemType holdItemType = eItemType::ITP_END;
	if (!getHoldItemBox().IsEmpty) {
		holdItemType = getHoldItemBox().Item->getItemType();
	}

	switch (changeStat) {
	case PS_WALK:
		if (holdItemType != ITP_TOOL && holdItemType != ITP_WEAPON) {
			changeAniStat(PAS_HOLD_WALK);
		}
		else {
			changeAniStat(PAS_WALK);
		}
		break;
	case PS_IDLE:
		if (holdItemType != ITP_TOOL && holdItemType != ITP_WEAPON) {
			changeAniStat(PAS_HOLD_IDLE);
		}
		else {
			changeAniStat(PAS_IDLE);
		}
		break;
	case PS_ATTACK:
		if (holdItemType == eItemType::ITP_TOOL) {
			changeAniStat(PAS_ATTACK_1);
		}
		else if(holdItemType == eItemType::ITP_WEAPON) {
			changeAniStat(PAS_ATTACK_2);
		}
		break;
	case PS_GRAP:
		changeAniStat(PAS_HARVESTING);
		break;
	};
}

void Player::changeAniStat(ePlayerAniStat changeStat)
{
	if (mCurActionStat != changeStat) {
		mCurActionStat = changeStat;
		mAni->changeStatAni(changeStat);
	}
}

void Player::changeDirection(eGameDirection changeDirection)
{
	if (mCurDirection != changeDirection) {
		mCurDirection = changeDirection;
		mAni->changeDirectionAni(changeDirection);
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
		if (mInventory.Items[i].Item->getItemId() == itemId) {
			mInventory.Items[i].Count++;
			return i;
		};
	}

	//없을 시 추가
	if (mInventory.Size >= mInventory.CurItemCount) {
		for (int i = 0; i < mInventory.Size; i++) {
			if (!mInventory.Items[i].IsEmpty) continue;
			mInventory.Items[i].Item = ITEMMANAGER->findItem(itemId);
			mInventory.Items[i].Count = count;
			mInventory.Items[i].IsEmpty = false;
			return i;
		}
	}

	return 0;
}

void Player::useItem()
{
}


void Player::release(void)
{
}

