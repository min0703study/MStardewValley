#pragma once
#include "TileObject.h"

class ItemAnimation;

class Item: public TileObject
{
public:
	HRESULT init(string itemId, eItemType type, wstring itemName, int price);

	void render(float relX, float relY) const;
	virtual void render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const;
	virtual void renderIdle(float playerCenterX, float playerCenterY) const;

	virtual void update(void) const;

	void setInventoryImg(Bitmap * idleBitmap);
	virtual void playUsingAni() const;

	eItemType getItemType() const { return mItemType; };
	string getItemId() const { return mItemId; }
	wstring getItemName() const { return mItemName; }

	ImageGp* getInventoryImg() const { return mInventoryImg; }

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

	void update() const override;
	void playUsingAni() const override;

	void render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const override;
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

	void playUsingAni() const override;
	void update() const override;

	void render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const override;
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
	float mHoldUpTime;
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


