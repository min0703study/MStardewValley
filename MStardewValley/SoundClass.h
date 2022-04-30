#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "�޴� �����";
	const char* MenuBtnClickEffect = "�޴� ��ư Ŭ�� ����Ʈ";
	const char* MenuBtnMouseOverEffect = "�޴� ��ư ���콺 ���� ����Ʈ";

	const char* GameBackBgm = "���� �����";

	const char* StepWood = "���� �߼Ҹ�";
	const char* StepSand = "�� �߼Ҹ�";
	const char* StepStone = "�� �߼Ҹ�";
	const char* StepGrassy = "���� �߼Ҹ�";

	const char* AttackRock = "�� ĳ�� ȿ����";
	const char* AttackTree = "���� ���� ȿ����";
	const char* AttackWeed = "���� ���� ȿ����";
	const char* UseHoe = "���� ���";
	const char* UseWateringCan = "���Ѹ��� ���";
	const char* PickUpItem = "������ ����";
	const char* ACCESS_MENU_ON = "ACCESS_MENU_ON";
	const char* ACCESS_MENU_OFF = "ACCESS_MENU_OFF";
	const char* SelectToolbar = "���� ����";

	HRESULT init(void);
	virtual void release(void);
};

