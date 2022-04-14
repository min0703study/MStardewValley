#pragma once
#include "GameObject.h"

class ItemAnimation;

class Item : public GameObject
{
public:
	HRESULT init(string itemId, eItemType type, float x, float y, float width, float height, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	void render(void) override;
	void render(float centerX, float bottomY, float width, float height);
	void update(void) override;

	void setInventoryImg(Bitmap * idleBitmap);

	eItemType getItemType() { return mItemType; };
	string getItemId() { return mItemId; }

	ImageGp* getInventoryImg() { return mInventoryImg; }

	void changeStat(eItemStat changeStat);
	void changeStat(eGameDirection direction);
protected:
	ItemAnimation* mAni;
private:
	string mItemId;
	eItemType mItemType;
	eItemStat mCurItemStat;

	ImageGp* mInfoImg;
	ImageGp* mInventoryImg;

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

class Seed: public Item {
public:
	HRESULT init(string itemId, eCropType eCropType, float width, float height);
	eCropType getCropType() { return mCropType; };
private:
	eCropType mCropType;
};

class Fruit: public Item {
public:
	HRESULT init(string itemId, eCropType eCropType, float width, float height);
	eCropType getCropType() { return mCropType; };

private:
	eCropType mCropType;
};

