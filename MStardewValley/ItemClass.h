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
	const char*	PARSNIP = "�Ľ��� ����";
	const char*	POTATO_SEED = "���� ����";
	const char*	POTATO = "���� ����";
	const char* CAULIFLOWER = "�ݸ��ö�� ����";
	const char* CAULIFLOWER_SEED = "�ݸ��ö�� ����";
	const char* BEEN = "�� ����";
	const char* BEEN_SEED = "�� ����";

	const char* STONE_NORMAL = "�Ϲ� ��";
};

