#include "Stdafx.h"
#include "JsonManager.h"

HRESULT JsonManager::init(void)
{
	return S_OK;
}

void JsonManager::release(void)
{
}

Json::Value * JsonManager::addJsonValue(string strKey, string fileName)
{
	Json::Value* tempJson = findJsonValue(strKey, true);

	if (tempJson) return tempJson;

	Json::Value json = JSONSAVELOADER->loadJsonFile(fileName);

	if (json == NULL)
	{
		LOG::e(fileName + " : json ������ ���� ����");
		return NULL;
	} else {
		LOG::d(fileName + " : json ���� ����");
	}

	mVJson.insert(make_pair(strKey, new Json::Value(json)));

	return tempJson;
}

Json::Value * JsonManager::findJsonValue(string strKey, bool isCreate)
{
	auto key = mVJson.find(strKey);

	if (key != mVJson.end())
	{
		return key->second;
	}
	else if (!isCreate) {
		LOG::w("json �˻� ���� : " + strKey);
	}

	return nullptr;
}
