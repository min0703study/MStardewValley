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
	typedef map<TINDEX, const MapPortal> mapPortal;
	typedef map<TINDEX, MapPortal>::iterator mapIterPortal;
public:
	void init(string mapKey);
	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	void addObject(TINDEX index);
	virtual void rebuild(string mapKey);
	bool isCollisionTile(RectF rectF);

	inline int getStartX() { 
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
	inline int getEndX() {
		if (CAMERA->getEndTileXIndex() > mTileXCount) {
			return mTileXCount;
		}
		else {
			return CAMERA->getEndTileXIndex();
		}
	};
	inline int getEndY() {
		if (CAMERA->getEndTileYIndex() > mTileYCount) {
			return mTileYCount;
		}
		else {
			return CAMERA->getEndTileYIndex();
		}
	};

	inline float getTileRelX(int tileX) { return (tileX * TILE_SIZE) - CAMERA->getX(); };
	inline float getTileRelY(int tileY) { return (tileY * TILE_SIZE) - CAMERA->getY(); };

	inline int getPtToIndexX(float aX) {
		return aX / TILE_SIZE;
	};
	inline int getPtToIndexY(float aY) {
		return aY / TILE_SIZE;
	};

	inline int getReqSceneChange() { return bReqChangeScene; }
	inline void setReqSceneChange(bool flag) { bReqChangeScene = flag; }
	inline const MapPortal getReqSceneChangePortal() { return mReqChangeScene; }

	inline tagTile* Map::getTile(TINDEX tIndex) { return &mMapTile[tIndex.Y][tIndex.X];}

	void setPlayerActionFunc(function<void()> playerActionFunc) { mPlayerActionFunc = playerActionFunc;};
	void setPlayerGrapFunc(function<void()> playerGrapFunc) { mPlayerGrapFunc = playerGrapFunc;};
	void setPlayerMoveFunc(function<void(eGameDirection)> playerGrapFunc) { mPlayerMoveFunc = playerGrapFunc;};

	Map() {};
	virtual ~Map() {};
protected:
	tagTile** mMapTile;
	ImageGp** mCurPalette;

	OBJTILE* mVObjectGroup;

	MapTileInfo mMapInfo;
	MapPortal* mPortalList;
	mapPortal mPortalMap;

	int mPortalCount;

	int mTileXCount;
	int mTileYCount;

	int mTileAllCount;

	int mRenderSTileX;
	int mRenderSTileY;
	int mRenderETileX;
	int mRenderETileY;

	bool bReqChangeScene;
	MapPortal mReqChangeScene;
private:
	function<void()> mPlayerGrapFunc;
	function<void()> mPlayerActionFunc;
	function<void(eGameDirection)> mPlayerMoveFunc;

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
	void init(int floor);
	void update(void) override;
	void render(void) override;
	void release(void) override;
	void rebuild(int floor);

	inline bool getRebuildRequest() const { return bReqRebuild; };
	inline void setRebuildRequest(bool flag) { bReqRebuild = flag; };

	inline int getRequestFloor() const { return mReqFloor; };

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

	TINDEX mLadderIndex;

	bool bReqRebuild;
	int mReqFloor;

	bool bReqElevatorUi;
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
	HRESULT init(const string mapKey, int portalKey);

	void update(void) override;
	void render(void) override;
	void release(void) override;

	vector<string> getSaleItemIdList(void);

	ShopMap() {};
	~ShopMap() {};
private:
	bool bReqShopUI;
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

class LoadMap: public Map {
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	LoadMap() {};
	~LoadMap() {};
};

