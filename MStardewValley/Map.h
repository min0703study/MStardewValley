#pragma once
#include "MapTile.h"
#include "GameNode.h"
#include "MineRock.h"
#include "Monster.h"

class Map: public GameObject
{
protected:
	eLocation mLocation;
	
	vector<tagTile> mVTagTile;
	vector<MapTile*> mVTileMap;

	int mTileXCount;
	int mTileYCount;
	int mTileAllCount;
public:
	ImageGp* mSpriteImg;

	bool isCollisionWall(RectF rectF);

	void init(string id, string mapSpriteId);

	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	bool ptInCollsionTile(int aX, int aY);

	bool InCollsionTile(int index);

	Map() {};
	virtual ~Map() {};
};

class MineMap: public Map {
public:
	typedef vector<MineRock*> vRocks;
	typedef vector<MineRock*>::iterator vIRocks;

	typedef vector<Monster*> vMonster;
	typedef vector<Monster*>::iterator vIMonster;

public:
	bool isCollisionRock(RectF rectF);

	void init(string id, int floor, eMineLevel level);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	float getEntranceAbsX() { return mEntranceTile->getAbsX(); };
	float getEntranceAbsY() { return mEntranceTile->getAbsY(); };

	MineMap() {};
	~MineMap() {};
private:
	MapTile* mEntranceTile; //입구 위치
	
	vRocks mVRocks;
	vIRocks mViRocks;

	vMonster mVMonster;
	vIMonster mViMonster;

	eMineLevel mMineLevel;

	int mFloor;
};

