#include "Stdafx.h"
#include "ItemManager.h"
#include "Item.h"

HRESULT ItemManager::init(void)
{
	LOG::d_blue("===================������ ���� ���� ==========================");
	Json::Value mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->ItemInfo);

	for (auto iter = mapInfoJson["item_info_list"].begin(); iter != mapInfoJson["item_info_list"].end(); iter++) {
		eItemType type = (eItemType)(*iter)["item_type"].asInt();

		std::wstring_convert<std::codecvt_utf8<wchar_t>> convertString;

		string itemId = JSONMANAGER->convertUnicodeString((*iter)["item_id"].asString());
		wstring itemName = convertString.from_bytes((*iter)["item_name"].asString());
		int price = (*iter)["price"].asInt();

		switch (type)
		{
		case ITP_TOOL: {
			eToolType toolType = (eToolType)(*iter)["tool_type"].asInt();
			addTool(itemId, toolType, itemName, price);
			break;
		}
		case ITP_WEAPON: {
			eWeaponType weaponType = (eWeaponType)(*iter)["weapon_type"].asInt();
			int minDamage = (*iter)["min_damage"].asInt();
			int maxDamage = (*iter)["max_damage"].asInt();
			addWeapon(itemId, weaponType, itemName, price, minDamage, maxDamage);
			break;
		}
		case ITP_SEED: {
			eCropType cropType = (eCropType)(*iter)["crop_type"].asInt();
			addSeed(itemId, cropType, itemName, price);
			break;
		}
		case ITP_FRUIT: {
			int energy = (*iter)["eneregy"].asInt();
			eCropType cropType = (eCropType)(*iter)["crop_type"].asInt();
			addFruit(itemId, cropType, itemName, price, energy);
			break;
		}
		case ITP_ORE:
		{
			eOreType stoneType = (eOreType)(*iter)["stone_type"].asInt();
			addStone(itemId, stoneType, itemName, price);
			break;
		}
		case ITP_FORAGE:
		{
			eForageType forageType = (eForageType)(*iter)["forage_type"].asInt();
			addForage(itemId, forageType, itemName, price);
			break;
		}
		case ITP_CRAFTING:
		{
			eCraftablesType craftingType = (eCraftablesType)(*iter)["crafting_type"].asInt();
			addCrafting(itemId, craftingType, itemName);
			break;
		}
		case ITP_END:
		default:
			//!DO NOTHING!
			break;
		}
	}
	LOG::d_blue("=================== ������ ���� ���� ==========================");

	return S_OK;
}

void ItemManager::release(void)
{
}

Weapon* ItemManager::addWeapon(string itemId, eWeaponType weaponType, wstring itemName, int price, int minDamage, int maxDamage)
{
	Weapon* item = findWeapon(itemId, true);

	if (item) {
		return item;
	}

	item = new Weapon;
	if (FAILED(item->init(itemId, weaponType, itemName, minDamage, maxDamage, price)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[����]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Tool* ItemManager::addTool(string itemId, eToolType toolType, wstring itemName, int price)
{
	Tool* item = findTool(itemId, true);
	if (item) {
		return item;
	}

	item = new Tool;
	if (FAILED(item->init(itemId, toolType, itemName, price)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[��]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Seed * ItemManager::addSeed(string itemId, eCropType cropType, wstring itemName, int price)
{
	Seed* item = (Seed*)findItem(itemId, true);
	if (item) {
		return (Seed*)item;
	}

	item = new Seed;
	if (FAILED(item->init(itemId, cropType,itemName, price)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[����]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Fruit * ItemManager::addFruit(string itemId, eCropType cropType, wstring itemName, int price, int eneregy)
{
	Fruit* item = (Fruit*)findItem(itemId, true);
	if (item) {
		return (Fruit*)item;
	}

	item = new Fruit;
	if (FAILED(item->init(itemId, cropType, itemName, price, eneregy)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[����]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Ore* ItemManager::addStone(string itemId, eOreType stoneType, wstring itemName, int price)
{
	Ore* item = (Ore*)findItem(itemId, true);
	if (item) {
		return (Ore*)item;
	}

	item = new Ore;
	if (FAILED(item->init(itemId, stoneType, itemName, price)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[�Ἦ]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Forage* ItemManager::addForage(string itemId, eForageType forageType, wstring itemName, int price)
{
	Forage* item = (Forage*)findItem(itemId, true);
	if (item) {
		return (Forage*)item;
	}

	item = new Forage;
	if (FAILED(item->init(itemId, forageType, itemName, price)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[FORAGE]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Craftable* ItemManager::addCrafting(string itemId, eCraftablesType type, wstring itemName)
{
	Craftable* item = (Craftable*)findItem(itemId, true);
	if (item) {
		return (Craftable*)item;
	}

	item = new Craftable;
	if (FAILED(item->init(itemId, type, itemName)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[Crafting]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}


Item* ItemManager::findItem(string itemId, bool isCreate)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		return key->second;
	}
	else if (!isCreate) {
		LOG::e(LOG_ITEM, "������ �˻� ���� : " + itemId);
	}

	return nullptr;
}

const Item* ItemManager::findItemReadOnly(string itemId, bool isCreate)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		return key->second;
	}
	else if (!isCreate) {
		LOG::e(LOG_ITEM, "������ �˻� ���� : " + itemId);
	}

	return nullptr;
}

Tool* ItemManager::findTool(string itemId, bool isCreate)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		if (key->second->getItemType() == ITP_TOOL) {
			return (Tool*)key->second;
		}
		else {
			LOG::d(LOG_IMG_BASE_TAG, "�� Ÿ�� ����ġ : " + itemId);
			LOG::d(LOG_IMG_BASE_TAG, "�� �˻� ���� : " + itemId);
		}
	}
	else if (!isCreate) {
		LOG::d(LOG_ITEM, "�� �˻� ���� : " + itemId);
	}

	return nullptr;
}

Weapon* ItemManager::findWeapon(string itemId, bool isCreate)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		if (key->second->getItemType() == ITP_WEAPON) {
			return (Weapon*)key->second;
		}
		else {
			LOG::d(LOG_IMG_BASE_TAG, "�� Ÿ�� ����ġ : " + itemId);
			LOG::d(LOG_IMG_BASE_TAG, "�� �˻� ���� : " + itemId);
		}
	}
	else if (!isCreate) {
		LOG::d(LOG_ITEM, "���� �˻� ���� : " + itemId);
	}

	return nullptr;
}