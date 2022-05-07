#pragma once
#include "SingletonBase.h"

class Item;

class ItemManager: public SingletonBase<ItemManager>
{
private:
	typedef map<string, Item*> mapItem;
	typedef map<string, Item*>::iterator mapItemIter;

	mapItem mVItem;
	mapItemIter mViItem;

	Item* findItem(string itemId);
public:
	HRESULT init(void);
	void release(void);
	const Item* findItemReadOnly(string itemId);
};

