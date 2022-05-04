#pragma once
#include "SingletonBase.h"

class Item;
class Tool;
class Weapon;
class Seed;
class Fruit;
class Ore;
class Forage;
class Craftable;

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

	Weapon * addWeapon(string itemId, eWeaponType weaponType, wstring itemName, int price, int minDamage, int maxDamage);
	Tool * addTool(string itemId, eToolType toolType, wstring itemName, int price);
	Seed * addSeed(string itemId, eCropType cropType, wstring itemName, int price);
	Fruit * addFruit(string itemId, eCropType cropType, wstring itemName, int price, int eneregy);
	Ore * addStone(string itemId, eOreType cropType, wstring itemName, int price);
	Forage * addForage(string itemId, eForageType forageType, wstring itemName, int price);
	Craftable * addCrafting(string itemId, eCraftablesType type, wstring itemName);

	Item* findItem(string itemId, bool isCreate = false);
	const Item* findItemReadOnly(string itemId, bool isCreate = false);
	Tool* findTool(string itemId, bool isCreate = false);
	Weapon* findWeapon(string itemId, bool isCreate = false);
};

