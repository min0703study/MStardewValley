#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	LOG::d_blue("=======================이미지 리소스 초기 생성 시작 ==============================");
	//MENU
	IMAGEMANAGER->addImage(MenuBack, "Resources/Images/Menu/menu_bg_sky.bmp", WINSIZE_INT_X, WINSIZE_INT_Y, false);

	GDIPLUSMANAGER->addImage(MenuBackLogo, "Resources/Images/Menu/menu_bg_logo.png", 1191, 549);
	GDIPLUSMANAGER->addImage(MenuBackCloud, "Resources/Images/Menu/menu_bg_cloud.png",  4560, 1080);
	GDIPLUSMANAGER->addImage(MenuBtnMaptool, "Resources/Images/Menu/menu_btn_maptool.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnStart, "Resources/Images/Menu/menu_btn_new_game.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnExit, "Resources/Images/Menu/menu_btn_exit.png", 222, 174);

	IMAGEMANAGER->addImage(Cursor, "Resources/Images/UI/mouse_cursor.bmp", 32, 40, true);
	GDIPLUSMANAGER->addImage(MenuBtn, "Resources/Images/UI/button.png", 222, 174);

	GDIPLUSMANAGER->addImage(UISetupBox, "Resources/Images/UI/ui_box.png", 840, 576);
	GDIPLUSMANAGER->addImage(UIVScrollBar, "Resources/Images/UI/scroll_v_bar.png", 24, 496);
	GDIPLUSMANAGER->addImage(UIVScrollBtn, "Resources/Images/UI/scroll_v_btn.png", 24, 200);
	GDIPLUSMANAGER->addImage(UIHScrollBar, "Resources/Images/UI/scroll_h_bar.png", 496, 24);
	GDIPLUSMANAGER->addImage(UIHScrollBtn, "Resources/Images/UI/scroll_h_btn.png", 200, 24);

	//maptool 팔레트
	GDIPLUSMANAGER->addImage(MapSpringSprite, "Resources/Images/MapTool/sample_outdoor_spring.png", 400, 1264);
	GDIPLUSMANAGER->addFrameImage(MapMines1To30, "Resources/Images/MapTool/Tiles/mines(1to30).png", 768, 864, 16, 18);
	
	//maptool btn
	GDIPLUSMANAGER->addImage(MapBtnEraser, "Resources/Images/MapTool/UI/btn_eraser.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSelect, "Resources/Images/MapTool/UI/btn_select.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnNone, "Resources/Images/MapTool/UI/btn_none.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSave, "Resources/Images/MapTool/UI/btn_save.png", 182, 76);
	GDIPLUSMANAGER->addImage(MapBtnLoad, "Resources/Images/MapTool/UI/btn_load.png", 203, 76);
	GDIPLUSMANAGER->addImage(MapBtnSelectMine, "Resources/Images/MapTool/UI/btn_select_mine.png", 64, 64);
	GDIPLUSMANAGER->addImage(MapBtnSelectFarm, "Resources/Images/MapTool/UI/btn_select_farm.png", 64, 64);

	GDIPLUSMANAGER->addFrameImage(PlayerSpriteMan, "Resources/Images/Player/3x/player_base_sprite_man.png", 864, 1512, 24, 21);
	GDIPLUSMANAGER->addFrameImage(PlayerSpriteHair, "Resources/Images/Player/player_hair_sprite.png", 288, 864, 8, 12);
	GDIPLUSMANAGER->addFrameImage(PlayerSpriteCloth, "Resources/Images/Player/player_cloth_sprite.png", 288, 504, 16, 28);

	GDIPLUSMANAGER->addFrameImage(ToolSprite, "Resources/Images/Tool/3x/tool_sprite.png", 1008, 1152, 21, 23);
	GDIPLUSMANAGER->setSizeRatio(ToolSprite, 1.5f);

	GDIPLUSMANAGER->addFrameImage(MineRockSprite, "Resources/Images/Mines/mines_rock_sprite.png", 384, 71, 23, 4);
	GDIPLUSMANAGER->addImage(MonsterSprite, "Resources/Images/Monster/monster_sprite.png", 950, 1136);
	GDIPLUSMANAGER->addFrameImage(WeaponSprite, "Resources/Images/Weapon/3x/weapon_sprite.png", 384, 432, 8, 9);

	GDIPLUSMANAGER->addImage(Toolbar, "Resources/Images/GameUI/toolbar.png", 800, 96);


	LOG::d_blue("=======================이미지 리소스 초기 생성 종료 ==============================");
	return S_OK;
}

void ImageClass::release(void)
{

}