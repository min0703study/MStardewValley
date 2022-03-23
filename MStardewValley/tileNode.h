#pragma once

enum TERRAIN //ÁöÇü
{
	TR_NONE,
	TR_NORMAL,
	TR_GRASS,
	TR_WOOD,
	TR_SAND,
	TR_SNOW,
	TR_WATER
};

enum OBJECT
{
	OBJ_WALL,
	OBJ_DOOR,
	OBJ_FENCE
};

typedef struct tagTile
{
	int Index;

	TERRAIN Terrain;
	OBJECT Object;

	int TerrainFrameX;
	int TerrainFrameY;

	int ObjectFrameX;
	int ObjectFrameY;

	tagTile(TERRAIN terrain, int index, int terrainFrameX, int terrainFrameY) {
		Terrain = terrain;
		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;
		Index = index;
	};

	tagTile(OBJECT object, int index, int objectFrameX, int objectFrameY) {
		Object = object;
		ObjectFrameX = objectFrameX;
		ObjectFrameY = objectFrameY;
		Index = index;
	};
};

typedef struct tagTileSprite
{
	string id;

	float frameX;
	float frameY;
};