#include "Stdafx.h"
#include "Player.h"
#include "PlayerAnimation.h"

void Player::init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mHitCount = 0;

	mCurDirection = eGameDirection::GD_DOWN;
	mCurActionState = ePlayerActionState::PS_IDLE;

	mAni = new PlayerAnimation;
	mAni->init();
	mAni->setStateFrameSec(PAS_HARVESTING, 6.0f);
	mAni->setStateFrameSec(PAS_ATTACK_2, WEAPON_ANI_FRAME_SEC);
	mAni->setStateFrameSec(PAS_ATTACK_1, TOOL_ANI_FRAME_SEC);
	mAni->playAniLoop(ePlayerAniState::PAS_IDLE);

	mHoldItemState = eItemState::IS_GRAP;

	mMaxEnergy = PLAYER_INIT_ENERGY;
	mEnergy = PLAYER_INIT_ENERGY;

	mMaxHP = PLAYER_INIT_HP;
	mHp = PLAYER_INIT_HP;


	mPower = PLAYER_POWER;
	mMoney = 10000;

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
				mCurHoldItem->renderHold(mHoldItemState, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f * 0.25f * mAni->getCurFrame());
			}
			else if (mAni->getAniStat() == PAS_EAT_FOOD) {
				if (mAni->getCurFrame() < 5) {
					mCurHoldItem->renderHold(mHoldItemState, getRelX(), getRelRectF().GetBottom(), PLAYER_HEIGHT * 0.5f);
				}
			}
			else {
				mCurHoldItem->renderHold(mHoldItemState, getRelX(), getRelRectF().GetBottom(), PLAYER_HEIGHT - mAni->getAniHeight());
			}
		}
		break;
	case GD_UP:
		if (mCurHoldItem != nullptr) {
			if (mAni->getAniStat() == PAS_HARVESTING) {
				mCurHoldItem->renderHold(mHoldItemState, getRelX(), getRelRectF().GetTop(), mAni->getAniHeight() * 0.5f * 0.25f * mAni->getCurFrame());
			}
			else {
				mCurHoldItem->renderHold(mHoldItemState, getRelX(), getRelRectF().GetBottom(), PLAYER_HEIGHT - mAni->getAniHeight());
			}
		}

		mAni->renderBase(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderArm(getMemDc(), getRelX(), getRelRectF().GetBottom());
		mAni->renderLeg(getMemDc(), getRelX(), getRelRectF().GetBottom());
		break;
	}
}

void Player::move(eGameDirection direction)
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

void Player::action(void)
{
	if (mHitCount > 0.0f) {
		mHitCount -= 0.1;
		if (static_cast<int>(mHitCount) % 2 == 0) {
			mAni->setAlphaMode(true);
		}
		else {
			mAni->setAlphaMode(false);
		}

		if (mHitCount <= 0.0f) {
			mAni->setAlphaMode(false);
		}
	}

	if (mAni->isOneTimeAniOver()) {
		mHoldItemState = IS_GRAP;
		changeActionStat(PS_IDLE);
		mAni->playAniLoop(ePlayerAniState::PAS_IDLE);
	}
}

void Player::harvesting(string cropId)
{
	mCurActionState = ePlayerActionState::PS_GRAP;
	mAni->playAniOneTime(PAS_HARVESTING);

	int index = addItem(cropId);
	changeHoldingItem(index);
}

void Player::eat()
{
	if (getHoldItemType() != ITP_FRUIT) return;
	Fruit* fruit = (Fruit*)mCurHoldItem;

	mEnergy += fruit->getEnergy();
	mHp += fruit->getHp();

	if (mEnergy > mMaxEnergy) {
		mEnergy = mMaxEnergy;
	}

	if (mHp > mMaxHP) {
		mHp = mMaxHP;
	}


	mCurActionState = ePlayerActionState::PS_GRAP;
	mAni->playAniOneTime(PAS_EAT_FOOD);

	useHoldItem();
}

void Player::hit(int power)
{
	if (mHitCount <= 0.0f) {
		mHitCount = 7.0f;
		mHp -= power;
	}
}

void Player::changeGrapAni(void)
{

}

void Player::changeActionAni(void)
{
	if (mCurHoldItem == nullptr) return;
	if (mCurActionState != ePlayerActionState::PS_ATTACK) {
		mHoldItemState = eItemState::IS_USE;
		mCurActionState = PS_ATTACK;
		mEnergy -= 0.001f;

		if (mCurHoldItem->getItemType() == ITP_TOOL) {
			if (mCurHoldItem->getItemId() == ITEMCLASS->WATERING_CAN) {
				mAni->playAniOneTime(PAS_WATER_THE_PLANT);
			}
			else {
				mAni->playAniOneTime(PAS_ATTACK_1);
			}
		}
		else if (mCurHoldItem->getItemType() == ITP_WEAPON) {
			mAni->playAniOneTime(PAS_ATTACK_2);
		}
		else {
			mCurActionState = PS_IDLE;
			mHoldItemState = IS_GRAP;
		}

		mCurHoldItem->playUsingAni();
	}
}

void Player::changeActionStat(ePlayerActionState changeStat)
{
	eItemType holdItemType = mInventory->getItemType(mCurHoldItemIndex);
	bool isHolding = !(holdItemType == ITP_TOOL || holdItemType == ITP_WEAPON || holdItemType == ITP_END);

	if (mCurActionState != changeStat) {
		mCurActionState = changeStat;
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
		return mInventory->addItem(ITEMMANAGER->findItemReadOnly(itemId), count);
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
	if (mInventory->getCount(index) <= 0) {
		mCurHoldItem = nullptr;
		mInventory->deleteItem(index);
	};
	return 0;
}

void Player::useHoldItem()
{
	eItemType holdItemType = mInventory->getItemType(mCurHoldItemIndex);

	switch (holdItemType) {
		case eItemType::ITP_SEED: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			if (mInventory->getCount(mCurHoldItemIndex) <= 0) {
				mCurHoldItem = nullptr;
				mInventory->deleteItem(mCurHoldItemIndex);
			};
			break;
		}

		case eItemType::ITP_FRUIT: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			if (mInventory->getCount(mCurHoldItemIndex) <= 0) {
				mCurHoldItem = nullptr;
				mInventory->deleteItem(mCurHoldItemIndex);
			};

			break;
		}

		case eItemType::ITP_CRAFTING: {
			mInventory->addCount(mCurHoldItemIndex, -1);
			if (mInventory->getCount(mCurHoldItemIndex) <= 0) {
				mCurHoldItem = nullptr;
				mInventory->deleteItem(mCurHoldItemIndex);
			};
			break;
		}
	}
}

void Player::useInventoryItem(int index, int count)
{
	mInventory->useItem(index, count);
	if (mInventory->getCount(index) <= 0) {
		mCurHoldItem = nullptr;
		mInventory->deleteItem(index);
	};
}

void Player::release(void)
{
}

