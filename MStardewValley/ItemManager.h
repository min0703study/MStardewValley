#pragma once
#include "SingletonBase.h"

class Item;
class Tool;
class Weapon;
class Seed;
class Fruit;

class ItemManager: public SingletonBase<ItemManager>
{
private:
	typedef map<string, Item*> mapItem;
	typedef map<string, Item*>::iterator mapItemIter;

	mapItem mVItem;
	mapItemIter mViItem;
public:
	HRESULT init(void);
	void release(void);

	Weapon * addWeapon(string itemId, eWeaponType weaponType, wstring itemName, int minDamage, int maxDamage, int price);
	Tool * addTool(string itemId, eToolType toolType, wstring itemName, int price);
	Seed * addSeed(string itemId, eCropType cropType, wstring itemName, int price);
	Fruit * addFruit(string itemId, eCropType cropType, wstring itemName, int price, int eneregy);

	Item* findItem(string itemId, bool isCreate = false);
	const Item* findItemReadOnly(string itemId, bool isCreate = false);
	Tool* findTool(string itemId, bool isCreate = false);
	Weapon* findWeapon(string itemId, bool isCreate = false);
};

