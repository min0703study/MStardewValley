#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "메뉴 배경음";
	const char* MenuBtnClickEffect = "메뉴 버튼 클릭 이팩트";
	const char* MenuBtnMouseOverEffect = "메뉴 버튼 마우스 오버 이팩트";

	const char* GameBackBgm = "게임 배경음";

	const char* StepWood = "나무 발소리";
	const char* StepSand = "흙 발소리";
	const char* StepStone = "돌 발소리";
	const char* StepGrassy = "유리 발소리";

	HRESULT init(void);
	virtual void release(void);
};

