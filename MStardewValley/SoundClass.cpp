#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	LOG::d_blue("=======================사운드 리소스 초기 생성 시작 ==============================");
	SOUNDMANAGER->addSound(MenuBackBgm, "Resources/Sounds/menu1.ogg", true, true);
	SOUNDMANAGER->addSound(MenuBtnClickEffect, "Resources/Sounds/select.wav", true, false);
	SOUNDMANAGER->addSound(MenuBtnMouseOverEffect, "Resources/Sounds/mouse_over.wav", true, false);
	LOG::d_blue("=======================사운드 리소스 초기 생성 종료 ==============================");
	return S_OK;
}

void SoundClass::release(void)
{
}
