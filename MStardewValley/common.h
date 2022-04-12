#pragma once

enum eMapToolCtrl {
	MC_ERASER,
	MC_DRAW_ONE
};

enum eMapSprite {
	MS_MINE_1TO30,
	MS_OUTDOOR_SPRING,
	MS_END
};

enum eXStandard {
	XS_LEFT,
	XS_RIGHT,
	XS_CENTER,
};

enum eYStandard {
	YS_TOP,
	YS_BOTTOM,
	YS_CENTER,
};

enum eGameDirection {
	GD_UP,
	GD_RIGHT,
	GD_LEFT,
	GD_DOWN,
	GD_END
};

enum ePlayerAniStat {
	PAS_IDLE,
	PAS_WALK,
	PAS_ATTACK_1,
	PAS_ATTACK_2,
	PAS_HOLD_IDLE,
	PAS_HOLD_WALK,
	PAS_HARVESTING,
	PAS_END,
};

enum eGameFixedUI {
	GFU_TOOLBAR,
	GFU_END,
};

enum ePlayerStat {
	PS_IDLE,
	PS_WALK,
	PS_ATTACK,
	PS_GRAP,
	PS_END,
};

enum eItemStat {
	IS_GRAP,
	IS_USE_UP,
	IS_USE_RIGHT,
	IS_USE_LEFT,
	IS_USE_DOWN,
	IS_END,
};

enum eHoedPos {
	HP_SINGLE,
	HP_V_TOP,
	HP_V_CENTER,
	HP_V_BOTTOM,
	HP_H_LEFT,
	HP_H_CENTER,
	HP_H_RIGHT,
	HP_R_LEFT_TOP,
	HP_R_TOP,
	HP_R_RIGHT_TOP,
	HP_R_LEFT,
	HP_R_CENTER,
	HP_R_RIGHT,
	HP_R_LEFT_BOTTOM,
	HP_R_BOTTOM,
	HP_R_RIGHT_BOTTOM,
	HP_END
};

enum eHoedStat {
	HS_NORMAL,
	HS_WET,
	HS_END,
};

enum eItemType {
	ITP_TOOL,
	ITP_WEAPON,
	ITP_SEED,
	ITP_CROP,
	ITP_END
};


enum eToolType {
	TT_PICK, //°î±ªÀÌ
	TT_AXE, //µµ³¢
	TT_WATERING_CAN, //¹°»Ñ¸®°Ô
	TT_HOE, //´ÙÁö´Â°Å
	TT_END
};

enum eWeaponType {
	WT_NORMAL, //°î±ªÀÌ
	WT_END
};

enum eToolLevel {
	TL_NORMAL,
	TL_COPPER,
	TL_IRON,
	TL_GOLD,
	TL_IRIDIUM,
	TL_END
};

enum eLocation {
	L_NONE,
	L_MINE_1,
	L_MINE_2,
	L_FARM,
	L_HOME,
	L_BEACH
};

enum eMapType {
	MT_MINE,
	MT_OUTDOOR,
};

enum eMineLevel {
	ML_ONE,
	ML_TWO,
	ML_TREE
};

enum eRockType {
	RT_NORMAL_1,
	RT_NORMAL_2,
	RT_NORMAL_3,
	RT_NORMAL_4,
	RT_NORMAL_5,
	RT_NORMAL_6,
	RT_COPPER,
	RT_IRON,
	RT_GOLD,
	RT_END
};

enum eMonsterType {
	MST_CAVE_FLY,
	MST_GRUB,
	MST_END
};

enum eMineStoneStat {
	IDLE,
	ATTACK,
	CRASH,
};

enum eCropType {
	CT_PARSNIP,
	CT_END
};

typedef struct tagItem {
	int Id;
	
	eItemType Type;
	
	string ImgKey;
	string Name;
	
	int Price;
} ItemBase;

typedef struct tagMapTileInfo {
	eMapType MapType;

	string FileName;

	int XCount;
	int YCount;

	int EnterenceIndex;

} MapTileInfo;

#define GAME_FONT				L"Leferi Base Type Bold"
#define TRANCECOLOR				RGB(255, 0, 255)

#define PLAYER_MOVE_SPEED		4.0f			
#define PLAYER_ANI_FRAME_SEC	10.0f			
#define WEAPON_ANI_FRAME_SEC	7.0f;
#define TOOL_ANI_FRAME_SEC 	6.0f;

#define TILE_SIZE		70.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	62.0f
#define PLAYER_HAIR_HEIGHT	124.0f
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f

#define ROCK_WIDTH		TILE_SIZE
#define ROCK_HEIGHT		TILE_SIZE

#define ROCK_IMG_WIDTH		(ROCK_WIDTH * 0.8)
#define ROCK_IMG_HEIGHT		(ROCK_HEIGHT * 0.9)

#define MAX_TOOLBAR_INDEX		12
#define INVENTORY_SIZE			24

#define INVENTORY_BOX_SIZE		TILE_SIZE * 0.9

#define WEAPON_SIZE_WIDTH  TILE_SIZE * 1.0f
#define WEAPON_SIZE_HEIGHT TILE_SIZE * 1.0f

#define ITEM_SIZE_WIDTH  TILE_SIZE * 1.0f
#define ITEM_SIZE_HEIGHT TILE_SIZE * 1.0f

#define WEAPON_IMG_SIZE_WIDTH  TILE_SIZE * 0.8f
#define WEAPON_IMG_SIZE_HEIGHT TILE_SIZE * 0.8f

#define MAP_FILE_PATH			"Resources/Map/"