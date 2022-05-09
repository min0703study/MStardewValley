#include "Stdafx.h"
#include "ItemManager.h"
#include "Item.h"

HRESULT ItemManager::init(void)
{
	LOG::d_blue("===================아이템 생성 시작 ==========================");
	Json::Value mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->ItemInfo);
	Json::Value jsonList = mapInfoJson["item_info_list"];
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convertString;

	for (auto iter = jsonList.begin(); iter != jsonList.end(); ++iter) {

		//common
		string itemId = JSONMANAGER->convertUnicodeString((*iter)["item_id"].asString());
		if (findItem(itemId)) {
			LOG::e(itemId + " : 아이템 아이디 중복");
			continue;
		}
		wstring itemName = convertString.from_bytes((*iter)["item_name"].asString());
		eItemType type = (eItemType)(*iter)["item_type"].asInt();
		wstring description = convertString.from_bytes((*iter)["description"].asString());
		int price = (*iter)["price"].asInt();

		Item* addItem = nullptr;
		HRESULT addItemResult = E_FAIL;
		
		switch (type)
		{
		case ITP_TOOL: {
			eToolType toolType = (eToolType)(*iter)["tool_type"].asInt();
			eToolLevel toolLevel = (eToolLevel)(*iter)["tool_level"].asInt();
			addItem = new Tool;
			addItemResult = static_cast<Tool*>(addItem)->init(itemId, toolType, toolLevel, itemName, price, description);
			break;
		}
		case ITP_WEAPON: {
			eWeaponType weaponType = (eWeaponType)(*iter)["weapon_type"].asInt();
			int minDamage = (*iter)["min_damage"].asInt();
			int maxDamage = (*iter)["max_damage"].asInt();
			addItem = new Weapon;
			addItemResult = static_cast<Weapon*>(addItem)->init(itemId, weaponType, itemName, minDamage, maxDamage, price, description);
			break;
		}
		case ITP_SEED: {
			eCropType cropType = (eCropType)(*iter)["crop_type"].asInt();
			addItem = new Seed;
			addItemResult = static_cast<Seed*>(addItem)->init(itemId, cropType, itemName, price, description);
			break;
		}
		case ITP_FRUIT: {
			int energy = (*iter)["eneregy"].asInt();
			int hp = (*iter)["hp"].asInt();
			eCropType cropType = (eCropType)(*iter)["crop_type"].asInt();
			addItem = new Fruit;
			addItemResult = static_cast<Fruit*>(addItem)->init(itemId, cropType, itemName, price, energy,hp, description);
			break;
		}
		case ITP_ORE: {
			eOreType oreType = (eOreType)(*iter)["ore_type"].asInt();
			addItem = new Ore;
			addItemResult = static_cast<Ore*>(addItem)->init(itemId, oreType, itemName, price, description);
			break;
		}
		case ITP_ORE_BAR: {
			eOreType oreType = (eOreType)(*iter)["ore_type"].asInt();
			addItem = new OreBar;
			addItemResult = static_cast<OreBar*>(addItem)->init(itemId, oreType, itemName, price, description);
			break;
		}
		case ITP_FORAGE: {
			eForageType forageType = (eForageType)(*iter)["forage_type"].asInt();
			addItem = new Forage;
			addItemResult = static_cast<Forage*>(addItem)->init(itemId, forageType, itemName, price, description);
			break;
		}
		case ITP_CRAFTING: {
			eCraftablesType craftingType = (eCraftablesType)(*iter)["crafting_type"].asInt();
			addItem = new Craftable;
			addItemResult = static_cast<Craftable*>(addItem)->init(itemId, craftingType, itemName, description);
;			Json::Value ingredientList = (*iter)["ingredient"];
			for (auto iterIg = ingredientList.begin(); iterIg != ingredientList.end(); ++iterIg) {
				static_cast<Craftable*>(addItem)->addIngredient(JSONMANAGER->convertUnicodeString((*iterIg)["item_id"].asString()), (*iterIg)["amount"].asInt());
			}
			break;
		}
		default:
			//!DO NOTHING!
			break;
		}

		if (FAILED(addItemResult)) {
			SAFE_DELETE(addItem);
			LOG::e(LOG_ITEM, "아이템 생성 실패: \t" + itemId);
		} else {
			mVItem.insert(make_pair(itemId, addItem));
			LOG::d(LOG_ITEM, "아이템 생성 성공: \t" + itemId);
		}
	}

	LOG::d_blue("=================== 아이템 생성 종료 ==========================");

	return S_OK;
}

void ItemManager::release(void)
{
}

Item* ItemManager::findItem(string itemId)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		return key->second;
	}

	return nullptr;
}

const Item* ItemManager::findItemReadOnly(string itemId)
{
	auto key = mVItem.find(itemId);

	if (key != mVItem.end())
	{
		return key->second;
	}

	LOG::e(LOG_ITEM, "아이템 검색 실패 : " + itemId);
	return nullptr;
}