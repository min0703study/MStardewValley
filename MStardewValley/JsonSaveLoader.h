#pragma once
#include "SingletonBase.h"
class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(string fileName);

public:
	HRESULT init(void);
	void release(void);

	void saveJsonFile(char* fileName, Json::Value root);
	Json::Value loadJsonFile(string fileName);

	JsonSaveLoader() {};
	~JsonSaveLoader() {};
};

