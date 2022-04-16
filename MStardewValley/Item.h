#pragma once
#include "TileObject.h"

class ItemAnimation;

class Item: public TileObject
{
public:
	HRESULT init(string itemId, eItemType type, string itemName, int price);
	void render(void);
	void render(float centerX, float bottomY, float width, float height) const;
	void update(void);

	void setInventoryImg(Bitmap * idleBitmap);

	eItemType getItemType() const { return mItemType; };
	string getItemId() const { return mItemId; }

	ImageGp* getInventoryImg() { return mInventoryImg; }

	void changeStat(eItemStat changeStat) const;
	void changeStat(eGameDirection direction) const;

	int getPrice() { return mPrice; };
protected:
	ItemAnimation* mAni;
private:
	string mItemId;
	string mItemName;
	string mDescription;

	eItemType mItemType;
	eItemStat mCurItemStat;

	ImageGp* mInfoImg;
	ImageGp* mInventoryImg;

	int mPrice;
};

class Weapon : public Item {
public:
	HRESULT init(string itemId, eWeaponType weaponType, string itemName, int minDamage, int maxDamage, int price);
	eWeaponType getWeaponType() { return mWeaponType; }
private:
	eWeaponType mWeaponType;

	int mMInDamage;
	int mMaxDamage;
};

class Tool : public Item {
public:
	HRESULT init(string itemId, eToolType eToolType, string itemName, int price);

	eToolType getToolType() const { return mToolType; };
	eToolLevel getToolLevel() const { return mToolLevel; };
private:
	eToolType mToolType;
	eToolLevel mToolLevel;
};

class Seed: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, string itemName, int price);
	eCropType getCropType() { return mCropType; };
private:
	eCropType mCropType;
};

class Fruit: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, string itemName, int price, int eneregy);
	eCropType getCropType() { return mCropType; };

private:
	eCropType mCropType;
	int mEnergy;
};

