#pragma once
#include "TileObject.h"

class ItemAnimation;

class Item: public TileObject
{
public:
	HRESULT init(string itemId, eItemType type, wstring itemName, int price);
	void render(void);
	void render(float leftX, float topY) const;

	void render(float playerCenterX, float playerBottomY, float playerWidth, float playerHeight, eGameDirection direction) const;
	void update(void) const;

	void setInventoryImg(Bitmap * idleBitmap);

	eItemType getItemType() const { return mItemType; };
	string getItemId() const { return mItemId; }
	wstring getItemName() const { return mItemName; }

	ImageGp* getInventoryImg() const { return mInventoryImg; }

	void changeStat(eItemStat changeStat) const;
	void changeStat(eGameDirection direction) const;

	int getPrice() const { return mPrice; };
protected:
	ItemAnimation* mAni;
private:
	string mItemId;
	wstring mItemName;
	string mDescription;

	eItemType mItemType;
	eItemStat mCurItemStat;

	ImageGp* mInfoImg;
	ImageGp* mInventoryImg;

	int mPrice;
};

class Weapon : public Item {
public:
	HRESULT init(string itemId, eWeaponType weaponType, wstring itemName, int minDamage, int maxDamage, int price);
	eWeaponType getWeaponType() { return mWeaponType; }
private:
	eWeaponType mWeaponType;

	int mMInDamage;
	int mMaxDamage;
};

class Tool : public Item {
public:
	HRESULT init(string itemId, eToolType eToolType, wstring itemName, int price);

	eToolType getToolType() const { return mToolType; };
	eToolLevel getToolLevel() const { return mToolLevel; };
private:
	eToolType mToolType;
	eToolLevel mToolLevel;
};

class Seed: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, wstring itemName, int price);
	eCropType getCropType() { return mCropType; };
private:
	eCropType mCropType;
};

class Fruit: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, wstring itemName, int price, int eneregy);
	eCropType getCropType() { return mCropType; };

private:
	eCropType mCropType;
	int mEnergy;
};

class Stone : public Item {
public:
	HRESULT init(string itemId, eStoneType stoneType, wstring itemName, int price);
	eStoneType getStoneType() { return mStoneType; };

private:
	eStoneType mStoneType;
};


