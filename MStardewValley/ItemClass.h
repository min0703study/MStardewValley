#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Ä®";
	const char* PICK = "°î±ªÀÌ";

	HRESULT init(void);
	virtual void release(void);
};

