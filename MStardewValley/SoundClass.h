#pragma once
#include "SingletonBase.h"

class SoundClass: public SingletonBase<SoundClass>
{
public:
	const char* MenuBackBgm = "메뉴 배경음";
	const char* MenuBtnClickEffect = "메뉴 버튼 클릭 이팩트";
	const char* MenuBtnMouseOverEffect = "메뉴 버튼 마우스 오버 이팩트";

	const char* GameBackBgm = "게임 배경음";
	const char* MineBackBgm = "광산 배경음";

	const char* StepWood = "나무 발소리";
	const char* StepSand = "흙 발소리";
	const char* StepStone = "돌 발소리";
	const char* StepGrassy = "유리 발소리";

	const char* DoorOpen = "문 여는 소리";

	const char* AttackRock = "돌 캐기";
	const char* AttackTree = "나무 베기";
	const char* AttackWeed = "잡초 베기";
	const char* UseHoe = "괭이 사용";
	const char* UseWeapon = "무기 사용";
	const char* UseWateringCan = "물뿌리개";
	const char* PickUpItem = "아이템 주음";
	const char* Harvesting = "수확";


	const char* ACCESS_MENU_ON = "ACCESS_MENU_ON";
	const char* ACCESS_MENU_OFF = "ACCESS_MENU_OFF";
	
	const char* SelectToolbar = "툴바 선택";

	const char* MonsterDead = "몬스터 죽음";
	const char* PlayerHit = "플레이어 피격";
	const char* LadderDown = "내려가는 소리";

	HRESULT init(void);
	virtual void release(void);
};

