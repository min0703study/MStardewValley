#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Į";
	const char* PICK = "���";
	const char*	HOE = "ȣ��";
	const char*	AXE = "����";
	const char*	WATERING_CAN = "���Ѹ���";
	const char*	PARSNIP_SEED = "�Ľ��� ����";
	const char*	PARSNIP = "�Ľ���";

	HRESULT init(void);
	virtual void release(void);
};

