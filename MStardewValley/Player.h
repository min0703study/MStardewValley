#pragma once

#include "SingletonBase.h"
#include "GameObject.h"
#include "Item.h"

class PlayerAnimation;

typedef struct tagInventoryOneBox {
	bool IsEmpty;
	int Count;
	const Item* Item;
} OneBox;

typedef struct tagInventory {
	int Size;
	int CurItemCount;

	OneBox Items[INVENTORY_SIZE];

	string getItemId(int index) {
		return Items[index].Item->getItemId();
	};

	inline const Item* getItem(int index) {
		return Items[index].Item;
	};

	template <typename T>
	inline const T getItemToType(int index) {
		return (const T)Items[index].Item;
	};

	eItemType getItemType(int index) {
		return Items[index].Item->getItemType();
	};

	bool isEmpty(int index) {
		return Items[index].IsEmpty;
	};

	void deleteItem(int index) {
		Items[index].IsEmpty = true;
		Items[index].Item = nullptr;
		Items[index].Count = -1;
		CurItemCount -= 1;
	};

	void addItem(int index, const Item* item) {
		Items[index].IsEmpty = false;
		Items[index].Item = item;
		Items[index].Count = 1;
		CurItemCount += 1;
	};
} Inventory;

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

	inline int getIndexX() { return static_cast<int>(getAbsX() / TILE_SIZE); };
	inline int getIndexY() { return static_cast<int>(getAbsY() / TILE_SIZE); };

	RectF getTempMoveAbsRectF(eGameDirection changeDirection);
	RectF getTempMoveRelRectF(eGameDirection changeDirection);

	void changeActionStat(ePlayerStat changeStat);
	void changeDirection(eGameDirection changeDirection);

	void changeHoldingItem(int inventoryIndex);
	//inline OneBox getHoldItemBox() { return mInventory.Items[mCurHoldItemIndex]; };
	inline eItemType getHoldItemType() { 
		if (mInventory.Items[mCurHoldItemIndex].IsEmpty) {
			return eItemType::ITP_END;
		}
		else {
			return mInventory.Items[mCurHoldItemIndex].Item->getItemType();
		}
	};
	inline string getHoldItemId() { return mInventory.getItemId(mCurHoldItemIndex); };

	template <typename T>
	inline const T getHoldItem() { return mInventory.getItemToType<T>(mCurHoldItemIndex); };

	int addItem(string itemId, int count = 1);

	const OneBox* getInventoryBox(int index) { return &mInventory.Items[index]; };

	inline ePlayerStat getStat() const { return mCurStat; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	string getToLoaction() { return mToMapKey; };
	string getCurLoaction() { return mCurMapKey; };

	void setToMapKey(string toLocation) { this->mToMapKey = toLocation; };
	void setToPortalKey(int toLocation) { this->mToPortalKey = toLocation; };
	void setCurMapKey(string toLocation) { this->mCurMapKey = toLocation; };

	inline const int getPower() { return mPower; };

	void useItem();
private:
	PlayerAnimation* mAni;

	ePlayerStat mCurStat;
	eGameDirection mCurDirection;

	string mCurMapKey;
	string mToMapKey;

	int mToPortalKey;

	int mCurHoldItemIndex;
	tagInventory mInventory;

	int mInventorySizeLevel;

	int mMoney;
	int mEnergy;
	int mPower;
};
