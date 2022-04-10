#pragma once
enum TERRAIN //지형
{
	TR_NULL,
	TR_NORMAL,		//노말 지형
	TR_GRASS,		//풀 지형
	TR_WOOD,		//나무 지형
	TR_SAND,		//모래 지형
	TR_SNOW,		//눈 지형
	TR_WATER,		//물 지형
	TR_STONE,		//돌 지형
	TR_CRYSTAL,		//유리 지형
	TR_BRICK		//벽돌 지형
};

enum OBJECT
{
	OBJ_NULL,
	OBJ_NORMAL,
	OBJ_WALL,
	OBJ_OBJECT,
	OBJ_TRAIN,
	OBJ_LIGHT,
	OBJ_DOOR,
	OBJ_FENCE,
	OBJ_ROCK,
	OBJ_NPC,
	OBJ_MINE_LADDER,
	OBJ_TREE,
	OBJ_TREE_ATTACK,
	OBJ_FLOWER,
	OBJ_BUILDING,
};

enum SUB_OBJECT {
	SOBJ_MONSTER,
	SOBJ_ROCK,
	SOBJ_NPC,
};

typedef struct tagTile
{
	int Index;

	TERRAIN Terrain;
	OBJECT Object;
	OBJECT SubObject;

	int TerrainFrameX;
	int TerrainFrameY;

	int ObjectFrameX;
	int ObjectFrameY;

	int SubObjectFrameX;
	int SubObjectFrameY;

	int X;
	int Y;

	bool IsOverrayTerrain;
	bool IsOverrayObject;

	bool IsInit;
	bool IsCanMove;

	tagTile(TERRAIN terrain, int terrainFrameX, int terrainFrameY, bool isCanMove = true) {
		IsInit = true;
		
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;

		Terrain = terrain;
		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;

		IsOverrayTerrain = false;
		IsOverrayObject = false;

		IsCanMove = isCanMove;
	};

	tagTile(OBJECT object, int objectFrameX, int objectFrameY, bool isCanMove = false, bool isOverrayTerrain = false, bool isOverrayObject = false) {
		IsInit = true;
		Terrain = TR_NULL;

		IsOverrayTerrain = isOverrayTerrain;
		IsOverrayObject = isOverrayObject;

		Object = object;
		ObjectFrameX = objectFrameX;
		ObjectFrameY = objectFrameY;
		
		IsCanMove = isCanMove;
	};

	void toString() {

		LOG::d("=====================================");
		switch (Terrain)
		{
		case TR_NULL:
			LOG::d("T : NULL");
			break;
		case TR_WATER:
			LOG::d("T : TR_WATER");
			break;
		case TR_GRASS:
			LOG::d("T : TR_GRASS");
			break;
		case TR_NORMAL:
			LOG::d("T : NORMAL");
			break;
		case TR_SAND:
			LOG::d("T : SAND");
		case TR_SNOW:
			LOG::d("T : TR_SNOW");
			break;
		case TR_BRICK:
			LOG::d("T : TR_SNOW");
			break;
		case TR_STONE:
			LOG::d("T : TR_STONE");
			break;
		default:
			LOG::d("T : ELSE");
			break;
		}
		switch (Object)
		{
		case OBJ_NULL:
			LOG::d("OBJ : NULL");
			break;
		case OBJ_NORMAL:
			LOG::d("OBJ : NORMAL");
			break;
		case OBJ_TREE:
			LOG::d("OBJ : OBJ_TREE");
			break;
		case OBJ_TREE_ATTACK:
			LOG::d("OBJ : OBJ_TREE_ATTACK");
			break;
		case OBJ_WALL:
			LOG::d("OBJ : OBJ_WALL");
			break;
		case OBJ_DOOR:
			LOG::d("OBJ : DOOR");
			break;
		default:
			LOG::d("OBJ : ELSE");
			break;
		}
		switch (SubObject)
		{
		case OBJ_NULL:
			LOG::d("SUBOBJ : NULL");
			break;
		case OBJ_ROCK:
			LOG::d("SUBOBJ : ROCK");
			break;
		case OBJ_MONSTER:
			LOG::d("SUBOBJ : MONSTER");
			break;
		default:
			LOG::d("SUBOBJ : ELSE");
			break;
		}

		LOG::d("INT Terrain X : " + to_string(TerrainFrameX));
		LOG::d("INT Terrain Y : " + to_string(TerrainFrameY));

		LOG::d("INT Object X : " + to_string(ObjectFrameX));
		LOG::d("INT Object Y : " + to_string(ObjectFrameY));


		if (IsCanMove) {
		LOG::d("IS CAN MOVE : TRUE");
		
		}
		else {
		LOG::d("IS CAN MOVE : false");

		}
		LOG::d(IsOverrayTerrain ? "IS OVERRAY TERRAIN :  true" : "IS OVERRAY TERRAIN :  False");

		LOG::d("INDEX : " + to_string(Index));
	}

	tagTile(int index) {
		IsInit = false;

		Index = index;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;
	};

	tagTile() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;
	};
} Tile;