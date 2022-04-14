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
	TR_BRICK,		//벽돌 지형
	TR_END,
};

enum OBJECT
{
	OBJ_NULL,
	OBJ_OBJECT,
	OBJ_WALL,
	OBJ_FENCE,
	OBJ_TRAIN,
	OBJ_MINE_DOOR,
	OBJ_MINE_LADDER,
	OBJ_TREE,
	OBJ_TREE_ATTACK,
	OBJ_BUSH,
	OBJ_FLOWER,
	OBJ_BUILDING,
	OBJ_BUILDING_DOOR,
	OBJ_SALE_STAND,
	OBJ_WINDOW,
	OBJ_END
};

enum SUB_OBJECT {
	SOBJ_NULL,
	SOBJ_MONSTER,
	SOBJ_ROCK,
	SOBJ_NPC,
	SOBJ_HOED,
	SOBJ_HOED_WET,
	SOBJ_SEED,
	SOBJ_END,
};
typedef struct tagTileOriginal
{
	int Index;

	TERRAIN Terrain;
	OBJECT Object;
	SUB_OBJECT SubObject;

	int TerrainFrameX;
	int TerrainFrameY;

	int ObjectFrameX;
	int ObjectFrameY;
	bool IsOverrayTerrain;

	int SubObjectFrameX;
	int SubObjectFrameY;

	int X;
	int Y;

	bool IsInit;
	bool IsCanMove;

	tagTileOriginal(TERRAIN terrain, int terrainFrameX, int terrainFrameY, bool isCanMove = true) {
		IsInit = true;

		Object = OBJ_NULL;
		SubObject = SOBJ_NULL;

		Terrain = terrain;
		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;

		IsOverrayTerrain = false;
		IsCanMove = true;
	};

	tagTileOriginal(OBJECT object, int objectFrameX, int objectFrameY, bool isCanMove = false, bool isOverrayTerrain = false, bool isOverrayObject = false) {
		IsInit = true;

		Object = object;
		ObjectFrameX = objectFrameX;
		ObjectFrameY = objectFrameY;

		Terrain = TR_NULL;
		SubObject = SOBJ_NULL;

		IsOverrayTerrain = false;
		IsCanMove = false;
	};

	tagTileOriginal(int index) {
		IsInit = false;

		Index = index;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = SOBJ_NULL;
	};

	tagTileOriginal() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = SOBJ_NULL;
	};

	void toString() {

		LOG::d("=====================================");
		switch (Terrain)
		{
		case TR_NULL:
			LOG::d("T : NULL");
			break;
		case TR_NORMAL:
			LOG::d("T : TR_NORMAL");
			break;
		case TR_GRASS:
			LOG::d("T : TR_GRASS");
			break;
		case TR_WOOD:
			LOG::d("T : TR_WOOD");
			break;
		case TR_SAND:
			LOG::d("T : TR_SAND");
			break;
		case TR_WATER:
			LOG::d("T : TR_WATER");
			break;
		case TR_SNOW:
			LOG::d("T : TR_SNOW");
			break;
		case TR_CRYSTAL:
			LOG::d("T : TR_CRYSTAL");
			break;
		case TR_BRICK:
			LOG::d("T : TR_BRICK");
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
		case OBJ_OBJECT:
			LOG::d("OBJ : OBJ_OBJECT");
			break;
		case OBJ_WALL:
			LOG::d("OBJ : OBJ_WALL");
			break;
		case OBJ_TRAIN:
			LOG::d("OBJ : OBJ_TRAIN");
			break;
		case OBJ_MINE_DOOR:
			LOG::d("OBJ : OBJ_MINE_DOOR");
			break;
		case OBJ_MINE_LADDER:
			LOG::d("OBJ : OBJ_MINE_LADDER");
			break;
		case OBJ_TREE:
			LOG::d("OBJ : OBJ_TREE");
			break;
		case OBJ_BUSH:
			LOG::d("OBJ : OBJ_BUSH");
			break;
		case OBJ_FLOWER:
			LOG::d("OBJ : OBJ_FLOWER");
			break;
		case OBJ_TREE_ATTACK:
			LOG::d("OBJ : OBJ_TREE_ATTACK");
			break;
		case OBJ_BUILDING:
			LOG::d("OBJ : OBJ_BUILDING");
			break;
		case OBJ_BUILDING_DOOR:
			LOG::d("OBJ : OBJ_BUILDING_DOOR");
			break;
		default:
			LOG::d("OBJ : ELSE");
			break;
		}

		LOG::d("INT Terrain X : " + to_string(TerrainFrameX));
		LOG::d("INT Terrain Y : " + to_string(TerrainFrameY));

		LOG::d("INT Object X : " + to_string(ObjectFrameX));
		LOG::d("INT Object Y : " + to_string(ObjectFrameY));

		LOG::d(IsCanMove ? "IS CAN MOVE : TRUE" : "IS CAN MOVE : FALSE");
		LOG::d(IsOverrayTerrain ? "IS OVERRAY TERRAIN :  true" : "IS OVERRAY TERRAIN :  False");

		LOG::d("INDEX : " + to_string(Index));
	}

} TileOriginal;
typedef struct tagTile
{
	int Index;

	TERRAIN Terrain;
	OBJECT Object;
	SUB_OBJECT SubObject;

	int TerrainFrameX;
	int TerrainFrameY;

	int ObjectFrameX;
	int ObjectFrameY;
	bool IsOverrayTerrain;

	int SubObjectFrameX;
	int SubObjectFrameY;

	int X;
	int Y;

	bool IsInit;
	bool IsCanMove;

	OBJECT Object2;
	
	int Object2FrameX;
	int Object2FrameY;

	bool IsOverrayObject;

	tagTile(TERRAIN terrain, int terrainFrameX, int terrainFrameY, bool isCanMove = true) {
		IsInit = true;
		
		Object = OBJ_NULL;
		SubObject = SOBJ_NULL;
		Object2 = OBJ_NULL;

		Terrain = terrain;
		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;

		ObjectFrameX = -1;
		ObjectFrameY = -1;

		Object2FrameX = -1;
		Object2FrameY = -1;

		IsOverrayTerrain = false;
		IsOverrayObject = false;

		IsCanMove = isCanMove;
	};

	tagTile(OBJECT object, int objectFrameX, int objectFrameY, bool isCanMove = false, bool isOverrayTerrain = false, bool isOverrayObject = false) {
		IsInit = true;

		Object = object;
		ObjectFrameX = objectFrameX;
		ObjectFrameY = objectFrameY;

		Terrain = TR_NULL;
		Object2 = OBJ_NULL;
		SubObject = SOBJ_NULL;

		Object2FrameX = -1;
		Object2FrameY = -1;

		TerrainFrameX = -1;
		TerrainFrameY = -1;
		
		IsOverrayTerrain = isOverrayTerrain;
		IsOverrayObject = false;
		IsCanMove = false;
	};

	tagTile(int index) {
		IsInit = false;

		Index = index;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		Object2 = OBJ_NULL;
		SubObject = SOBJ_NULL;
	};

	tagTile() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		Object2 = OBJ_NULL;
		SubObject = SOBJ_NULL;
	};

	void save(TileOriginal& tile) {
		IsInit = tile.IsInit;

		Index = -1;

		Terrain = tile.Terrain;
		Object = tile.Object;
		Object2 = OBJ_NULL;


		TerrainFrameX = tile.TerrainFrameX;
		TerrainFrameY = tile.TerrainFrameY;

		ObjectFrameX = tile.ObjectFrameX;
		ObjectFrameY = tile.ObjectFrameY;

		if (Terrain == TR_NULL) {
			TerrainFrameX = -1;
			TerrainFrameY = -1;
		}
		if(Object == OBJ_NULL) {
			ObjectFrameX = -1;
			ObjectFrameY = -1;
		}

		Object2FrameX = -1;
		Object2FrameY = -1;

		SubObjectFrameX = tile.SubObjectFrameX;
		SubObjectFrameY = tile.SubObjectFrameY;

		X = tile.X;
		Y = tile.Y;

		IsCanMove = tile.IsCanMove;
		IsOverrayTerrain = tile.IsOverrayTerrain;
		IsOverrayObject = false;
	};

	void toString() {

		LOG::d("=====================================");
		switch (Terrain)
		{
		case TR_NULL:
			LOG::d("T : NULL");
			break;
		case TR_NORMAL:
			LOG::d("T : TR_NORMAL");
			break;
		case TR_GRASS:
			LOG::d("T : TR_GRASS");
			break;
		case TR_WOOD:
			LOG::d("T : TR_WOOD");
			break;
		case TR_SAND:
			LOG::d("T : TR_SAND");
			break;
		case TR_WATER:
			LOG::d("T : TR_WATER");
			break;
		case TR_SNOW:
			LOG::d("T : TR_SNOW");
			break;
		case TR_CRYSTAL:
			LOG::d("T : TR_CRYSTAL");
			break;
		case TR_BRICK:
			LOG::d("T : TR_BRICK");
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
		case OBJ_OBJECT:
			LOG::d("OBJ : OBJ_OBJECT");
			break;
		case OBJ_WALL:
			LOG::d("OBJ : OBJ_WALL");
			break;
		case OBJ_TRAIN:
			LOG::d("OBJ : OBJ_TRAIN");
			break;
		case OBJ_MINE_DOOR:
			LOG::d("OBJ : OBJ_MINE_DOOR");
			break;
		case OBJ_MINE_LADDER:
			LOG::d("OBJ : OBJ_MINE_LADDER");
			break;
		case OBJ_TREE:
			LOG::d("OBJ : OBJ_TREE");
			break;
		case OBJ_BUSH:
			LOG::d("OBJ : OBJ_BUSH");
			break;
		case OBJ_FLOWER:
			LOG::d("OBJ : OBJ_FLOWER");
			break;
		case OBJ_TREE_ATTACK:
			LOG::d("OBJ : OBJ_TREE_ATTACK");
			break;
		case OBJ_BUILDING:
			LOG::d("OBJ : OBJ_BUILDING");
			break;
		case OBJ_BUILDING_DOOR:
			LOG::d("OBJ : OBJ_BUILDING_DOOR");
			break;
		default:
			LOG::d("OBJ : ELSE");
			break;
		}
		switch (Object2)
		{
		case OBJ_NULL:
			LOG::d("OBJ2 : NULL");
			break;
		case OBJ_OBJECT:
			LOG::d("OBJ2 : OBJ_OBJECT");
			break;
		case OBJ_WALL:
			LOG::d("OBJ2 : OBJ_WALL");
			break;
		case OBJ_WINDOW:
			LOG::d("OBJ2 : OBJ_WINDOW");
			break;
		case OBJ_MINE_DOOR:
			LOG::d("OBJ2 : OBJ_MINE_DOOR");
			break;
		case OBJ_MINE_LADDER:
			LOG::d("OBJ2 : OBJ_MINE_LADDER");
			break;
		case OBJ_TREE:
			LOG::d("OBJ2 : OBJ_TREE");
			break;
		case OBJ_BUSH:
			LOG::d("OBJ2 : OBJ_BUSH");
			break;
		case OBJ_FLOWER:
			LOG::d("OBJ2 : OBJ_FLOWER");
			break;
		case OBJ_TREE_ATTACK:
			LOG::d("OBJ2 : OBJ_TREE_ATTACK");
			break;
		case OBJ_BUILDING:
			LOG::d("OBJ2 : OBJ_BUILDING");
			break;
		case OBJ_BUILDING_DOOR:
			LOG::d("OBJ2 : OBJ_BUILDING_DOOR");
			break;
		default:
			LOG::d("OBJ2 : ELSE");
			break;
		}

		LOG::d("INT Terrain X : " + to_string(TerrainFrameX));
		LOG::d("INT Terrain Y : " + to_string(TerrainFrameY));

		LOG::d("INT Object X : " + to_string(ObjectFrameX));
		LOG::d("INT Object Y : " + to_string(ObjectFrameY));

		LOG::d("INT Object2 X : " + to_string(Object2FrameX));
		LOG::d("INT Object2 Y : " + to_string(Object2FrameY));

		LOG::d(IsCanMove ? "IS CAN MOVE : TRUE" : "IS CAN MOVE : FALSE");
		LOG::d(IsOverrayTerrain ? "IS OVERRAY TERRAIN :  true" : "IS OVERRAY TERRAIN :  False");

		LOG::d("INDEX : " + to_string(Index));
	}

} Tile;

