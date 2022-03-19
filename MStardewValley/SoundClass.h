#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "�޴� �����";
	const char* MenuBtnClickEffect = "�޴� ��ư Ŭ�� ����Ʈ";
	const char* MenuBtnMouseOverEffect = "�޴� ��ư ���콺 ���� ����Ʈ";

	HRESULT init(void);
	virtual void release(void);
};

