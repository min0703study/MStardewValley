#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	SOUNDMANAGER->addSound(MenuBackBgm, "Resources/Sounds/menu1.ogg", true, true);
	SOUNDMANAGER->addSound(MenuBtnClickEffect, "Resources/Sounds/select.wav", true, false);
	SOUNDMANAGER->addSound(MenuBtnMouseOverEffect, "Resources/Sounds/mouse_over.wav", true, false);

	return S_OK;
}

void SoundClass::release(void)
{
}
