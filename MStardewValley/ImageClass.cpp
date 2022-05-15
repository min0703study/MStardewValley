#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	LOG::d_blue("=======================�̹��� ���ҽ� �ʱ� ���� ���� ==============================");

	//Common
	IMAGEMANAGER->addImage(Cursor, "Resources/Images/UI/mouse_cursor.bmp", 32, 40, true);
	GDIPLUSMANAGER->addImage(UISetupBox, "Resources/Images/UI/ui_box.png", 840, 576);
	GDIPLUSMANAGER->addImage(UIVScrollBar, "Resources/Images/UI/scroll_v_bar.png", 24, 496);
	GDIPLUSMANAGER->addImage(UIVScrollBtn, "Resources/Images/UI/scroll_v_btn.png", 24, 200);
	GDIPLUSMANAGER->addImage(UIHScrollBar, "Resources/Images/UI/scroll_h_bar.png", 496, 24);
	GDIPLUSMANAGER->addImage(UIHScrollBtn, "Resources/Images/UI/scroll_h_btn.png", 200, 24);

	//�޴�
	IMAGEMANAGER->addImage(MenuBack, "Resources/Images/Menu/menu_bg_skys.bmp", WINSIZE_INT_X, WINSIZE_INT_Y, false);
	GDIPLUSMANAGER->addImage(MenuBackLogo, "Resources/Images/Menu/menu_bg_logo.png", 1192, 549);
	IMAGEMANAGER->addImage(MenuBackCloud, "Resources/Images/Menu/menu_bg_cloud.bmp",  4560, 1080, true, RGB(255,0,255));
	GDIPLUSMANAGER->addImage(MenuBtnMaptool, "Resources/Images/Menu/menu_btn_maptool.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnStart, "Resources/Images/Menu/menu_btn_new_game.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtnExit, "Resources/Images/Menu/menu_btn_exit.png", 222, 174);
	GDIPLUSMANAGER->addImage(MenuBtn, "Resources/Images/UI/button.png", 222, 174);

	//���� - �ȷ�Ʈ
	GDIPLUSMANAGER->addFrameImage(MapOutdoorSpring, "Resources/Images/MapTool/Tiles/3x/outdoor(spring).png", 900, 3204, 25, 89);
	GDIPLUSMANAGER->addFrameImage(MapMines1To30, "Resources/Images/MapTool/Tiles/3x/mines(1to30).png", 768, 864, 16, 18);
	GDIPLUSMANAGER->addFrameImage(MapTownInterior, "Resources/Images/MapTool/Tiles/3x/town_interior.png", 1152, 2448, 32, 68);
	
	//���� - UI
	GDIPLUSMANAGER->addImage(MapBtnCollision, "Resources/Images/MapTool/UI/btn_collision.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnMovable, "Resources/Images/MapTool/UI/btn_movable.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnObjectGroup, "Resources/Images/MapTool/UI/btn_object_group.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnEraser, "Resources/Images/MapTool/UI/btn_eraser.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSelect, "Resources/Images/MapTool/UI/btn_select.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnNone, "Resources/Images/MapTool/UI/btn_none.png", 80, 76);
	GDIPLUSMANAGER->addImage(MapBtnSave, "Resources/Images/MapTool/UI/btn_save.png", 165, 76);
	GDIPLUSMANAGER->addImage(MapBtnLoad, "Resources/Images/MapTool/UI/btn_load.png", 165, 76);
	GDIPLUSMANAGER->addImage(MapBtnBack, "Resources/Images/MapTool/UI/btn_back.png", 202, 76);
	GDIPLUSMANAGER->addImage(MapBtnSelectMine, "Resources/Images/MapTool/UI/btn_select_mine.png", 64, 64);
	GDIPLUSMANAGER->addImage(MapBtnSelectFarm, "Resources/Images/MapTool/UI/btn_select_farm.png", 64, 64);
	GDIPLUSMANAGER->addImage(MapBtnSelectInterior, "Resources/Images/MapTool/UI/btn_select_interior.png", 64, 64);

	//UI
	GDIPLUSMANAGER->addImage(Toolbar, "Resources/Images/GameUI/toolbar.png", 800, 96);
	GDIPLUSMANAGER->addImage(MoneyBoard, "Resources/Images/GameUI/money_board.png", 260, 76);
	GDIPLUSMANAGER->addImage(Clock, "Resources/Images/GameUI/clock.png", 284, 160);
	GDIPLUSMANAGER->addImage(ClockHand, "Resources/Images/GameUI/clock_hand.png", 28, 71);
	GDIPLUSMANAGER->addImage(EnergePGBarF, "Resources/Images/GameUI/energe_progress_bar_front.png", 48, 330);
	GDIPLUSMANAGER->addImage(EnergePGBarB, "Resources/Images/GameUI/energe_progress_bar_back.png", 48, 330);
	GDIPLUSMANAGER->addImage(HPPGBarF, "Resources/Images/GameUI/hp_progress_bar_front.png", 48, 279);
	GDIPLUSMANAGER->addImage(HPPGBarB, "Resources/Images/GameUI/hp_progress_bar_back.png", 48, 279);
	GDIPLUSMANAGER->addImage(InventoryBox, "Resources/Images/GameUI/inventory_box.png", 848, 276);
	GDIPLUSMANAGER->addImage(InventoryRadioBtn, "Resources/Images/GameUI/inventory_radio_btn.png", 64, 64);
	GDIPLUSMANAGER->addImage(CraftRadioBtn, "Resources/Images/GameUI/craft_radio_btn.png", 64, 64);

	GDIPLUSMANAGER->addImage(ItemInfoName, "Resources/Images/UI/item_info_name.png", 296, 145);
	GDIPLUSMANAGER->addImage(ItemInfoContent, "Resources/Images/UI/item_info_content.png", 296, 274);
	GDIPLUSMANAGER->addImage(ItemInfoEnd, "Resources/Images/UI/item_info_end.png", 296, 20);
	GDIPLUSMANAGER->addImage(EventBox, "Resources/Images/GameUI/show_item_box.png", 213, 96);

	//PLAYER
	GDIPLUSMANAGER->addFrameImage(PlayerSpriteMan, "Resources/Images/Player/3x/player_base_sprite_man.png", 864, 1512, 24, 21);
	GDIPLUSMANAGER->addFrameImage(PlayerSpriteHair, "Resources/Images/Player/player_hair_sprite.png", 288, 864, 8, 12);
	GDIPLUSMANAGER->addFrameImage(PlayerSpriteCloth, "Resources/Images/Player/player_cloth_sprite.png", 288, 504, 16, 28);


	//MINES - ext
	GDIPLUSMANAGER->addFrameImage(MineRockSprite, "Resources/Images/Mines/mines_rock_sprite.png", 384, 71, 23, 4);
	GDIPLUSMANAGER->addFrameImage(WeedSprite, "Resources/Images/Mines/mines_weed_sprite.png", 119, 51, 7, 3);
	GDIPLUSMANAGER->addFrameImage(MinesItemSprite, "Resources/Images/Mines/mines_item_sprite.png", 384, 71, 23, 4);
	GDIPLUSMANAGER->addImage(MonsterSprite, "Resources/Images/Monster/monster_sprite.png", 950, 1136);
	GDIPLUSMANAGER->addFrameImage(WeaponSprite, "Resources/Images/Weapon/3x/weapon_sprite.png", 384, 432, 8, 9);
	GDIPLUSMANAGER->addImage(WeaponIcon, "Resources/Images/Weapon/weapon_icon.png", 44, 44);
	GDIPLUSMANAGER->addImage(HpIcon, "Resources/Images/GameUI/hp_icon.png", 34, 34);
	GDIPLUSMANAGER->addImage(EnergyIcon, "Resources/Images/GameUI/energy_icon.png", 34, 34);
	GDIPLUSMANAGER->addFrameImage(TreeSprite, "Resources/Images/Tree/tree_sprite.png", 224, 512,14,32);

	//ITEM
	GDIPLUSMANAGER->addFrameImage(ToolSprite, "Resources/Images/Tool/3x/tool_sprite.png", 1008, 1152, 21, 23);
	GDIPLUSMANAGER->addFrameImage(CropsSeedSprite, "Resources/Images/Crops/3x/seed_sprite.png", 441, 216, 9, 4);
	GDIPLUSMANAGER->addFrameImage(CropsStageSprite, "Resources/Images/Crops/3x/crop_sprite.png", 1008, 1632, 21, 34);

	GDIPLUSMANAGER->addFrameImage(HoedSprite, "Resources/Images/Hoed/hoed_sprite.png", 192, 192, 12, 12);
	GDIPLUSMANAGER->addImage(ShopMenuItem, "Resources/Images/Shop/menu_item.png", 1048, 110);
	GDIPLUSMANAGER->addFrameImage(ForageSprite, "Resources/Images/Forage/3x/forage_sprite.png", 264, 308, 6, 7);

	//NPC
	GDIPLUSMANAGER->addFrameImage(NpcSpritePierreP, "Resources/Images/NPC/3x/pierre_sprite_p.png", 456, 681, 2, 3);
	GDIPLUSMANAGER->addFrameImage(NpcSpritePierreA, "Resources/Images/NPC/3x/pierre_sprite_a.png", 193, 577, 4, 6);
	GDIPLUSMANAGER->addImage(NpcSpriteMarlonP, "Resources/Images/NPC/3x/marlon_sprite_p.png", 228, 225);
	GDIPLUSMANAGER->addFrameImage(NpcSpriteMarlonA, "Resources/Images/NPC/3x/marlon_sprite_a.png", 192, 378, 4, 4);
	GDIPLUSMANAGER->addFrameImage(NpcSpriteClintA, "Resources/Images/NPC/3x/clint_sprite_a.png", 192, 576, 4, 6);
	GDIPLUSMANAGER->addFrameImage(NpcSpriteClintP, "Resources/Images/NPC/3x/clint_sprite_p.png", 456, 681, 2, 3);

	GDIPLUSMANAGER->addFrameImage(EffectSprite, "Resources/Images/Effect/effect_sprite.png", 160, 832, 10, 52);
	GDIPLUSMANAGER->addFrameImage(CraftablesSprite, "Resources/Images/Craftables/craftables_sprite.png", 128, 1152, 8, 72);

	GDIPLUSMANAGER->addImage(TileSize, "Resources/Images/tile_size.png", 1282, 752);
	GDIPLUSMANAGER->addImage(FuranceOverEvent, "Resources/Images/Craftables/furance_over_event.png", 80, 96);
	GDIPLUSMANAGER->addImage(QuestionBox, "Resources/Images/GameUI/question_box.png", 1277, 357);

	LOG::d_blue("=======================�̹��� ���ҽ� �ʱ� ���� ���� ==============================");
	return S_OK;
}

void ImageClass::release(void)
{

}