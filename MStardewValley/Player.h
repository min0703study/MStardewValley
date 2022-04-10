#pragma once
#include "GameObject.h"
#include "SingletonBase.h"
#include "PlayerAnimation.h"
#include "Item.h"

typedef struct tagInventoryOneBox {
	bool IsEmpty;
	Item* Item;
	int Count;

	tagInventoryOneBox() {
		IsEmpty = true;
		Item = nullptr;
		Count = -1;
	}
} OneBox;

typedef struct tagInventory {
	int Size;
	int CurItemCount;

	OneBox Items[MAX_TOOLBAR_INDEX];

	tagInventory() {
		Size = MAX_TOOLBAR_INDEX;
		//Items = new OneBox[MAX_TOOLBAR_INDEX];
	}
} Inventory;

class Player: public GameObject, public SingletonBase<Player>
{
public:
	void init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	void draw(void) override;
	void animation(void)override;
	void move(void) override;
	void action(void) override;

	void move(eGameDirection direction);
	void changeMoveAni(eGameDirection direction);
	void attack(void);

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


	RectF getTempMoveBoxRectF(eGameDirection changeDirection);

	void changeActionStat(ePlayerStat changeStat);
	void changeDirection(eGameDirection changeDirection);

	void changeHoldingItem(int inventoryIndex);

	int addItem(string itemId, int count = 1);

	inline ePlayerStat getActionStat() const { return mCurActionStat; }
	inline eGameDirection getDirection() const { return mCurDirection; }

	eLocation getToLoaction() { return mToLoaction; };
	eLocation getCurLoaction() { return mCurLoacation; };

	void setToLoaction(eLocation toLocation) { this->mToLoaction = toLocation; };
	void setCurLoaction(eLocation toLocation) { this->mCurLoacation = toLocation; };
private:
	PlayerAnimation* mAni;
	ePlayerStat mCurActionStat;
	eGameDirection mCurDirection;

	eLocation mCurLoacation;
	eLocation mToLoaction;

	bool bIsHoldItem;
	int mCurHoldItemIndex;

	tagInventory mInventory;

	int mInventorySizeLevel;
};
