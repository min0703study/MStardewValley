#pragma once
#define DEBUG_MODE				true

enum eMapToolCtrl {
	MC_ERASER,
	MC_DRAW,
	MC_COLLISION_TILE,
	MC_MOVABLE_TILE,
	MC_OBJECT_GROUP,
	MC_END
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
	PAS_WATER_THE_PLANT,
	PAS_END,
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

enum eHoedStat {
	HS_NORMAL,
	HS_WET,
	HS_END,
};

enum eItemType {
	ITP_TOOL,
	ITP_WEAPON,
	ITP_SEED,
	ITP_FRUIT,
	ITP_STONE,
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
	WT_NORMAL,
	WT_WOODEN_BLADE,
	WT_IRON_DIRCT,
	WT_PIRATES_SWORD,
	WT_WOOD_MALLET,
	WT_BONE_SWORD,
	WT_INSECT_HEAD,
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

enum eSpriteType {
	MP_MINE_1TO30,
	MP_OUTDOOR_SPRING,
	MP_TOWN_INTERIOR,
	MP_END
};

enum eShopType {
	SPT_PIERRE_SHOP,
	SPT_GILL_SHOP,
	SPT_END
};

enum eMapType {
	MT_MINE,
	MT_FARM,
	MT_HOME,
	MT_TOWN,
	MT_LOAD
};

enum eRockAniStat {
	RA_IDLE,
	RA_HIT,
	RA_CRASH,
	RA_END,
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

enum eStoneType {
	ST_NORMAL,
	ST_COPPER,
	ST_IRON,
	ST_GOLD,
	ST_END
};

enum eTreeType {
	TTP_NORMAL,
	TTP_END,
};

enum eMonsterType {
	MST_GRUB,
	MST_SLIME,
	MST_END
};

enum eNpcs {
	NPC_PIERRE,
	NPC_END
};

enum eNpcAniType {
	NAT_IDLE,
	NAT_END
};

enum eNpcPortraitsType {
	NPT_IDLE,
	NPT_END
};

enum eMineStoneStat {
	IDLE,
	ATTACK,
	CRASH,
};

enum eCropType {
	CT_PARSNIP,
	CT_POTATO,
	CT_BEEN,
	CT_CAULIFLOWER,
	CT_END
};

enum eAccessMenu {
	AM_INVENTORY,
	AM_END
};

typedef struct tagTileIndex {
	int X;
	int Y;
	int ORDER;

	bool operator==(const tagTileIndex& compObject) const {
		return compObject.X == X && compObject.Y == Y;
	};

	bool operator!=(const tagTileIndex& compObject) const {
		return compObject.X != X || compObject.Y != Y;
	};

	bool operator<(const tagTileIndex& compObject) const {
		if (Y != compObject.Y) {
			return Y < compObject.Y;
		}
		else {
			return X < compObject.X;
		}
	}

	tagTileIndex() :X(-1), Y(-1), ORDER(-1) {};
	tagTileIndex(int x, int y) :X(x), Y(y) {};
	tagTileIndex(int x, int y, int xSize) :X(x), Y(y) {
		ORDER = x + y * xSize;
	};

} TINDEX;


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
	string FilePath;

	int XCount;
	int YCount;

	//±¤»ê
	int Floor;
	int EnterenceIndex;
	string PaletteKey;
	int MonsterCount;
	int RockCount;

	int PortalCount;
} MapTileInfo;

typedef struct tagMapPortal {
	TINDEX TIndex;

	string ToMapKey;
	string ToSceneName;

	int ToPortal;

	tagMapPortal() : TIndex(TINDEX()), ToMapKey(""), ToSceneName(""), ToPortal(-1) {}
	tagMapPortal(TINDEX tIndex, string toSceneName, string toMapKey, int toPortal) : TIndex(tIndex), ToMapKey(toMapKey), ToSceneName(toSceneName), ToPortal(toPortal) {}
} MapPortal;

#define GAME_FONT				L"Leferi Base Type Bold"
#define GAME_FONT_2				L"SVBold Inner"
#define GAME_FONT_3				L"Sandoll ¹Ì»ý"

#define TRANCECOLOR				RGB(255, 0, 255)

#define TILE_SIZE				70.0f

#define PLAYER_MOVE_SPEED		7.0f
#define PLAYER_ANI_FRAME_SEC	8.0f			
#define WEAPON_ANI_FRAME_SEC	8.0f
#define TOOL_ANI_FRAME_SEC 		8.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	PLAYER_WIDTH * 0.8
#define PLAYER_HAIR_HEIGHT	PLAYER_HEIGHT * 0.8
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f
#define PLAYER_POWER	10
#define PLAYER_MOENY	2700

#define ROCK_WIDTH		TILE_SIZE
#define ROCK_HEIGHT		TILE_SIZE

#define ROCK_IMG_WIDTH		(ROCK_WIDTH * 0.8)
#define ROCK_IMG_HEIGHT		(ROCK_HEIGHT * 0.9)

#define TREE_IMG_WIDTH		TILE_SIZE * 3.0f
#define TREE_IMG_HEIGHT		TILE_SIZE * 6.0f

#define MAX_TOOLBAR_INDEX		12
#define INVENTORY_SIZE			36

#define TOOLBAR_WIDTH			800.0f
#define TOOLBAR_HEIGHT			96.0f
#define TOOLBAR_BORDER_H		16.0f
#define TOOLBAR_BORDER_W		16.0f

#define ACCESS_MENU_WIDTH			WINSIZE_X * 0.4
#define ACCESS_MENU_HEIGHT			WINSIZE_Y * 0.5

#define INVENTORY_BOX_WIDTH		64.0f

#define WEAPON_SIZE_WIDTH  TILE_SIZE * 1.0f
#define WEAPON_SIZE_HEIGHT TILE_SIZE * 1.0f

#define ITEM_SIZE_WIDTH  TILE_SIZE * 1.0f
#define ITEM_SIZE_HEIGHT TILE_SIZE * 1.0f

#define WEAPON_IMG_SIZE_WIDTH  TILE_SIZE
#define WEAPON_IMG_SIZE_HEIGHT TILE_SIZE

#define MAP_FILE_PATH			"Resources/Map/"

#define MAX_OBJECT_COUNT		20

#define CR_RED					 Gdiplus::Color(255, 0, 0)
#define CR_A_RED				 Gdiplus::Color(50, 255, 0, 0)
#define CR_BLUE					 Gdiplus::Color(0, 0, 255)
#define CR_A_BLUE				 Gdiplus::Color(50, 0, 0, 255)
#define CR_WHITE				 Gdiplus::Color(255, 255, 255)
#define CR_YELLOW				 Gdiplus::Color(0, 255, 255)
#define CR_A_YELLOW				 Gdiplus::Color(100, 0, 255, 255)
#define CR_NONE					 Gdiplus::Color(0, 0, 0,0)
