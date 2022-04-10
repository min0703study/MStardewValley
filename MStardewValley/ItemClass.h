#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Į";
	const char* PICK = "���";
	const char*	HOE = "ȣ��";
	const char*	PARSNIP_SEED = "�Ľ��� ����";

	HRESULT init(void);
	virtual void release(void);
};

