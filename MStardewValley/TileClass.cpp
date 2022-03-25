#include "Stdafx.h"
#include "TileClass.h"

HRESULT TileClass::init(void)
{
	//±¤»ê 1
	int index = 1;
	int xFrame = 0;
	vector<tagTile*> vMines;
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 16; x++) {
			vMines.push_back(new tagTile(TR_NORMAL, index++, x, y));
		}
	}
	/*
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	xFrame++	,0 ));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++	,0 ));

	xFrame = 0;
	vMines.push_back(new tagTile(TR_NONE,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(TR_NORMAL, index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	 1));

	xFrame = 0;
	vMines.push_back(new tagTile(TR_NONE,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(TR_NORMAL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	vMines.push_back(new tagTile(OBJ_WALL,	index++,	xFrame++,	2));
	*/
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
