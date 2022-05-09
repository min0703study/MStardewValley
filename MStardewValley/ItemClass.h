#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	//����
	const char* PICK = "���";
	const char* COPPER_PICK = "���� ���";
	const char* IRON_PICK = "ö ���";

	const char*	HOE = "ȣ��";
	const char*	COPPER_HOE = "���� ȣ��";
	const char*	IRON_HOE = "ö ȣ��";

	const char*	AXE = "����";
	const char*	COPPER_AXE = "���� ����";
	const char*	IRON_AXE = "ö ����";

	const char*	WATERING_CAN = "���Ѹ���";
	const char*	COPPER_WATERING_CAN = "���� ���Ѹ���";
	const char*	IRON_WATERING_CAN = "ö ���Ѹ���";

	const char*	SICKLE = "��";

	//����
	const char* WEAPON = "�콼 ��";
	const char* WOODEN_BLADE = "��";
	const char* IRON_DIRCT = "ö ��ũ";
	const char* PIRATES_SWORD = "������ ��";
	const char* WOOD_MALLET = "���� ��ġ";
	const char* BONE_SWORD = "���� ��";
	const char* INSECT_HEAD = "���� �Ӹ�";

	//����
	const char*	PARSNIP_SEED = "�Ľ��� ����";
	const char*	PARSNIP = "�Ľ��� ����";
	const char*	POTATO_SEED = "���� ����";
	const char*	POTATO = "���� ����";
	const char* CAULIFLOWER = "�ݸ��ö�� ����";
	const char* CAULIFLOWER_SEED = "�ݸ��ö�� ����";
	const char* BEEN = "�� ����";
	const char* BEEN_SEED = "�� ����";
	
	//�ڿ�
	const char* WOOD = "���� ����";
	const char* FIBER = "����";
	const char* STONE_NORMAL = "�Ϲ� ��";

	//����
	const char* IRON = "ö����";
	const char* GOLD = "�ݱ���";
	const char* COPPER = "��������";
	const char* COAL = "��ź";

	//�ֱ�
	const char* IRON_BAR = "ö �ֱ�";
	const char* GOLD_BAR = "�� �ֱ�";
	const char* COPPER_BAR = "���� �ֱ�";

	//
	const char* FURNACE = "�뱤��";
};

