#include "Stdafx.h"
#include "TileClass.h"

HRESULT TileClass::init(void)
{
	//±¤»ê 1
	int index = 1;
	vector<tagTile*> vMines;
	
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	1,	1));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	1,	2));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	1,	3));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	1,	4));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	5));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	6));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	7));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	8));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	9));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	10));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	11));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	12));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	13));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	14));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	15));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	1,	16));

	vMines.push_back(new tagTile(TR_NONE,	index++,	2, 1));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	2, 2));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	2, 3));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	2, 4));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 5));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 6));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 7));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 8));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 9));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 10));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 11));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 12));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 13));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 14));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 15));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	2, 16));

	vMines.push_back(new tagTile(TR_NONE,	index++,	3,	1));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	3,	2));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	3,	3));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	3,	4));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	5));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	6));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	7));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	8));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	9));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	10));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	11));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	12));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	13));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	14));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	15));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	3,	16));

	mVMapSprites.insert(make_pair(IMGCLASS->MapMines1To30, vMines));

	return E_NOTIMPL;
}

void TileClass::release(void)
{
}

HRESULT TileClass::findTileNodeLIst(string strKey, OUT vector<tagTile*>& tagTiles)
{
	auto key = mVMapSprites.find(strKey);

	if (key != mVMapSprites.end())
	{
		tagTiles = key->second;
		return S_OK;
	}

	return E_FAIL;
}
