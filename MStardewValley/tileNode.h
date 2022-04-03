#pragma once
enum TERRAIN //ÁöÇü
{
	TR_NULL,
	TR_NORMAL,
	TR_GRASS,
	TR_WOOD,
	TR_SAND,
	TR_SNOW,
	TR_WATER
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

	tagTile(TERRAIN terrain, int index, int terrainFrameX, int terrainFrameY) {
		IsInit = true;
		
		Terrain = terrain;
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;

		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;

		Index = index;

		IsOverrayTerrain = false;
		IsOverrayObject = false;
	};

	tagTile(OBJECT object, int index, int objectFrameX, int objectFrameY, bool isOverrayTerrain = false, bool isOverrayObject = false) {
		IsInit = true;
		Terrain = TR_NULL;

		IsOverrayTerrain = isOverrayTerrain;
		IsOverrayObject = isOverrayObject;

		if (isOverrayObject) {
			SubObject = object;
			SubObjectFrameX = objectFrameX;
			SubObjectFrameY = objectFrameY;
			Object = OBJ_NULL;
		}
		else {
			Object = object;
			ObjectFrameX = objectFrameX;
			ObjectFrameY = objectFrameY;
			SubObject = OBJ_NULL;
		}
	};


	void toString() {

		LOG::d("=====================================");
		switch (Terrain)
		{
		case TR_NULL:
			LOG::d("T : NULL");
			break;
		case TR_NORMAL:
			LOG::d("T : NORMAL");
			break;
		case TR_SAND:
			LOG::d("T : SAND");
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
		default:
			LOG::d("OBJ : ELSE");
			break;
		}
		switch (SubObject)
		{
		case OBJ_NULL:
			LOG::d("SUBOBJ : NULL");
			break;
		case TR_NORMAL:
			LOG::d("SUBOBJ : NORMAL");
			break;
		default:
			LOG::d("SUBOBJ : ELSE");
			break;
		}

		LOG::d("INT Terrain X : " + to_string(TerrainFrameX));
		LOG::d("INT Terrain Y : " + to_string(TerrainFrameY));

		LOG::d("INT Object X : " + to_string(ObjectFrameX));
		LOG::d("INT Object Y : " + to_string(ObjectFrameY));

		LOG::d("INT X : " + to_string(X));
		LOG::d("INT Y : " + to_string(Y));

	}

	tagTile() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;
	};
} Tile;