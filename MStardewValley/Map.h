#pragma once
#include "MapTile.h"
#include "GameNode.h"
#include "MineRock.h"

class Map: public GameNode
{
private:
	eLocation mLocation;
	
	vector<tagTile> mVTagTile;
	vector<MapTile*> mVTileMap;
public:
	ImageGp* mSpriteImg;

	bool isCollisionWall(RectF rectF);

	void init(string id, string mapSpriteId);

	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	bool ptInCollsionTile(int aX, int aY);

	Map() {};
	virtual ~Map() {};
};

class MineMap: public Map {
public:
	typedef vector<MineRock*> vRocks;
	typedef vector<MineRock*>::iterator vIRocks;
public:
	bool isCollisionRock(RectF rectF);

	void init(string id, int floor, eMineLevel level);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	MineMap() {};
	~MineMap() {};
private:
	vRocks mVRocks;
	vIRocks mViRocks;

	eMineLevel mMineLevel;
	int mFloor;
};

