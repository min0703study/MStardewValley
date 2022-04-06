#pragma once
#include "GameObject.h"

class ItemAnimation;

class Item : public GameObject
{
public:
	HRESULT init(string id, string itemId, eItemType type, float x, float y, float width, float height, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	void render(void) override;
	void render(float x, float y, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	void update(void) override;

	eItemType getItemType() { return mItemType; };
	string getItemId() { return mItemId; }

	ImageGp* getInventoryImg() { return mInventoryImg; }
	void changeStat(eItemStat changeStat);
	void changeStat(eGameDirection direction);
protected:
	ImageGp* mInventoryImg;
	ItemAnimation* mAni;
private:
	string mItemId;
	eItemType mItemType;

	ImageGp* mInfoImg;
	eItemStat mCurItemStat;

	int mPrice;
};

class Weapon : public Item {
public:
	HRESULT init(string id, string itemId, eWeaponType weaponType, float x, float y, float width, float height, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	eWeaponType getWeaponType() { return mWeaponType; }
private:
	eWeaponType mWeaponType;
};

class Tool : public Item {
public:
	HRESULT init(string id, string itemId, eToolType eToolType, float x, float y, float width, float height, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);

	eToolType getToolType() { return mToolType; };
	eToolLevel getToolLevel() { return mToolLevel; };
private:
	eToolType mToolType;
	eToolLevel mToolLevel;
};

