#pragma once
#include "TileObject.h"

class ItemAnimation;

class Item: public TileObject
{
public:
	HRESULT init(string itemId, eItemType type, wstring itemName, int price, string description = "", int xCount = 0, int yCount = 0);

	void render(float relX, float relY) const;
	virtual void renderHold(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const;
	virtual void renderIdle(float playerCenterX, float playerCenterY) const;
	virtual void renderInfo(float playerCenterX, float playerCenterY) const;

	void renderPriceInfo(float x, float y) const;

	virtual void update(void) const;

	//제발 수정해라 진짜 이거는
	void setInventoryImg(Bitmap * idleBitmap);

	virtual void playUsingAni() const;
	virtual void setInfoImg();

	eItemType getItemType() const { return mItemType; };
	string getItemId() const { return mItemId; }
	wstring getItemName() const { return mItemName; }

	ImageGp* getInventoryImg() const { return mInventoryImg; }
	ImageGp* getItemInfo() const { return mInfoImg; }

	int getPrice() const { return mPrice; };
protected:
	ItemAnimation* mAni;
private:
	string mItemId;
	wstring mItemName;
	string mDescription;

	eItemType mItemType;
	eItemStat mCurItemStat;

	ImageGp* mInventoryImg;
	ImageGp* mHoldingImg;
	ImageGp* mPriceInfoImg;
	ImageGp* mInfoImg;

	int mPrice;
};
//////////////////////////////////////////
class Weapon : public Item {
public:
	HRESULT init(string itemId, eWeaponType weaponType, wstring itemName, int minDamage, int maxDamage, int price);
	eWeaponType getWeaponType() { return mWeaponType; }

	void update() const override;
	void playUsingAni() const override;

	void renderHold(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const override;

	inline int getMinDamage() const { return mMInDamage; };
	inline int getMaxDamage() const { return mMaxDamage; };
private:
	eWeaponType mWeaponType;

	int mMInDamage;
	int mMaxDamage;
};
//////////////////////////////////////////
class Tool : public Item {
public:
	HRESULT init(string itemId, eToolType eToolType, wstring itemName, int price);

	eToolType getToolType() const { return mToolType; };
	eToolLevel getToolLevel() const { return mToolLevel; };

	void playUsingAni() const override;
	void update() const override;

	void renderHold(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const override;
private:
	eToolType mToolType;
	eToolLevel mToolLevel;
};
//////////////////////////////////////////
class Seed: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, wstring itemName, int price);
	eCropType getCropType() { return mCropType; };
private:
	eCropType mCropType;
};
//////////////////////////////////////////
class Fruit: public Item {
public:
	HRESULT init(string itemId, eCropType cropType, wstring itemName, int price, int eneregy);
	eCropType getCropType() { return mCropType; };
private:
	float mHoldUpTime;
	eCropType mCropType;
	int mEnergy;
};
//////////////////////////////////////////
class Ore : public Item {
public:
	HRESULT init(string itemId, eOreType oreType, wstring itemName, int price);
	eOreType getOreType() { return mOreType; };
private:
	eOreType mOreType;
};
//////////////////////////////////////////
class OreBar : public Item {
public:
	HRESULT init(string itemId, eOreType mOreType, wstring itemName, int price);
	eOreType getOreType() { return mOreType; };
private:
	eOreType mOreType;
};
//////////////////////////////////////////
class Forage : public Item {
public:
	HRESULT init(string itemId, eForageType forageType, wstring itemName, int price);
	eForageType getForageType() { return mForagetype; };

private:
	eForageType mForagetype;
};
//////////////////////////////////////////
class Craftable: public Item {
public:
	typedef struct tagIngredient {
		string ItemId;
		int Amount;

		tagIngredient(string itemId, int amount) : ItemId(itemId), Amount(amount) {};
	} Ingredient;
public:
	HRESULT init(string itemId, eCraftablesType type, wstring itemName);
	void addIngredient(string itemId, int amount);

	eCraftablesType getCraftingType() { return mCraftablesType; };
private:
	vector<tagIngredient> mVIngredient;
	eCraftablesType mCraftablesType;
};
//////////////////////////////////////////