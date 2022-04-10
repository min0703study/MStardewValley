#pragma once

#include "GameNode.h"
#include "MineRock.h"
#include "Monster.h"

class Map: public GameObject
{
public:
	void init(string id, eLocation location);

	bool isCollisionWall(RectF rectF);
	bool isCollisionTile(RectF rectF);

	inline int getPtToIndexX(float aX) {
		return aX / TILE_SIZE;
	};

	inline int getPtToIndexY(float aY) {
		return aY / TILE_SIZE;
	};

	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	bool ptInCollsionTile(int aX, int aY);
	bool InCollsionTile(int index);

	Map() {};
	virtual ~Map() {};
protected:
	eLocation mLocation;

	tagTile** mMapTile;
	MapTileInfo mTileInfo;


	int mTileXCount;
	int mTileYCount;

	int mTileAllCount;

	ImageGp* mSpriteImg;
	eMapSprite mCurSprite;
private:
#if	DEBUG_MODE
	Gdiplus::CachedBitmap* mMapIndexBitmap;
#endif
};

class MineMap: public Map {
public:
	typedef vector<MineRock*> vRocks;
	typedef vector<MineRock*>::iterator vIRocks;

	typedef vector<Monster*> vMonster;
	typedef vector<Monster*>::iterator vIMonster;

public:
	bool isCollisionRock(RectF rectF);

	void init(string id, eLocation location);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	float getEntranceAbsX() { return mEntranceIndexX * TILE_SIZE; };
	float getEntranceAbsY() { return mEntranceIndexY * TILE_SIZE; };

	MineMap() {};
	~MineMap() {};
private:
	int mEntranceIndexX; //입구 위치
	int mEntranceIndexY; //입구 위치
	
	vRocks mVRocks;
	vIRocks mViRocks;

	vMonster mVMonster;
	vIMonster mViMonster;

	int mMineLevel;

	int mRockCount;
	int mMonsterCount;

	int mFloor;
};

