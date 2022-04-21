#pragma once

#include "GameNode.h"
#include "Environment.h"

class Item;
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

	inline int getPtToIndexX(float aX) {
		return aX / TILE_SIZE;
	};
	inline int getPtToIndexY(float aY) {
		return aY / TILE_SIZE;
	};

	function<void()> mPlayerGrapFunc;
	function<void()> mPlayerActionFunc;
	function<void()> mPlayerMoveFunc;

	void setPlayerActionFunc(function<void()> playerActionFunc) { mPlayerActionFunc = playerActionFunc;};
	void setPlayerGrapFunc(function<void()> playerGrapFunc) { mPlayerGrapFunc = playerGrapFunc;};
	void setPlayerMoveFunc(function<void()> playerGrapFunc) { mPlayerMoveFunc = playerGrapFunc;};

	Map() {};
	virtual ~Map() {};
protected:
	tagTile** mMapTile;
	ImageGp** mCurPalette;

	OBJTILE* mVObjectGroup;

	MapTileInfo mMapInfo;
	MapPortal* mPortalList;

	int mPortalCount;

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
	typedef map<TINDEX, Rock*> mapRock;
	typedef map<TINDEX, Rock*>::iterator mapIterRock;

	typedef map<TINDEX, Monster*> mapMonster;
	typedef map<TINDEX, Monster*>::iterator mapIterMonster;

	typedef map<TINDEX, Item*> mapItem;
	typedef map<TINDEX, Item*>::iterator mapIterItem;
public:
	void init(string mapKey);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	MineMap() {};
	~MineMap() {};
private:
	mapMonster mMonsterList;
	mapIterMonster miMonsterList;

	mapRock mRockList;
	mapIterRock miRockList;

	mapItem mItemList;
	mapIterItem miItemList;

	tagTileDef* mLadderTileDef;

	int mMineLevel;
	int mFloor;

	int mRockCount;
	int mMonsterCount;

	TINDEX mLadderIndex;

};

class FarmMap : public Map {
public:
	typedef map<tagTileDef*, Rock*> mapRock;
	typedef map<tagTileDef*, Rock*>::iterator mapIterRock;

	typedef map<tagTileDef*, Crop*> mapCrop;
	typedef map<tagTileDef*, Crop*>::iterator mapIterCrop;


	typedef map<tagTileDef*, Tree*> mapTree;
	typedef map<tagTileDef*, Tree*>::iterator mapIterTree;
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

	bool openUI;

	bool isOpenUi() { return openUI; }
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

class TownMap : public Map {
public:
	typedef map<tagTile*, Monster*> mapMonster;
	typedef map<tagTile*, Monster*>::iterator mapIterMonster;
public:
	mapMonster mMonsterList;
	mapIterMonster miMonsterList;

	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	TownMap() {};
	~TownMap() {};
private:
	int mMonsterCount;
};

