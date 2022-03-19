#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "메뉴 배경음";
	const char* MenuBtnClickEffect = "메뉴 버튼 클릭 이팩트";
	const char* MenuBtnMouseOverEffect = "메뉴 버튼 마우스 오버 이팩트";

	HRESULT init(void);
	virtual void release(void);
};

