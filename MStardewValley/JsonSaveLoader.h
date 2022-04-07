#pragma once
#include "SingletonBase.h"
class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(const char* fileName, string data);
	void saveStringWithFileStream(const char* fileName, string data);

	string loadString(const char* fileName);
	string loadStringWithFileStream(string fileName);

public:
	HRESULT init(void);
	void release(void);

	void saveJsonFile(const char* fileName, Json::Value root);
	Json::Value loadJsonFile(string fileName);

	JsonSaveLoader() {};
	~JsonSaveLoader() {};
};

