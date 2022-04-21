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
private:
	int mSize;
	int mCurItemCount;

	OneBox* mItems;
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
			mItems[index].Item->getInventoryImg()->render(getMemDc(), rcF.GetLeft(), rcF.GetTop());

			if (mItems[index].Item->getItemType() != eItemType::ITP_TOOL && mItems[index].Item->getItemType() != eItemType::ITP_WEAPON) {
				mItems[index].CountImg->render(getMemDc(), rcF.GetRight(), rcF.GetBottom(), XS_RIGHT, YS_BOTTOM);
			}
		}
	}
	string getItemId(int index) {
		return mItems[index].Item->getItemId();
	};
	inline const Item* getItem(int index) {
		return mItems[index].Item;
	};
	eItemType getItemType(int index) {
		if (mItems[index].IsEmpty) {
			return eItemType::ITP_END;
		}
		return mItems[index].Item->getItemType();
	};
	int getItemIndex(string itemId) {
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

	void addItem(const Item* item) {
		for (int i = 0; i < mSize; i++) {
			if (!mItems[i].IsEmpty) continue;
			mItems[i].Item = item;
			mItems[i].IsEmpty = false;
			mItems[i].Count = 1;
			mItems[i].CountImg->clear();
			mCurItemCount += 1;
			GDIPLUSMANAGER->drawTextToBitmap(mItems[i].CountImg->getBitmap(), to_wstring(mItems[i].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
			mItems[i].CountImg->rebuildChachedBitmap();
			break;
		}
	};
	void addCount(int index, int count) {
		mItems[index].Count += count;
		if (mItems[index].Count <= 0) {
			mItems[index].IsEmpty = true;
			mItems[index].Item = nullptr;
		}
		else {
			mItems[index].CountImg->clear();
			GDIPLUSMANAGER->drawTextToBitmap(mItems[index].CountImg->getBitmap(), to_wstring(mItems[index].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
			mItems[index].CountImg->rebuildChachedBitmap();
			mCurItemCount += count;
		}
	};
	void deleteItem(int index) {
		mItems[index].IsEmpty = true;
		mItems[index].Item = nullptr;
		mItems[index].Count = -1;
		mCurItemCount -= 1;
	};
};

class Player: public GameObject, public SingletonBase<Player>
{
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override {
		action();
		//move();
	};
	void render(void) override {
		animation();
		draw();
	};
	void release(void) override;

	void draw(void) override;
	void animation(void)override;
	void move(void) override;
	void moveTo(eGameDirection direction);
	void action(void) override;

	void attack(void);
	void grap(void);

	inline bool isActing() {
		return mCurStat == ePlayerStat::PS_ATTACK || mCurStat == ePlayerStat::PS_GRAP;
	};

	void changePos(float initX, float initY, eXStandard xStandard, eYStandard yStandard);

	inline int getAttackIndexX() {
		switch (mCurDirection) {
		case GD_LEFT:
			return getIndexX() - 1;
		case GD_RIGHT:
			return getIndexX() + 1;
		case GD_UP: case GD_DOWN:
			return getIndexX();
		}
	}
	inline int getAttackIndexY() {
		switch (mCurDirection) {
		case GD_UP:
			return getIndexY() - 1;
		case GD_DOWN:
			return getIndexY() + 1;
		case GD_LEFT: case GD_RIGHT:
			return getIndexY();
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

	inline int getEndIndexX() { return static_cast<int>(getAbsRectF().GetRight() / TILE_SIZE); };
	inline int getEndIndexY() { return static_cast<int>(getAbsRectF().GetBottom() / TILE_SIZE); };

	inline int getStartIndexX() { return static_cast<int>(getAbsRectF().GetLeft() / TILE_SIZE); };
	inline int getStartIndexY() { return static_cast<int>((getAbsRectF().GetTop()) / TILE_SIZE); };

	RectF getTempMoveAbsRectF(eGameDirection changeDirection);
	RectF getTempMoveRelRectF(eGameDirection changeDirection);

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

	template <typename T>
	inline const T getHoldItem() { return (T)mInventory->getItem(mCurHoldItemIndex); };
	inline const bool getHoldItemIsNull() { return mInventory->isEmpty(mCurHoldItemIndex); };

	int addItem(string itemId, int count = 1);

	int buyItem(string itemId, int count);
	int saleItem(int index, int count);


	const Inventory* getInventory() { return mInventory; };

	inline ePlayerStat getStat() const { return mCurStat; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	string getToLoaction() { return mToMapKey; };
	string getCurLoaction() { return mCurMapKey; };

	void setToMapKey(string toLocation) { this->mToMapKey = toLocation; };
	void setToPortalKey(int toLocation) { this->mToPortalKey = toLocation; };
	int getToPortalKey() { return this->mToPortalKey; };
	void setCurMapKey(string toLocation) { this->mCurMapKey = toLocation; };

	inline const int getPower() { return mPower; };
	inline const int getMoeny() { return mMoney; };

	void useItem();
private:
	PlayerAnimation* mAni;

	ePlayerStat mCurStat;
	eGameDirection mCurDirection;

	string mCurMapKey;
	string mToMapKey;

	int mToPortalKey;

	int mCurHoldItemIndex;
	Inventory* mInventory;

	int mInventorySizeLevel;

	int mMoney;
	int mEnergy;
	int mPower;
};
