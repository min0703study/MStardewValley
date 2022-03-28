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
	GDIPLUSMANAGER->addImage(UIVScrollBar, "Resources/Images/UI/scroll_v_bar.png", 24, 496);
	GDIPLUSMANAGER->addImage(UIVScrollBtn, "Resources/Images/UI/scroll_v_btn.png", 24, 40);
	GDIPLUSMANAGER->addImage(UIHScrollBar, "Resources/Images/UI/scroll_h_bar.png", 496, 24);
	GDIPLUSMANAGER->addImage(UIHScrollBtn, "Resources/Images/UI/scroll_h_btn.png", 40, 24);


	//maptool �ȷ�Ʈ
	IMAGEMANAGER->addImage(MapSpringSprite, "Resources/Images/MapTool/sample_outdoor_spring.bmp", 400, 1264);
	GDIPLUSMANAGER->addImage(MapSpringSpriteG, "Resources/Images/MapTool/sample_outdoor_spring.png", 400, 1264);
	GDIPLUSMANAGER->addFrameImage(MapMines1To30, "Resources/Images/MapTool/Tiles/mines(1to30).png", 768, 864, 16, 18);
	
	//maptool btn
	GDIPLUSMANAGER->addImage(MapBtnEraser, "Resources/Images/MapTool/UI/btn_eraser.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSelect, "Resources/Images/MapTool/UI/btn_select.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnNone, "Resources/Images/MapTool/UI/btn_none.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSave, "Resources/Images/MapTool/UI/btn_save.png", 182, 76);
	GDIPLUSMANAGER->addImage(MapBtnLoad, "Resources/Images/MapTool/UI/btn_load.png", 203, 76);

	GDIPLUSMANAGER->addFrameImage(PlayerSpriteMan, "Resources/Images/MapTool/Player/player_sprite_m.png", 384, 672, 21, 24);

	return S_OK;
}

void ImageClass::release(void)
{

}