#pragma once
#define OBJ_C		3	

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
	OBJ_BED,
	OBJ_TV,
	OBJ_FURNITURE,
	OBJ_HOED,
	OBJ_HOED_WET,
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
	SOBJ_PORTAL,
	SOBJ_TREE_ATTACK,
	SOBJ_END,
};

typedef struct tagTileDef
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
	tagTileDef() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
	};
	void toString() {
		LOG::d("=====================================");
		string terrain = "";
		string object = "";

		switch (Terrain)
		{
		case TR_NULL:		terrain = "TR_NULL";	break;
		case TR_NORMAL:		terrain = "TR_NORMAL";	break;
		case TR_GRASS:		terrain = "TR_GRASS";	break;
		case TR_WOOD:		terrain = "TR_WOOD";	break;
		case TR_SAND:		terrain = "TR_SAND";	break;
		case TR_WATER:		terrain = "TR_WATER";	break;
		case TR_SNOW:		terrain = "TR_SNOW";	break;
		case TR_CRYSTAL:	terrain = "TR_CRYSTAL";	break;
		case TR_BRICK:		terrain = "TR_BRICK";	break;
		default:			terrain = "TR_ELSE";	break;
		}

		LOG::d("Terrain : " + terrain);
		LOG::d("Terrain X : " + to_string(TerrainFrameX));
		LOG::d("Terrain Y : " + to_string(TerrainFrameY));

		switch (Object)
		{
		case OBJ_NULL:				object = "OBJ_NULL";			break;
		case OBJ_OBJECT:			object = "OBJ_OBJECT";			break;
		case OBJ_WALL:				object = "OBJ_WALL";			break;
		case OBJ_TRAIN:				object = "OBJ_TRAIN";			break;
		case OBJ_MINE_DOOR:			object = "OBJ_MINE_DOOR";		break;
		case OBJ_MINE_LADDER:		object = "OBJ_MINE_LADDER";		break;
		case OBJ_TREE:				object = "OBJ_TREE";			break;
		case OBJ_BUSH:				object = "OBJ_BUSH";			break;
		case OBJ_FLOWER:			object = "OBJ_FLOWER";			break;
		case OBJ_TREE_ATTACK:		object = "OBJ_TREE_ATTACK";		break;
		case OBJ_BUILDING:			object = "OBJ_BUILDING";		break;
		case OBJ_BUILDING_DOOR:		object = "OBJ_BUILDING_DOOR";	break;
		case OBJ_BED:				object = "OBJ_BED";				break;
		default:					object = "OBJ_ELSE";			break;
		}
		LOG::d("Object : " + object);
		LOG::d("ObjectXFrameX : " + to_string(ObjectFrameX));
		LOG::d("ObjectYFrameY : " + to_string(ObjectFrameY));

		LOG::d(IsCanMove ? "IsCanMove : TRUE" : "IsCanMove : FALSE");
		LOG::d(IsOverrayTerrain ? "IsTransparency :  true" : "IsTransparency:  false");
		LOG::d("=====================================");
	}


	TERRAIN getTerrainByStr(string terrainStr) {
		TERRAIN terrain = TR_NULL;
		if (terrainStr == "normal")	terrain = TR_NORMAL;
		else if (terrainStr == "grass")	terrain = TR_GRASS;
		else if (terrainStr == "wood")	terrain = TR_WOOD;
		else if (terrainStr == "sand")	terrain = TR_SAND;
		else if (terrainStr == "water")	terrain = TR_WATER;
		else if (terrainStr == "snow")	terrain = TR_SNOW;
		else if (terrainStr == "crystal")	terrain = TR_CRYSTAL;
		else if (terrainStr == "stone")	terrain = TR_STONE;
		return terrain;
	}

	OBJECT getObjectByStr(string objStr) {
		OBJECT object = OBJ_NULL;
		if (objStr == "obj")				object = OBJ_OBJECT;		
		else if (objStr == "wall")			object = OBJ_WALL;
		else if (objStr == "fence")			object = OBJ_FENCE;
		else if (objStr == "train")			object = OBJ_TRAIN;
		else if (objStr == "mine_door")		object = OBJ_MINE_DOOR;
		else if (objStr == "mine_ladder")	object = OBJ_MINE_LADDER;
		else if (objStr == "tree")			object = OBJ_TREE;
		else if (objStr == "tree_a")		object = OBJ_TREE_ATTACK;
		else if (objStr == "bush")			object = OBJ_BUSH;
		else if (objStr == "flower")		object = OBJ_FLOWER;
		else if (objStr == "building")		object = OBJ_BUILDING;
		else if (objStr == "building_door")	object = OBJ_BUILDING_DOOR;
		else if (objStr == "sale_stand")	object = OBJ_SALE_STAND;
		else if (objStr == "window")		object = OBJ_WINDOW;
		else if (objStr == "bed")			object = OBJ_BED;
		else if (objStr == "tv")			object = OBJ_TV;
		else if (objStr == "furniture")		object = OBJ_FURNITURE;
		return object;
	}

} TileDef;

typedef struct tagTile
{
	TERRAIN Terrain;
	OBJECT Object[OBJ_C];
	SUB_OBJECT SubObject[OBJ_C];

	int TerrainFrameX;
	int TerrainFrameY;

	int ObjectFrameX[OBJ_C];
	int ObjectFrameY[OBJ_C];
	int ObjectLevel[OBJ_C];

	int SubObjectFrameX[OBJ_C];
	int SubObjectFrameY[OBJ_C];
	int SubObjectLevel[OBJ_C];

	bool IsCanMove;
	bool IsTransparency;
	
	bool IsInit;

	void toString() {
		LOG::d("=====================================");
		string terrain = "";
		string object = "";
		string sobject = "";

		switch (Terrain)
		{
		case TR_NULL:		terrain = "TR_NULL";	break;
		case TR_NORMAL:		terrain = "TR_NORMAL";	break;
		case TR_GRASS:		terrain = "TR_GRASS";	break;
		case TR_WOOD:		terrain = "TR_WOOD";	break;
		case TR_SAND:		terrain = "TR_SAND";	break;
		case TR_WATER:		terrain = "TR_WATER";	break;
		case TR_SNOW:		terrain = "TR_SNOW";	break;
		case TR_CRYSTAL:	terrain = "TR_CRYSTAL";	break;
		case TR_BRICK:		terrain = "TR_BRICK";	break;
		default:			terrain = "TR_ELSE";	break;
		}

		LOG::d("Terrain : " + terrain);
		LOG::d("Terrain X : " + to_string(TerrainFrameX));
		LOG::d("Terrain Y : " + to_string(TerrainFrameY));

		for (int i = 0; i < OBJ_C; i++) {
			switch (Object[i])
			{
			case OBJ_NULL:				object = "OBJ_NULL";			break;
			case OBJ_OBJECT:			object = "OBJ_OBJECT";			break;
			case OBJ_WALL:				object = "OBJ_WALL";			break;
			case OBJ_TRAIN:				object = "OBJ_TRAIN";			break;
			case OBJ_MINE_DOOR:			object = "OBJ_MINE_DOOR";		break;
			case OBJ_MINE_LADDER:		object = "OBJ_MINE_LADDER";		break;
			case OBJ_TREE:				object = "OBJ_TREE";			break;
			case OBJ_BUSH:				object = "OBJ_BUSH";			break;
			case OBJ_FLOWER:			object = "OBJ_FLOWER";			break;
			case OBJ_TREE_ATTACK:		object = "OBJ_TREE_ATTACK";		break;
			case OBJ_BUILDING:			object = "OBJ_BUILDING";		break;
			case OBJ_BUILDING_DOOR:		object = "OBJ_BUILDING_DOOR";	break;
			case OBJ_BED:				object = "OBJ_BED";				break;
			default:					object = "OBJ_ELSE";			break;
			}
			LOG::d("Object[" + to_string(i) + "] : " + object);
			LOG::d("ObjectXFrame[" + to_string(i) + "] X : " + to_string(ObjectFrameX[i]));
			LOG::d("ObjectYFrame[" + to_string(i) + "] Y : " + to_string(ObjectFrameY[i]));
			LOG::d("ObjectLevel[" + to_string(i) + "] : " + to_string(ObjectLevel[i]));

			switch (SubObject[i])
			{
			case SOBJ_NULL:				sobject = "SOBJ_NULL";			break;
			case SOBJ_TREE_ATTACK:		sobject = "SOBJ_TREE_ATTACK";	break;
			case SOBJ_MONSTER:			sobject = "SOBJ_MONSTER";		break;
			default:					sobject = "SOBJ_ELSE";			break;
			}
			LOG::d("SObject[" + to_string(i) + "] : " + sobject);
			LOG::d("SObjectXFrame[" + to_string(i) + "] X : " + to_string(SubObjectFrameX[i]));
			LOG::d("SObjectYFrame[" + to_string(i) + "] Y : " + to_string(SubObjectFrameY[i]));
			LOG::d("SObjectLevel[" + to_string(i) + "] : " + to_string(SubObjectLevel[i]));
		}

		LOG::d(IsCanMove ? "IsCanMove : true" : "IsCanMove : false");
		LOG::d(IsTransparency ? "IsTransparency :  true" : "IsTransparency:  false");
		LOG::d("=====================================");
	}

	void clear() {
		Terrain = TR_NULL;
		TerrainFrameX = -1;
		TerrainFrameY = -1;
		for (int i = 0; i < OBJ_C; i++) {
			Object[i] = OBJ_NULL;
			IsInit = false;
			ObjectFrameX[i] = -1;
			ObjectFrameY[i] = -1;
			ObjectLevel[i] = -1;
		}

		IsCanMove = false;
		IsTransparency = false;
	}

	TERRAIN getTerrainByStr(const char* terrainStr) {
		TERRAIN terrain = TR_NULL;
		if(terrainStr == "normal")	terrain = TR_NORMAL;
		else if(terrainStr == "grass")	terrain = TR_GRASS;
		else if(terrainStr == "wood")	terrain = TR_WOOD;
		else if(terrainStr == "sand")	terrain = TR_SAND;
		else if(terrainStr == "water")	terrain = TR_WATER;
		else if(terrainStr == "snow")	terrain = TR_SNOW;
		else if(terrainStr == "crystal")	terrain = TR_CRYSTAL;
		return terrain;
	}

	OBJECT getObjectByStr(const char* objStr) {
		OBJECT object = OBJ_NULL;
		if (objStr == "obj")				object = OBJ_OBJECT;
		else if (objStr == "wall")			object = OBJ_WALL;
		else if (objStr == "fence")			object = OBJ_FENCE;
		else if (objStr == "train")			object = OBJ_TRAIN;
		else if (objStr == "mine_door")		object = OBJ_MINE_DOOR;
		else if (objStr == "mine_ladder")	object = OBJ_MINE_LADDER;
		else if (objStr == "tree")			object = OBJ_TREE;
		else if (objStr == "tree_a")		object = OBJ_TREE_ATTACK;
		else if (objStr == "bush")			object = OBJ_BUSH;
		else if (objStr == "flower")		object = OBJ_FLOWER;
		else if (objStr == "building")		object = OBJ_BUILDING;
		else if (objStr == "building_door")	object = OBJ_BUILDING_DOOR;
		else if (objStr == "sale_stand")	object = OBJ_SALE_STAND;
		else if (objStr == "window")		object = OBJ_WINDOW;
		else if (objStr == "bed")			object = OBJ_BED;
		else if (objStr == "tv")			object = OBJ_TV;
		else if (objStr == "furniture")		object = OBJ_FURNITURE;
		return object;
	}

} TILE;

typedef struct tagObjectTile
{
	OBJECT Object;
	int GroupId;
	int Level;
	vector<TINDEX> IndexList;

	tagObjectTile(): Object(OBJ_NULL), GroupId(-1), Level(-1) {
	}
	
} OBJTILE;