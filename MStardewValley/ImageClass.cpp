#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	//MENU
	IMAGEMANAGER->addImage(MenuBack, "Resources/Images/Menu/menu_bg_sky.bmp", WINSIZE_X, WINSIZE_Y, false);
	GDIPLUSMANAGER->addImage(MenuBackLogo, "Resources/Images/Menu/menu_bg_logo.png", 1191, 549);
	GDIPLUSMANAGER->addImage(MenuBackCloud, "Resources/Images/Menu/menu_bg_cloud.png",  4560, 1080);
	GDIPLUSMANAGER->addImage(MenuBtnMaptool, "Resources/Images/Menu/menu_btn_maptool.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnStart, "Resources/Images/Menu/menu_btn_new_game.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnExit, "Resources/Images/Menu/menu_btn_exit.png", 222, 174);

	IMAGEMANAGER->addImage(Cursor, "Resources/Images/UI/mouse_cursor.bmp", 32, 40, true);
	GDIPLUSMANAGER->addImage(MenuBtn, "Resources/Images/UI/button.png", 222, 174);

	GDIPLUSMANAGER->addImage(UISetupBox, "Resources/Images/UI/ui_box.png", 840, 576);
	GDIPLUSMANAGER->addImage(UIScrollBar, "Resources/Images/UI/scroll_bar.png", 24, 496);
	GDIPLUSMANAGER->addImage(UIScrollBtn, "Resources/Images/UI/scroll_btn.png", 24, 40);

	IMAGEMANAGER->addImage(MapSpringSprite, "Resources/Images/MapTool/sample_outdoor_spring.bmp", 400, 1264);
	GDIPLUSMANAGER->addImage(MapSpringSpriteG, "Resources/Images/MapTool/sample_outdoor_spring.png", 400, 1264);

	return S_OK;
}

void ImageClass::release(void)
{

}