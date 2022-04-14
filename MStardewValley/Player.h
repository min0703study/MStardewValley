#pragma once
#include "GameObject.h"
#include "SingletonBase.h"
#include "PlayerAnimation.h"
#include "Item.h"

typedef struct tagInventoryOneBox {
	bool IsEmpty;
	int Count;
	Item* Item;
} OneBox;

typedef struct tagInventory {
	int Size;
	int CurItemCount;

	OneBox Items[INVENTORY_SIZE];
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
	void moveTo(eGameDirection direction);
	void move(void) override;
	void action(void) override;
	void attack(void);
	void grap(void);
	inline bool isActing() {
		return mCurActionStat == PAS_ATTACK_1 || mCurActionStat == PAS_ATTACK_2 || mCurActionStat == PAS_HARVESTING || mCurActionStat == PAS_WATER_THE_PLANT;
	};
	void changePos(float initX, float initY, eXStandard xStandard, eYStandard yStandard);

	int getAttackIndexX() {
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

	RectF getTempMoveBoxRectF(eGameDirection changeDirection);

	void changeActionStat(ePlayerStat changeStat);
	void changeAniStat(ePlayerAniStat changeStat);
	void changeDirection(eGameDirection changeDirection);

	void changeHoldingItem(int inventoryIndex);
	string getHoldItemId() { return mInventory.Items[mCurHoldItemIndex].Item->getItemId(); };
	inline OneBox getHoldItemBox() { return mInventory.Items[mCurHoldItemIndex]; };

	int addItem(string itemId, int count = 1);

	inline ePlayerAniStat getActionStat() const { return mCurActionStat; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	string getToLoaction() { return mToMapKey; };
	string getCurLoaction() { return mCurMapKey; };

	void setToMapKey(string toLocation) { this->mToMapKey = toLocation; };
	void setToPortalKey(int toLocation) { this->mToPortalKey = toLocation; };
	void setCurMapKey(string toLocation) { this->mCurMapKey = toLocation; };

	void useItem();
private:
	PlayerAnimation* mAni;
	ePlayerAniStat mCurActionStat;
	eGameDirection mCurDirection;

	string mCurMapKey;

	string mToMapKey;
	int mToPortalKey;

	//bool bIsHoldItem;
	int mCurHoldItemIndex;

	tagInventory mInventory;

	int mInventorySizeLevel;
};
