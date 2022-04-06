#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Į";
	const char* PICK = "���";

	HRESULT init(void);
	virtual void release(void);
};

