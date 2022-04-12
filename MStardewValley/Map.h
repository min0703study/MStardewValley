#pragma once

#include "GameNode.h"
#include "MineRock.h"
#include "Monster.h"
#include "Environment.h"

class Map: public GameObject
{
public:
	void init(eLocation location);

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
	virtual void clickDownEvent();

	bool ptInCollsionTile(int aX, int aY);
	bool InCollsionTile(int index);

	float getTileRelX(int tileX) { return (tileX * TILE_SIZE) - CAMERA->getX(); };
	float getTileRelY(int tileY) { return (tileY * TILE_SIZE) - CAMERA->getY(); };

	function<void(tagTile*tile)> mSubObjRenderFunc;
	void setSubObjRenderFunc(function<void(tagTile* tile)> subObjRenderFunc);

	Map() {};
	virtual ~Map() {};
protected:
	eLocation mLocation;

	tagTile** mMapTile;
	MapTileInfo mTileInfo;
	ImageGp** mCurPalette;

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

class FarmMap : public Map {
public:
	typedef map<tagTile*, Rock*> mapRock;
	typedef map<tagTile*, Rock*>::iterator mapIterRock;
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;
private:
	mapRock mRockList;
	int mRockCount;

};

