#pragma once

enum TERRAIN //����
{
	TR_NULL,
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
	OBJ_NULL,
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

	int X;
	int Y;

	tagTile(TERRAIN terrain, int index, int terrainFrameX, int terrainFrameY) {
		Terrain = terrain;
		Object = OBJ_NULL;
		TerrainFrameX = terrainFrameX;
		TerrainFrameY = terrainFrameY;
		Index = index;
	};

	tagTile(OBJECT object, int index, int objectFrameX, int objectFrameY) {
		Terrain = TR_NULL;
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