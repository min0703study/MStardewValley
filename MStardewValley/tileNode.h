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

		MY_UTIL::log("=====================================");
		switch (Terrain)
		{
		case TR_NULL:
			MY_UTIL::log("T : NULL");
			break;
		case TR_NORMAL:
			MY_UTIL::log("T : NORMAL");
			break;
		case TR_SAND:
			MY_UTIL::log("T : SAND");
			break;
		default:
			MY_UTIL::log("T : ELSE");
			break;
		}
		switch (Object)
		{
		case OBJ_NULL:
			MY_UTIL::log("OBJ : NULL");
			break;
		case OBJ_NORMAL:
			MY_UTIL::log("OBJ : NORMAL");
			break;
		default:
			MY_UTIL::log("OBJ : ELSE");
			break;
		}
		switch (SubObject)
		{
		case OBJ_NULL:
			MY_UTIL::log("SUBOBJ : NULL");
			break;
		case TR_NORMAL:
			MY_UTIL::log("SUBOBJ : NORMAL");
			break;
		default:
			MY_UTIL::log("SUBOBJ : ELSE");
			break;
		}

		MY_UTIL::log("INT Terrain X : " + to_string(TerrainFrameX));
		MY_UTIL::log("INT Terrain Y : " + to_string(TerrainFrameY));

		MY_UTIL::log("INT Object X : " + to_string(ObjectFrameX));
		MY_UTIL::log("INT Object Y : " + to_string(ObjectFrameY));

		MY_UTIL::log("INT X : " + to_string(X));
		MY_UTIL::log("INT Y : " + to_string(Y));

	}

	tagTile() {
		IsInit = false;

		Terrain = TR_NULL;
		Object = OBJ_NULL;
		SubObject = OBJ_NULL;
	};
};