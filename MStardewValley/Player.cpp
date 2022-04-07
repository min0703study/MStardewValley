#include "Stdafx.h"
#include "Player.h"

void Player::init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mAni = new PlayerAnimation;
	mAni->init(PS_IDLE, eGameDirection::GD_DOWN);

	mAni->setStatFrameSec(PS_IDLE, 10);
	mAni->setStatFrameSec(PS_WALK, 10);
	mAni->setStatFrameSec(PS_ATTACK_1, 10);
	mAni->setStatFrameSec(PS_ATTACK_2, 10);

	changeHoldingItem(0);
}

void Player::changePos(float initAbsX, float initAbsY, eXStandard xStandard, eYStandard yStandard)
{
	XYToCenter(initAbsX, initAbsY, mWidth, mHeight, xStandard, yStandard);
	setAbsXY(initAbsX, initAbsY);
}

void Player::update(void)
{
	GameObject::update();
	this->move();
	this->action();
	if (bIsHoldItem) mInventory.Items[mCurHoldItemIndex].Item->update();
}

void Player::render(void)
{
	GameObject::render();

	this->animation();
	this->draw();

	if (bIsHoldItem) mInventory.Items[mCurHoldItemIndex].Item->render(getRelX(), getRelY() - 30.0f);
}

void Player::release(void)
{
}

void Player::draw(void)
{
	mAni->render(getMemDc(), getRelRectF());
}

void Player::animation(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Player::move(void)
{
	bool isMove = false;
	eGameDirection moveDirection;

	if (KEYMANAGER->isStayKeyDown(LEFT_KEY)) {
		isMove = true;
		moveDirection = GD_LEFT;
	}

	if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
		isMove = true;
		moveDirection = GD_RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
		if (!isMove) {
			isMove = true;
			moveDirection = GD_UP;
		}
	}

	if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
		if (!isMove) {
			isMove = true;
			moveDirection = GD_DOWN;
		}
	}

	if (isMove) {
		PLAYER->changeActionStat(PS_WALK);
		PLAYER->changeDirection(moveDirection);
	}
	else {
		if (mCurActionStat != PS_ATTACK_1 && mCurActionStat != PS_ATTACK_2) {
			PLAYER->changeActionStat(PS_IDLE);
		}
	}
}

void Player::move(eGameDirection direction)
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

void Player::changeMoveAni(eGameDirection direction)
{
	switch (direction)
	{
	case GD_LEFT:
		PLAYER->changeDirection(GD_LEFT);
		break;
	case GD_RIGHT:
		PLAYER->changeDirection(GD_RIGHT);
		break;
	case GD_UP:
		PLAYER->changeDirection(GD_UP);
		break;
	case GD_DOWN:
		PLAYER->changeDirection(GD_DOWN);
		break;
	default:
		//DO NOTHING!
		break;
	}
}

void Player::action(void)
{
	switch (mCurActionStat)
	{
	case PS_ATTACK_1: case PS_ATTACK_2:
		if (mAni->getPlayCount() >= 1) {
			changeActionStat(PS_IDLE);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(eItemStat::IS_GRAP);
		};
		break;
	default:
		break;
	}
}

void Player::attack(void)
{
	if (bIsHoldItem) {
		switch (mInventory.Items[mCurHoldItemIndex].Item->getItemType()) {
		case ITP_TOOL:
			changeActionStat(PS_ATTACK_1);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
		case ITP_WEAPON:
			changeActionStat(PS_ATTACK_2);
			mInventory.Items[mCurHoldItemIndex].Item->changeStat(mCurDirection);
			break;
		};
	}
}

RectF Player::getTempMoveBoxRectF(eGameDirection changeDirection)
{
	float x = getAbsRectF().GetLeft();
	float y = getAbsRectF().GetTop() + getHalfHeight();

	switch (changeDirection)
	{
	case GD_LEFT:
		x += -PLAYER_MOVE_SPEED;
		break;
	case GD_RIGHT:
		x += +PLAYER_MOVE_SPEED;
		break;
	case GD_UP:
		y += (-PLAYER_MOVE_SPEED);
		break;
	case GD_DOWN:
		y += (+PLAYER_MOVE_SPEED);
		break;

	default:
		//DO NOTHING!
		break;
	}

	RectF tempMoveRectF = RectFMake(x, y, getWidth(), getHalfHeight());
	return tempMoveRectF;
}

void Player::changeActionStat(ePlayerStat changeStat)
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
	if (IS_NULL(mInventory.Items[inventoryIndex].Item)) {
		mCurHoldItemIndex = -1;
		bIsHoldItem = false;
	} else if (mInventory.Items[inventoryIndex].IsEmpty) {
		mCurHoldItemIndex = -1;
		bIsHoldItem = false;
	} else {
		mCurHoldItemIndex = inventoryIndex;
		bIsHoldItem = true;
	}
}

int Player::addItem(string itemId, int count)
{
	for (int i = 0; i < mInventory.Size; i++) {
		if (mInventory.Items[i].IsEmpty) continue;
		if (mInventory.Items[i].Item->getItemId() == itemId) {
			mInventory.Items[i].Count++;
			return i;
		};
	}

	if (mInventory.Size >= mInventory.CurItemCount) {
		for (int i = 0; i < mInventory.Size; i++) {
			if (!mInventory.Items[i].IsEmpty) continue;
			mInventory.Items[i].Item = ITEMMANAGER->findItem(itemId);
			mInventory.Items[i].Count = count;
			mInventory.Items[i].IsEmpty = false;
			return i;
		}
	}

	return -1;
}

