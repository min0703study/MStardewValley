#include "Stdafx.h"
#include "JsonManager.h"

HRESULT JsonManager::init(void)
{
	return S_OK;
}

void JsonManager::release(void)
{
}

Json::Value JsonManager::addJsonValue(string strKey, string fileName)
{
	Json::Value tempJson = findJsonValue(strKey, true);
	if (tempJson) return tempJson;

	Json::Value json = JSONSAVELOADER->loadJsonFile(fileName);

	if (json == NULL)
	{
		LOG::e(fileName + " : json ������ ���� ����");
		return NULL;
	} else {
		LOG::d(fileName + " : json ���� ����");
	}

	JsonFile* addJson = new JsonFile();
	addJson->JsonValue = json;
	addJson->FileName = fileName;

	mVJson.insert(make_pair(strKey, addJson));

	return tempJson;
}

Json::Value JsonManager::findJsonValue(string strKey, bool isCreate)
{
	auto key = mVJson.find(strKey);

	if (key != mVJson.end())
	{
		LOG::d("json �˻� ���� : " + strKey);
		return key->second->JsonValue;
	}
	else if (!isCreate) {
		LOG::w("json �˻� ���� : " + strKey);
	}

	return Json::Value();
}

JsonFile* JsonManager::findJsonFile(string strKey, bool isCreate)
{
	auto key = mVJson.find(strKey);

	if (key != mVJson.end())
	{
		LOG::d("json �˻� ���� : " + strKey);
		return key->second;
	}
	else if (!isCreate) {
		LOG::w("json �˻� ���� : " + strKey);
	}

	return nullptr;
}

HRESULT JsonManager::saveJsonFile(string strKey, Json::Value saveJson)
{
	JsonFile* tempJson = findJsonFile(strKey, true);
	JSONSAVELOADER->saveJsonFile((tempJson->FileName).c_str(), saveJson);
	return S_OK;
}

