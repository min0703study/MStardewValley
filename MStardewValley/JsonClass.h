#pragma once
#include "SingletonBase.h"

class JsonClass : public SingletonBase<JsonClass>
{
public:
	const char* MapInfo = "�� ����";
	const char* ItemInfo = "������ ����";

	HRESULT init(void);
	virtual void release(void);
};

