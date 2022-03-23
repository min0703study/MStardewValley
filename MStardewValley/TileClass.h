#pragma once

#include "SingletonBase.h"

struct tagTile;

class TileClass: public SingletonBase<TileClass>
{
public:
	map<string, vector<tagTile*>> mVMapSprites;

	HRESULT init(void);
	HRESULT findTileNodeLIst(string strKey, OUT vector<tagTile*>& tagTiles);
	virtual void release(void);
};

