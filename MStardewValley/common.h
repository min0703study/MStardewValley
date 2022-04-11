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
};

enum ePlayerStat {
	PS_IDLE,
	PS_WALK,
	PS_ATTACK_1,
	PS_ATTACK_2,
	PS_HOLD_IDLE,
	PS_HOLD_WALK,
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

enum eItemType {
	ITP_TOOL,
	ITP_WEAPON,
	ITP_NOLMAR,
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

enum eMineStoneType {
	MT_NORMAL_1,
	MT_NORMAL_2,
	MT_NORMAL_3,
	MT_NORMAL_4,
	MT_NORMAL_5,
	MT_NORMAL_6,
	MT_COPPER,
	MT_IRON,
	MT_GOLD,
	MT_END
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

enum eCropKinds {
	CK_PARSNIP,
	CK_END
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

#define TILE_SIZE		70.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	50.0f
#define PLAYER_HAIR_HEIGHT	100.0f
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f

#define ROCK_WIDTH		TILE_SIZE
#define ROCK_HEIGHT		TILE_SIZE

#define ROCK_IMG_WIDTH		(ROCK_WIDTH * 0.8)
#define ROCK_IMG_HEIGHT		(ROCK_HEIGHT * 0.9)

#define MAX_TOOLBAR_INDEX		12

#define INVENTORY_BOX_WIDTH		TILE_SIZE * 0.9
#define INVENTORY_BOX_HEIGHT	TILE_SIZE * 0.9

#define WEAPON_SIZE_WIDTH  TILE_SIZE * 1.0f
#define WEAPON_SIZE_HEIGHT TILE_SIZE * 1.0f

#define ITEM_SIZE_WIDTH  TILE_SIZE * 1.0f
#define ITEM_SIZE_HEIGHT TILE_SIZE * 1.0f

#define WEAPON_IMG_SIZE_WIDTH  TILE_SIZE * 0.8f
#define WEAPON_IMG_SIZE_HEIGHT TILE_SIZE * 0.8f

#define MAP_FILE_PATH			"Resources/Map/"