#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	//����
	const char* PICK = "���";
	const char*	HOE = "ȣ��";
	const char*	AXE = "����";
	const char*	WATERING_CAN = "���Ѹ���";
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

