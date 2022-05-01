#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	LOG::d_blue("=======================사운드 리소스 초기 생성 시작 ==============================");
	SOUNDMANAGER->addSound(MenuBackBgm, "Resources/Sounds/menu1.ogg", true, true);
	SOUNDMANAGER->addSound(MenuBtnClickEffect, "Resources/Sounds/select.wav", true, false);
	SOUNDMANAGER->addSound(MenuBtnMouseOverEffect, "Resources/Sounds/mouse_over.wav", true, false);
	SOUNDMANAGER->addSound(GameBackBgm, "Resources/Sounds/calm1.ogg", true, true);
	SOUNDMANAGER->addSound(MineBackBgm, "Resources/Sounds/nuance2.ogg", true, true);
	SOUNDMANAGER->addSound(SelectToolbar, "Resources/Sounds/smallSelect.wav", false, false);
	
	/*
	SOUNDMANAGER->addSound(StepWood, "Resources/Sounds/step/woody_step.wav", false, false);
	SOUNDMANAGER->addSound(StepSand, "Resources/Sounds/step/sandy_step.wav", false, false);
	SOUNDMANAGER->addSound(StepStone, "Resources/Sounds/step/stone_step.wav", false, false);
	SOUNDMANAGER->addSound(StepGrassy, "Resources/Sounds/step/grassy_step.wav", false, false);

	SOUNDMANAGER->addSound(AttackRock, "Resources/Sounds/action/hammer.wav", false, false);
	SOUNDMANAGER->addSound(AttackTree, "Resources/Sounds/action/axe.wav", false, false);
	SOUNDMANAGER->addSound(AttackWeed, "Resources/Sounds/action/cut.wav", false, false);
	SOUNDMANAGER->addSound(Harvesting, "Resources/Sounds/action/harvest.wav", false, false);
	SOUNDMANAGER->addSound(UseHoe, "Resources/Sounds/action/hoeHit.wav", false, false);
	SOUNDMANAGER->addSound(UseWeapon, "Resources/Sounds/action/hoe.wav", false, false);
	SOUNDMANAGER->addSound(UseWateringCan, "Resources/Sounds/action/water_lap3.wav", false, false);
	SOUNDMANAGER->addSound(PickUpItem, "Resources/Sounds/action/pickUpItem.wav", false, false);
	SOUNDMANAGER->addSound(ACCESS_MENU_ON, "Resources/Sounds/bigDeSelect.wav", false, false);
	SOUNDMANAGER->addSound(ACCESS_MENU_OFF, "Resources/Sounds/bigSelect.wav", false, false);

	SOUNDMANAGER->addSound(DoorOpen, "Resources/Sounds/action/doorOpen.wav", false, false);
	SOUNDMANAGER->addSound(MonsterDead, "Resources/Sounds/monster/monsterdead.wav", false, false);
	SOUNDMANAGER->addSound(MonsterDead, "Resources/Sounds/monster/monsterdead.wav", false, false);
	SOUNDMANAGER->addSound(PlayerHit, "Resources/Sounds/monster/hitEnemy.wav", false, false);
	SOUNDMANAGER->addSound(LadderDown, "Resources/Sounds/stairsdown.wav", false, false);
	*/
	LOG::d_blue("=======================사운드 리소스 초기 생성 종료 ==============================");
	return S_OK;
}

void SoundClass::release(void)
{
}
