#pragma once
#include "MapTile.h"
#include "GameNode.h"

class Map: public GameNode
{
private:
public:
	vector<tagTile> mVTagTile;
	vector<MapTile*> mVTileMap;

	ImageGp* mSpriteImg;

	bool isCollisionWall(RectF rectF);

	void Init(string id, string mapId);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	Map() {};
	~Map() {};
};

