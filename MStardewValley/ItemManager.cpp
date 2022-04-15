#include "Stdafx.h"
#include "ItemManager.h"
#include "Item.h"
#include <codecvt>

HRESULT ItemManager::init(void)
{
	LOG::d_blue("===================아이템 생성 시작 ==========================");
	Json::Value mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->ItemInfo);

	for (auto iter = mapInfoJson["item_info_list"].begin(); iter != mapInfoJson["item_info_list"].end(); iter++) {
		eItemType type = (eItemType)(*iter)["item_type"].asInt();
		string itemId = (*iter)["item_id"].asString();
		string ss = "";
		string itemName = (*iter)["item_name"].asString();

		std::wstring_convert<std::codecvt_utf8<wchar_t>> convertString;
		std::wstring convertId = convertString.from_bytes(itemId);
		std::wstring convertName = convertString.from_bytes(itemName);

		std::string ret;
		std::string buff(MB_CUR_MAX, '\0');

		for (wchar_t const & wc : convertId)
		{
			int mbCharLen = std::wctomb(&buff[0], wc);

			if (mbCharLen < 1) { break; }

			for (int i = 0; i < mbCharLen; ++i)
			{
				ret += buff[i];
			}
		}

		string a  = convertString.to_bytes(convertId);

		cout << convertId.c_str() << endl;

		ss.assign(convertId.begin(), convertId.end());

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

		case ITP_END:
			break;
		default:
			break;
		}
	}
	LOG::d_blue("===================맵 타일 매니저 종료 ==========================");

	return S_OK;
}

void ItemManager::release(void)
{
	//
}

Weapon* ItemManager::addWeapon(string itemId, eWeaponType weaponType, string itemName, int minDamage, int maxDamage, int price)
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

	LOG::d(LOG_ITEM, "[무기]아이템 생성 : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Tool* ItemManager::addTool(string itemId, eToolType toolType, string itemName, int price)
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

	LOG::d(LOG_ITEM, "[툴]아이템 생성 : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Seed * ItemManager::addSeed(string itemId, eCropType cropType, string itemName, int price)
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

	LOG::d(LOG_ITEM, "[씨앗]아이템 생성 : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Fruit * ItemManager::addFruit(string itemId, eCropType cropType, string itemName, int price, int eneregy)
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

	LOG::d(LOG_ITEM, "[과일]아이템 생성 : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));

	return nullptr;
}

Item * ItemManager::findItem(string itemId, bool isCreate)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		return key->second;
	}
	else if (!isCreate) {
		LOG::e(LOG_ITEM, "아이템 검색 실패 : " + itemId);
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
			LOG::d(LOG_IMG_BASE_TAG, "툴 타입 불일치 : " + itemId);
			LOG::d(LOG_IMG_BASE_TAG, "툴 검색 실패 : " + itemId);
		}
	}
	else if (!isCreate) {
		LOG::d(LOG_ITEM, "툴 검색 실패 : " + itemId);
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
			LOG::d(LOG_IMG_BASE_TAG, "툴 타입 불일치 : " + itemId);
			LOG::d(LOG_IMG_BASE_TAG, "툴 검색 실패 : " + itemId);
		}
	}
	else if (!isCreate) {
		LOG::d(LOG_ITEM, "무기 검색 실패 : " + itemId);
	}

	return nullptr;
}