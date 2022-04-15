#pragma once
#include "SingletonBase.h"

class JsonClass : public SingletonBase<JsonClass>
{
public:
	const char* MapInfo = "맵 정보";
	const char* ItemInfo = "아이템 정보";

	HRESULT init(void);
	virtual void release(void);
};

