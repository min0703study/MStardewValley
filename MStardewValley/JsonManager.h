#pragma once
#include "SingletonBase.h"

class JsonManager: public SingletonBase<JsonManager>
{
private:
	typedef map<string, Json::Value*> mapJsonList;
	typedef map<string, Json::Value*>::iterator mapJsonIter;
private:
	mapJsonList mVJson;
public:
	HRESULT init(void);
	void release(void);

	Json::Value* addJsonValue(string strKey, string fileName);
	Json::Value* findJsonValue(string strKey, bool isInit = false);
};

