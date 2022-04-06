#pragma once
#include "SingletonBase.h"

class Item;
class Tool;
class Weapon;

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

	Weapon* addWeapon(string itemId, eWeaponType mWeaponType);
	Tool * addTool(string itemId, eToolType mWeaponType);

	Item* findItem(string itemId, bool isCreate = false);
	Tool* findTool(string itemId, bool isCreate = false);
	Weapon* findWeapon(string itemId, bool isCreate = false);
};

