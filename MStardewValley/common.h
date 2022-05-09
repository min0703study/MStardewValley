#pragma once

#define DEBUG_MODE				true
#define SOUND_MODE				true

enum eMapToolCtrl {
	MC_ERASER,
	MC_DRAW,
	MC_COLLISION_TILE,
	MC_MOVABLE_TILE,
	MC_OBJECT_GROUP,
	MC_END
};

enum eFuranceStat {
	FS_NONE,
	FS_SMELTING,
	FS_SMELTING_OVER,
	FS_END
};

enum eCraftablesType {
	CBT_FURNACE,
	CBT_BOX,
	CBT_END
};

enum eRefiningEquipmentType {
	RET_FURANCE,
	RET_END
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

enum eEffectAniType {
	EAT_WEED_CRUSH,
	EAT_ROCK_CRUSH,
	EAT_STUMP_CRUSH,
	EAT_USE_WATERING_CAN,
	EAT_FURANCE_SMELTING,
	EAT_END,
};

enum class eUIEventStat
{
	ES_CLICK_DOWN,
	ES_CLICK_UP,
	ES_DRAG,
	ES_MOUSE_OVER,
	ES_MOUSE_OFF
};

enum eEffectSoundType {
	EST_WALK_WOOD,
	EST_WALK_NORMAL,
	EST_WALK_GRASS,
	EST_WALK_STONE,
	EST_ATTACK_ROCK,
	EST_ATTACK_TREE,
	EST_ATTACK_WEED,
	EST_USE_HOE,
	EST_USE_WEAPON,
	EST_USE_WATERING_CAN,
	EST_PICKUP_ITEM,
	EST_DOOR_OPEN,
	EST_MONSTER_DEAD,
	EST_PLAYER_HIT,
	EST_HARVESTING,
	EST_LADDER_DOWN,
	EST_FURNACE,
	EST_END,
};

enum eGameDirection {
	GD_UP,
	GD_RIGHT,
	GD_LEFT,
	GD_DOWN,
	GD_END
};

enum eUIDirection {
	UI_UP,
	UI_RIGHT,
	UI_LEFT,
	UI_DOWN,
	UI_END
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
	PAS_EAT_FOOD,
	PAS_GIVE_ITEM,
	PAS_END,
};

enum ePlayerStat {
	PS_IDLE,
	PS_WALK,
	PS_ATTACK,
	PS_GRAP,
	PS_HIT,
	PS_END,
};

enum eHoedStat {
	HS_NORMAL,
	HS_WET,
	HS_END,
};

//item
enum eItemType {
	ITP_TOOL,
	ITP_WEAPON,
	ITP_SEED,
	ITP_FRUIT,
	ITP_ORE,
	ITP_FORAGE,
	ITP_CRAFTING,
	ITP_ORE_BAR,
	ITP_END
};

enum eItemStat {
	IS_IDLE,
	IS_GRAP,
	IS_USE,
	IS_DROP,
	IS_END,
};

enum eToolType {
	TT_PICK,
	TT_AXE,
	TT_WATERING_CAN,
	TT_HOE,
	TT_END
};

enum eToolLevel {
	TL_NORMAL,
	TL_COPPER,
	TL_IRON,
	TL_GOLD,
	TL_IRIDIUM,
	TL_END
};

enum eWeaponType {
	WT_NORMAL,
	WT_WOODEN_BLADE,
	WT_IRON_DIRCT,
	WT_PIRATES_SWORD,
	WT_WOOD_MALLET,
	WT_BONE_SWORD,
	WT_INSECT_HEAD,
	WT_SICKLE,
	WT_END
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
	SPT_CLINT_SHOP,
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

enum eTreeAniStat {
	TAS_IDLE,
	TAS_TRANS,
	TAS_HIT,
	TAS_CRASH,
	TAS_STUMP_IDLE,
	TAS_STUMP_CRASH,
	TAS_STUMP_HIT,
	TAS_END,
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

enum eOreType {
	OT_COPPER,
	OT_IRON,
	OT_GOLD,
	OT_COAL,
	OT_END
};

enum eMinesItem {
	MI_COPPER_BAR,
	MI_IRON_BAR,
	MI_GOLD_BAR,
	MI_END
};

enum eForageType {
	FT_WOOD,
	FT_FIBER,
	FT_STONE,
	FT_END
};

enum eTreeType {
	TTP_NORMAL,
	TTP_NORMAL_1,
	TTP_NORMAL_2,
	TTP_END,
};

enum eWeedType {
	WDT_NORMAL_1,
	WDT_NORMAL_2,
	WDT_NORMAL_3,
	WDT_NORMAL_4,
	WDT_NORMAL_5,
	WDT_END,
};

enum eMonsterType {
	MST_GRUB,
	MST_SLIME,
	MST_END
};

enum eMonsterStat {
	MSS_IDLE,
	MSS_HIT,
	MSS_TO_PLAYER,
	MSS_ATTACK,
	MSS_END
};

enum eMonsterAniStat {
	MAS_IDLE,
	MAS_HIT,
	MAS_END
};

enum eNpcs {
	NPC_PIERRE,
	NPC_MARLON,
	NPC_CLINT,
	NPC_END
};

enum eNpcAniStat {
	NAT_IDLE,
	NAT_END
};

enum eNpcPortraitsType {
	NPT_IDLE,
	NPT_END
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

inline eGameDirection getOppositeDirection(eGameDirection direction) {
	switch (direction)
	{
	case GD_LEFT:
		return GD_RIGHT;
	case GD_RIGHT:
		return GD_LEFT;
	case GD_UP:
		return GD_DOWN;
	case GD_DOWN:
		return GD_UP;
	default:
		//DO NOTHING!
		break;
	}
}

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

	bool operator>(const tagTileIndex& compObject) const {
		if (Y != compObject.Y) {
			return Y > compObject.Y;
		}
		else {
			return X > compObject.X;
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

	//광산
	int Floor;
	int EnterenceIndex;
	string PaletteKey;
	int MonsterCount;
	int RockCount;

	int PortalCount;
} MapTileInfo;

typedef struct tagMapPortal {
	TINDEX TIndex;
	TINDEX StartIndex;

	string ToMapKey;
	string ToSceneName;

	int ToPortal;

	tagMapPortal() : TIndex(TINDEX()), ToMapKey(""), ToSceneName(""), ToPortal(-1) {}
	tagMapPortal(int toPortal) : TIndex(TINDEX()), ToMapKey(""), ToSceneName(""), ToPortal(toPortal) {}
	tagMapPortal(TINDEX tIndex,TINDEX startIndex, string toSceneName, string toMapKey, int toPortal) : TIndex(tIndex),StartIndex(startIndex), ToMapKey(toMapKey), ToSceneName(toSceneName), ToPortal(toPortal) {}
} MapPortal;

#define GAME_FONT				L"Leferi Base Type Bold"
#define GAME_FONT_2				L"SVBold Inner"
#define GAME_FONT_3				L"Sandoll 미생"

#define GAME_FONT_1_S				"Leferi Base Type Bold"
#define GAME_FONT_2_S				"SVBold Inner"
#define GAME_FONT_3_S				"Sandoll 미생"


#define TRANCECOECOLOR				RGB(255, 0, 255)

#define TILE_SIZE				70.0f

#define PLAYER_MOVE_SPEED		6.0f
#define PLAYER_ANI_FRAME_SEC	8.0f			
#define WEAPON_ANI_FRAME_SEC	12.0f
#define TOOL_ANI_FRAME_SEC 		17.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	PLAYER_WIDTH * 0.8
#define PLAYER_HAIR_HEIGHT	PLAYER_HEIGHT * 0.8
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f
#define PLAYER_POWER	10
#define PLAYER_INIT_ENERGY	100
#define PLAYER_INIT_HP		100
#define PLAYER_MOENY	10000

#define ROCK_WIDTH		TILE_SIZE
#define ROCK_HEIGHT		TILE_SIZE

#define ROCK_IMG_WIDTH		(ROCK_WIDTH * 0.8)
#define ROCK_IMG_HEIGHT		(ROCK_HEIGHT * 0.9)


#define TREE_WIDTH		TILE_SIZE * 3.0f
#define TREE_HEIGHT		TILE_SIZE * 6.0f

#define TREE_IMG_WIDTH		TILE_SIZE * 3.0f
#define TREE_IMG_HEIGHT		TILE_SIZE * 6.0f

#define TREE_IMG_TOP_WIDTH		TILE_SIZE * 3.0f
#define TREE_IMG_TOP_HEIGHT		TILE_SIZE * 6.0f

#define TREE_IMG_STUMP_WIDTH		TILE_SIZE
#define TREE_IMG_STUMP_HEIGHT		TILE_SIZE * 2.0f

#define MAX_TOOLBAR_INDEX		12
#define INVENTORY_SIZE			36

#define TOOLBAR_WIDTH			800.0f
#define TOOLBAR_HEIGHT			96.0f
#define TOOLBAR_BORDER_H		16.0f
#define TOOLBAR_BORDER_W		16.0f

#define ACCESS_MENU_WIDTH			845.0f
#define ACCESS_MENU_HEIGHT			576.0f

#define INVENTORY_WIDTH				845.0f
#define INVENTORY_HEIGHT			289.0f

#define RADIO_BTN_WIDTH				64.0f
#define RADIO_BTN_HEIGHT			64.0f

#define INVENTORY_BOX_WIDTH		64.0f

#define WEAPON_SIZE_WIDTH  TILE_SIZE * 1.0f
#define WEAPON_SIZE_HEIGHT TILE_SIZE * 1.0f

#define ITEM_SIZE_WIDTH  TILE_SIZE * 1.0f
#define ITEM_SIZE_HEIGHT TILE_SIZE * 1.0f

#define WEAPON_IMG_SIZE_WIDTH  TILE_SIZE * 1.1f
#define WEAPON_IMG_SIZE_HEIGHT TILE_SIZE * 1.1f

#define MAP_FILE_PATH			"Resources/Map/"

#define MAX_OBJECT_COUNT		20

#define CR_RED					Gdiplus::Color(255, 0, 0)
#define CR_A_RED				Gdiplus::Color(100, 255, 0, 0)
#define CR_BLUE					Gdiplus::Color(0, 0, 255)
#define CR_GREEN				Gdiplus::Color(0, 128, 0)
#define CR_A_BLUE				Gdiplus::Color(100, 0, 0, 255)
#define CR_WHITE				Gdiplus::Color(255, 255, 255)
#define CR_YELLOW				Gdiplus::Color(255, 255, 0)
#define CR_A_YELLOW				Gdiplus::Color(100, 255, 255, 0)
#define CR_A_SALE_CHANGE		Gdiplus::Color(50, 245, 155, 0)
#define CR_NONE					Gdiplus::Color(0, 0, 0, 0)
#define CR_BLACK				Gdiplus::Color(0, 0, 0)
#define CR_DEFULAT				Gdiplus::Color(0, 0, 0)

#define NPC_P_W_SIZE				297.0f
#define NPC_P_H_SIZE				297.0f

#define GAME_REAL_MINUAGTE_SEC		10.0f