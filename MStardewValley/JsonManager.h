#pragma once
#include "SingletonBase.h"

typedef struct tagJsonFile {
	Json::Value JsonValue;
	string FileName;
} JsonFile;

class JsonManager : public SingletonBase<JsonManager>
{
private:
	typedef map<string, JsonFile*> mapJsonList;
	typedef map<string, JsonFile*>::iterator mapJsonIter;

private:
	mapJsonList mVJson;
public:
	HRESULT init(void);
	void release(void);
	map<string, string> mFilePathList;

	Json::Value addJsonValue(string strKey, string fileName);
	Json::Value findJsonValue(string strKey, bool isInit = false);
	JsonFile* findJsonFile(string strKey, bool isCreate);
	HRESULT saveJsonFile(string strKey, Json::Value saveJson);
};

