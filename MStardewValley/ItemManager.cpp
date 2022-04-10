#include "Stdafx.h"
#include "ItemManager.h"
#include "Item.h"

HRESULT ItemManager::init(void)
{
	return S_OK;
}

void ItemManager::release(void)
{
	//
}

Item* ItemManager::addItem(string itemId, eItemType itemType)
{
	Item* item = findItem(itemId, true);

	if (item) {
		return item;
	}

	item = new Item;
	if (FAILED(item->init("", itemId, itemType, 0.0f, 0.0f, ITEM_SIZE_WIDTH, ITEM_SIZE_HEIGHT)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[�Ϲ�]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Weapon* ItemManager::addWeapon(string itemId, eWeaponType mWeaponType)
{
	Weapon* item = findWeapon(itemId, true);

	if (item) {
		return item;
	}

	item = new Weapon;
	if (FAILED(item->init("", itemId, mWeaponType, 0.0f, 0.0f, WEAPON_SIZE_WIDTH, WEAPON_SIZE_HEIGHT)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[����]������ ���� : \t" + itemId);
	mVItem.insert(make_pair(itemId, item));
	return nullptr;
}

Tool* ItemManager::addTool(string itemId, eToolType eToolType)
{
	Tool* item = findTool(itemId, true);
	if (item) {
		return item;
	}

	item = new Tool;
	if (FAILED(item->init("", itemId, eToolType, 0.0f, 0.0f, WEAPON_SIZE_WIDTH, WEAPON_SIZE_HEIGHT)))
	{
		SAFE_DELETE(item);
		return NULL;
	}

	LOG::d(LOG_ITEM, "[��]������ ���� : \t" + itemId);
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