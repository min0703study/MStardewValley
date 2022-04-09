#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MapPalette : public GameNode, public SingletonBase<MapPalette>
{
public:
	HRESULT init(void);

	void setTileInfo(void);
	void release(void);

	ImageGp * getBaseSprite(eMapSprite mapSprite);
	ImageGp** getPalette(eMapSprite mapSprite);

	map<string, vector<tagTile*>> mVMapSprites;
	HRESULT findTileNodeLIst(string strKey, OUT vector<tagTile*>& tagTiles);

	Bitmap * getBitmap(eMapSprite mapSprite, int startX, int startY, int xCount, int yCount);
private:
	ImageGp* mBaseImgList[eMapSprite::MS_END];
	ImageGp** mPallete[eMapSprite::MS_END];
};
