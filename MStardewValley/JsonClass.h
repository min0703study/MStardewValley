#pragma once
#include "SingletonBase.h"

class JsonClass : public SingletonBase<JsonClass>
{
public:
	const char* MapInfo = "¸Ê Á¤º¸";

	HRESULT init(void);
	virtual void release(void);
};

