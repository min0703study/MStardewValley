#pragma once
#include "MapTile.h"
#include "GameNode.h"

class Map: public GameNode
{
private:
public:
	vector<MapTile*> mVTileMap;
	vector<tagTile*> mCurTilePalette;
	vector<tagTile> mCurTagTile;

	GameUI* mTilePalette;
	ImageGp* mSpriteImg;

	void Init(string id, string mapId);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	Map() {};
	~Map() {};
};

