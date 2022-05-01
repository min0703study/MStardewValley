#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "�޴� �����";
	const char* MenuBtnClickEffect = "�޴� ��ư Ŭ�� ����Ʈ";
	const char* MenuBtnMouseOverEffect = "�޴� ��ư ���콺 ���� ����Ʈ";

	const char* GameBackBgm = "���� �����";
	const char* MineBackBgm = "���� �����";

	const char* StepWood = "���� �߼Ҹ�";
	const char* StepSand = "�� �߼Ҹ�";
	const char* StepStone = "�� �߼Ҹ�";
	const char* StepGrassy = "���� �߼Ҹ�";

	const char* DoorOpen = "�� ���� �Ҹ�";

	const char* AttackRock = "�� ĳ��";
	const char* AttackTree = "���� ����";
	const char* AttackWeed = "���� ����";
	const char* UseHoe = "���� ���";
	const char* UseWeapon = "���� ���";
	const char* UseWateringCan = "���Ѹ���";
	const char* PickUpItem = "������ ����";
	const char* Harvesting = "��Ȯ";


	const char* ACCESS_MENU_ON = "ACCESS_MENU_ON";
	const char* ACCESS_MENU_OFF = "ACCESS_MENU_OFF";
	
	const char* SelectToolbar = "���� ����";

	const char* MonsterDead = "���� ����";
	const char* PlayerHit = "�÷��̾� �ǰ�";
	const char* LadderDown = "�������� �Ҹ�";

	HRESULT init(void);
	virtual void release(void);
};

