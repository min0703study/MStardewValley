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

	HRESULT init(void);
	virtual void release(void);
};

