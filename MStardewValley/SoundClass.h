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

	const char* AttackRock = "돌 캐기 효과음";
	const char* AttackTree = "나무 베기 효과음";
	const char* AttackWeed = "잡초 베기 효과음";
	const char* UseHoe = "괭이 사용";
	const char* UseWateringCan = "물뿌리개 사용";
	const char* PickUpItem = "아이템 주음";
	const char* ACCESS_MENU_ON = "ACCESS_MENU_ON";
	const char* ACCESS_MENU_OFF = "ACCESS_MENU_OFF";
	const char* SelectToolbar = "툴바 선택";

	HRESULT init(void);
	virtual void release(void);
};

