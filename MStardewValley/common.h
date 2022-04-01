#pragma once

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
	PS_END
};

enum eToolType {
	TT_PICK, //°î±ªÀÌ
	TT_AXE, //µµ³¢
	TT_WATERING_CAN, //¹°»Ñ¸®°Ô
	TT_HOE, //´ÙÁö´Â°Å
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

enum eImgResult {
	IR_SUCCESS,
	IR_FAIL,
	IR_SIZE_DIFF
};

#define GAME_FONT				L"Leferi Base Type Bold"
#define TRANCECOLOR				RGB(255, 0, 255)

#define PLAYER_MOVE_SPEED		2.0f			

#define TILE_SIZE		70.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	50.0f
#define PLAYER_HAIR_HEIGHT	100.0f
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f