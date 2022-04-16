#pragma once

#include "GameNode.h"
#include "Environment.h"

class Monster;
//class Rock;
//class Crop;

class Map: public GameObject
{
public:
	void init(string mapKey);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	inline int getPtToIndexX(float aX) {
		return aX / TILE_SIZE;
	};
	inline int getPtToIndexY(float aY) {
		return aY / TILE_SIZE;
	};

	bool isCollisionTile(RectF rectF);

	int getStartX() { 
		if (CAMERA->getStartTileXIndex() < 0) {
			return 0;
		} else {
			return CAMERA->getStartTileXIndex();
		}
	};
	inline int getStartY() {
		if (CAMERA->getStartTileYIndex() < 0) {
			return 0;
		} else {
			return CAMERA->getStartTileYIndex();
		}
	};
	int getEndX() {
		if (CAMERA->getEndTileXIndex() > mTileXCount) {
			return mTileXCount;
		}
		else {
			return CAMERA->getEndTileXIndex();
		}
	};
	int getEndY() {
		if (CAMERA->getEndTileYIndex() > mTileYCount) {
			return mTileYCount;
		}
		else {
			return CAMERA->getEndTileYIndex();
		}
	};

	float getTileRelX(int tileX) { return (tileX * TILE_SIZE) - CAMERA->getX(); };
	float getTileRelY(int tileY) { return (tileY * TILE_SIZE) - CAMERA->getY(); };

	function<void(tagTile*tile)> mSubObjRenderFunc;
	function<void()> mPlayerGrapFunc;
	function<void()> mPlayerActionFunc;
	function<void()> mPlayerMoveFunc;

	void setSubObjRenderFunc(function<void(tagTile* tile)> subObjRenderFunc) { mSubObjRenderFunc = subObjRenderFunc; };
	void setPlayerActionFunc(function<void()> playerActionFunc) { mPlayerActionFunc = playerActionFunc;};
	void setPlayerGrapFunc(function<void()> playerGrapFunc) { mPlayerGrapFunc = playerGrapFunc;};
	void setPlayerMoveFunc(function<void()> playerGrapFunc) { mPlayerMoveFunc = playerGrapFunc;};

	Map() {};
	virtual ~Map() {};
protected:
	MapTileInfo mMapInfo;
	PORTAL* mPortalList;
	int mPortalCount;

	tagTile** mMapTile;
	ImageGp** mCurPalette;

	int mTileXCount;
	int mTileYCount;

	int mTileAllCount;

	int mRenderSTileX;
	int mRenderSTileY;
	int mRenderETileX;
	int mRenderETileY;
private:
#if	DEBUG_MODE
	Gdiplus::CachedBitmap* mDebugCBitmap;
#endif
};

class MineMap: public Map {
public:
	typedef vector<Rock*> vRocks;
	typedef vector<Rock*>::iterator vIRocks;

	typedef vector<Monster*> vMonster;
	typedef vector<Monster*>::iterator vIMonster;
public:
	bool isCollisionRock(RectF rectF);

	void init(string id, int floor);

	void init(string mapKey);

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

	typedef map<tagTile*, Crop*> mapCrop;
	typedef map<tagTile*, Crop*>::iterator mapIterCrop;


	typedef map<tagTile*, Tree*> mapTree;
	typedef map<tagTile*, Tree*>::iterator mapIterTree;
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	int stage;

	FarmMap() {};
	~FarmMap() {};
private:
	mapRock mRockList;
	mapTree mTreeList;
	mapCrop mCropList;

	int mRockCount;
	int mTreeCount;

};

class ShopMap : public Map {
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	ShopMap() {};
	~ShopMap() {};
private:

};

class HomeMap : public Map {
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	HomeMap() {};
	~HomeMap() {};
private:

};

