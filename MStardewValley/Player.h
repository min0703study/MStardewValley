#pragma once
#include "SingletonBase.h"
#include "GameObject.h"
#include "Item.h"
#include "PlayerAnimation.h"

typedef struct tagInventoryOneBox {
	bool IsEmpty;
	int Count;
	const Item* Item;
	ImageGp* CountImg;
} OneBox;

class Inventory: public GameObject {
public:
	HRESULT init(int size) {
		mSize = size;
		mCurItemCount = 0;
		mItems = new OneBox[mSize];
		for (int i = 0; i < mSize; i++) {
			mItems[i].Count = 0;
			mItems[i].IsEmpty = true;
			mItems[i].CountImg = new ImageGp;
			mItems[i].CountImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(INVENTORY_BOX_WIDTH, INVENTORY_BOX_WIDTH * 0.4));
		}

		return S_OK;
	}

	const void render(RectF rcF, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderIdle(rcF.GetLeft(), rcF.GetTop());

			if (mItems[index].Item->getItemType() != eItemType::ITP_TOOL && mItems[index].Item->getItemType() != eItemType::ITP_WEAPON) {
				mItems[index].CountImg->render(rcF.GetRight(), rcF.GetBottom(), XS_RIGHT, YS_BOTTOM);
			}
		}
	}
	const void render(float x, float y, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderIdle(x, y);
		}
	}

	const void renderInfo(float x, float y, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderInfo(x, y);
		}
	}

	const void renderPriceInfo(float x, float y, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderPriceInfo(x, y);
		}
	}
	string getItemId(int index) {
		return mItems[index].Item->getItemId();
	};
	
	inline const Item* getItem(int index) {
		if (mItems[index].IsEmpty) { return nullptr; }
		else { return mItems[index].Item; }
	};
	inline const int getCount(int index) {
		if (mItems[index].IsEmpty) { return -1; }
		else { return mItems[index].Count; }
	};

	eItemType getItemType(int index) {
		if (mItems[index].IsEmpty) {
			return eItemType::ITP_END;
		}
		return mItems[index].Item->getItemType();
	};
	int getIndexToId(string itemId) {
		for (int i = 0; i < mSize; i++) {
			if (mItems[i].IsEmpty) continue;
			if (mItems[i].Item->getItemId() == itemId) {
				return i;
			};
		}

		return -1;
	}
	bool isEmpty(int index) const {
		return mItems[index].IsEmpty;
	};
	int addItem(const Item* item) {
		for (int i = 0; i < mSize; i++) {
			if (!mItems[i].IsEmpty) continue;
			mItems[i].Item = item;
			mItems[i].IsEmpty = false;
			mItems[i].Count = 1;
			mItems[i].CountImg->clear();
			mCurItemCount += 1;
			GDIPLUSMANAGER->drawTextToBitmap(mItems[i].CountImg->getBitmap(), to_wstring(mItems[i].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
			mItems[i].CountImg->rebuildChachedBitmap();
			return i;
		}
		return -1;
	};
	void addCount(int index, int count) {
		mItems[index].Count += count;
		mItems[index].CountImg->clear();
		GDIPLUSMANAGER->drawTextToBitmap(mItems[index].CountImg->getBitmap(), to_wstring(mItems[index].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
		mItems[index].CountImg->rebuildChachedBitmap();
		mCurItemCount += count;
	};

	void swap(int index1, int index2) const {
		OneBox tempBox;
		tempBox = mItems[index1];
		mItems[index1] = mItems[index2];
		mItems[index2] = tempBox;
	};

	void deleteItem(int index) {
		mItems[index].IsEmpty = true;
		mItems[index].Item = nullptr;
		mItems[index].Count = -1;
		mCurItemCount -= 1;
	};

	bool findItem(string itemId, OUT int& index, OUT int& count) const {
		for (int i = 0; i < mSize; i++) {
			if (!mItems[i].IsEmpty) continue;
			if (mItems[i].Item->getItemId() == itemId) {
				index = i;
				count = mItems[i].Count;
				return true;
			}
		}
		return false;
	};
private:
	int mSize;
	int mCurItemCount;

	OneBox* mItems;
};

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
		return mCurStat == ePlayerStat::PS_ATTACK || mCurStat == ePlayerStat::PS_GRAP;
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

	void changeActionStat(ePlayerStat changeStat);
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
	inline const int	getHoldItemCount() { return mInventory->getCount(mCurHoldItemIndex); };
	inline const bool	getHoldItemIsNull() { return mInventory->isEmpty(mCurHoldItemIndex); };

	int addItem(string itemId, int count = 1);
	int buyItem(string itemId, int count = 1);
	int saleItem(int index, int count = 1);

	inline const Inventory* getInventory() { return mInventory; };
	inline ePlayerStat getStat() const { return mCurStat; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	inline void setToPortal(const MapPortal portal) { mToPortal = portal; };
	inline const MapPortal getToPortal() const { return mToPortal; };

	inline const int getWeaponPower() { 
		if (mCurHoldItem != nullptr) {
			if (mCurHoldItem->getItemType() == ITP_WEAPON) {
				return RND->getFromIntTo(((Weapon*)mCurHoldItem)->getMinDamage(), ((Weapon*)mCurHoldItem)->getMaxDamage());
			};
		}
		return -1;
	};
	inline const int getToolPower() {
		return mPower;
	}
	inline const int getMoeny() { return mMoney; };

	void useItem();
private:
	PlayerAnimation* mAni;

	int mCurHoldItemIndex;
	const Item* mCurHoldItem;

	ePlayerStat mCurStat;
	eItemStat mHoldItemStat;

	eGameDirection mCurDirection;
	string mCurMapKey;
	Inventory* mInventory;

	int mInventorySizeLevel;

	MapPortal mToPortal;

	int mMoney;
	int mEnergy;
	int mMaxEnergy;
	int mHp;
	int mPower;

	float mMoveWidth;
	float mMoveHeight;

	RectF mMoveRectF;
};
