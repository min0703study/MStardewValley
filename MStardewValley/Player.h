#pragma once
#include "SingletonBase.h"
#include "GameObject.h"
#include "Item.h"
#include "PlayerAnimation.h"
#include "Inventory.h"

class Player: public GameObject, public SingletonBase<Player>
{
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override {
		action();
	};
	void render(void) override {
		animation();
		draw();
	};
	void release(void) override;

	void draw(void) override;
	void animation(void)override;
	void move(eGameDirection direction);
	void action(void) override;

	void changeActionAni(void);
	void changeGrapAni(void);
	void harvesting(string cropId);

	void eat();
	void hit(int power);

	void setAbsX(float centerX) {
		GameObject::setAbsX(centerX);
		mMoveRectF.X = getAbsX() - mMoveWidth / 2.0f;
	};
	void setAbsY(float centerY) {
		GameObject::setAbsY(centerY);
		mMoveRectF.Y = getAbsRectF().GetBottom() - mMoveHeight;
	};
	void setAbsXY(float centerX, float centerY) {
		GameObject::setAbsXY(centerX, centerY);
		mMoveRectF.X = getAbsX() - mMoveWidth / 2.0f;
		mMoveRectF.Y = getAbsRectF().GetBottom() - mMoveHeight;
	};
	void setAbsXYToTile(int tileX, int tileY) {
		GameObject::setAbsXYToTile(tileX, tileY);
		mMoveRectF.X = getAbsX() - mMoveWidth / 2.0f;
		mMoveRectF.Y = getAbsRectF().GetBottom() - mMoveHeight;
	};
	void offsetX(float x) {
		GameObject::offsetX(x);
		mMoveRectF.Offset(x, 0);
	};
	void offsetY(float y) {
		GameObject::offsetY(y);
		mMoveRectF.Offset(0, y);
	};

	inline bool isActing() {
		return mCurActionState == ePlayerActionState::PS_ATTACK || mCurActionState == ePlayerActionState::PS_GRAP;
	};

	inline TINDEX getAttackTIndex() {
		switch (mCurDirection) {
		case GD_LEFT:
			return TINDEX(getIndexX() - 1, getIndexY());
		case GD_RIGHT:
			return TINDEX(getIndexX() + 1, getIndexY());
		case GD_UP: 
			return TINDEX(getIndexX(), getIndexY() - 1);
		case GD_DOWN:
			return TINDEX(getIndexX(), getIndexY() + 1);
		}
	}

	inline vector<TINDEX> getAroundTIndexList() {
		vector<TINDEX> returnVIndex;

		int indexX = getIndexX();
		int indexY = getIndexY();
		
		returnVIndex.push_back(TINDEX(indexX - 1, indexY));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
		returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));

		return returnVIndex;
	}
	inline vector<TINDEX> getAttackIndexList() {
		vector<TINDEX> returnVIndex;
		int indexX = getIndexX();
		int indexY = getIndexY();
		switch (mCurDirection) {
			case GD_LEFT:
				returnVIndex.push_back(TINDEX(indexX - 1, indexY));
				returnVIndex.push_back(TINDEX(indexX - 1, indexY + 1));
				returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
				break;
			case GD_RIGHT:
				returnVIndex.push_back(TINDEX(indexX + 1, indexY));
				returnVIndex.push_back(TINDEX(indexX + 1, indexY + 1));
				returnVIndex.push_back(TINDEX(indexX + 1, indexY - 1));
				break;
			case GD_UP: 
				returnVIndex.push_back(TINDEX(indexX + 1, indexY - 1));
				returnVIndex.push_back(TINDEX(indexX, indexY - 1));
				returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
				break;
			case GD_DOWN:
				returnVIndex.push_back(TINDEX(indexX + 1, indexY + 1));
				returnVIndex.push_back(TINDEX(indexX, indexY + 1));
				returnVIndex.push_back(TINDEX(indexX - 1, indexY + 1));
				break;
		}
		return returnVIndex;
	}

	inline vector<TINDEX> getItemIndex() {
		vector<TINDEX> returnVIndex;
		int indexX = getIndexX();
		int indexY = getIndexY();
		switch (mCurDirection) {
		case GD_LEFT:
			returnVIndex.push_back(TINDEX(indexX - 1, indexY));
			returnVIndex.push_back(TINDEX(indexX - 1, indexY + 1));
			returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
			break;
		case GD_RIGHT:
			returnVIndex.push_back(TINDEX(indexX + 1, indexY));
			returnVIndex.push_back(TINDEX(indexX + 1, indexY + 1));
			returnVIndex.push_back(TINDEX(indexX + 1, indexY - 1));
			break;
		case GD_UP:
			returnVIndex.push_back(TINDEX(indexX + 1, indexY - 1));
			returnVIndex.push_back(TINDEX(indexX, indexY - 1));
			returnVIndex.push_back(TINDEX(indexX - 1, indexY - 1));
			break;
		case GD_DOWN:
			returnVIndex.push_back(TINDEX(indexX + 1, indexY + 1));
			returnVIndex.push_back(TINDEX(indexX, indexY + 1));
			returnVIndex.push_back(TINDEX(indexX - 1, indexY + 1));
			break;
		}
		return returnVIndex;
	}

	inline int getEndIndexX() { return static_cast<int>(mMoveRectF.GetRight() / TILE_SIZE); };
	inline int getEndIndexY() { return static_cast<int>(mMoveRectF.GetBottom() / TILE_SIZE); };

	inline int getStartIndexX() { return static_cast<int>(mMoveRectF.GetLeft() / TILE_SIZE); };
	inline int getStartIndexY() { return static_cast<int>(mMoveRectF.GetTop()) / TILE_SIZE; };

	inline float getMaxEnergy(void) const { return mMaxEnergy; };
	inline float getEnergy(void) const { return mEnergy; };

	inline float getHP(void) const { return mHp; };
	inline float getMaxHP(void) const { return mMaxHP; };

	inline RectF Player::getTempMoveAbsRectF(eGameDirection changeDirection)
	{
		RectF tempMoveRectF;
		mMoveRectF.GetBounds(&tempMoveRectF);
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
	inline RectF Player::getTempMoveRelRectF(eGameDirection changeDirection)
	{
		RectF tempMoveRectF;
		mMoveRectF.GetBounds(&tempMoveRectF);
		tempMoveRectF.Offset(-CAMERA->getX(), -CAMERA->getY());
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

	void changeActionStat(ePlayerActionState changeStat);
	void changeDirection(eGameDirection changeDirection);
	void changeHoldingItem(int inventoryIndex);

	inline eItemType getHoldItemType() { 
		if (mInventory->isEmpty(mCurHoldItemIndex)) {
			return eItemType::ITP_END;
		}
		else {
			return mInventory->getItemType(mCurHoldItemIndex);
		}
	};
	inline string getHoldItemId() { return mInventory->getItemId(mCurHoldItemIndex); };

	inline const Item*	getHoldItem() { return mCurHoldItem; };
	inline const int	getHoldItemIndex() { return mCurHoldItemIndex; };
	inline const int	getHoldItemCount() { return mInventory->getCount(mCurHoldItemIndex); };
	inline const bool	getHoldItemIsNull() { return mInventory->isEmpty(mCurHoldItemIndex); };

	int addItem(string itemId, int count = 1);
	int buyItem(string itemId, int count = 1);
	int saleItem(int index, int count = 1);

	inline const Inventory* getInventory() { return mInventory; };
	inline ePlayerActionState getStat() const { return mCurActionState; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	inline void setToPortal(const MapPortal portal) { mToPortal = portal; };
	inline const MapPortal getToPortal() const { return mToPortal; };
	inline const int getWeaponPower() const { 
		if (mCurHoldItem != nullptr) {
			if (mCurHoldItem->getItemType() == ITP_WEAPON) {
				return RND->getFromIntTo(((Weapon*)mCurHoldItem)->getMinDamage(), ((Weapon*)mCurHoldItem)->getMaxDamage());
			};
		}
		return -1;
	};
	inline const int getToolPower() const {
		return mPower;
	}
	inline const int getMoeny() const { return mMoney; };

	void useHoldItem();
	void useInventoryItem(int index, int count);
private:
	PlayerAnimation* mAni;

	int mCurHoldItemIndex;
	const Item* mCurHoldItem;

	ePlayerActionState mCurActionState;
	eItemState mHoldItemState;
	eGameDirection mCurDirection;
	Inventory* mInventory;

	MapPortal mToPortal;

	float mHitCount;

	int mMoney;
	int mHp;
	int mEnergy;
	int mPower;

	int mMaxEnergy;
	int mMaxHP;

	float mMoveWidth;
	float mMoveHeight;
	RectF mMoveRectF;
};
