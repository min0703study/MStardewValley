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
		LOG::e(fileName + " : json 데이터 생성 실패");
		return NULL;
	} else {
		LOG::d(fileName + " : json 생성 성공");
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
		LOG::d("json 검색 성공 : " + strKey);
		return key->second->JsonValue;
	}
	else if (!isCreate) {
		LOG::w("json 검색 실패 : " + strKey);
	}

	return Json::Value();
}

JsonFile* JsonManager::findJsonFile(string strKey, bool isCreate)
{
	auto key = mVJson.find(strKey);

	if (key != mVJson.end())
	{
		LOG::d("json 검색 성공 : " + strKey);
		return key->second;
	}
	else if (!isCreate) {
		LOG::w("json 검색 실패 : " + strKey);
	}

	return nullptr;
}

HRESULT JsonManager::saveJsonFile(string strKey, Json::Value saveJson)
{
	JsonFile* tempJson = findJsonFile(strKey, true);
	JSONSAVELOADER->saveJsonFile((tempJson->FileName).c_str(), saveJson);
	return S_OK;
}

string JsonManager::convertUnicodeString(string oString)
{
	wstring mWString = mConverter.from_bytes(oString);

	string resultString;
	string buff(MB_CUR_MAX, '\0');

	for (wchar_t const & wc : mWString)
	{
		int mbCharLen = std::wctomb(&buff[0], wc);

		if (mbCharLen < 1) { break; }

		for (int i = 0; i < mbCharLen; ++i)
		{
			resultString += buff[i];
		}
	}

	return resultString;
}

