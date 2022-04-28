#pragma once

#include "GameNode.h"
#include "Environment.h"
#include "NPC.h"
class Item;
class Monster;

class Map: public GameObject
{
public:
	typedef map<TINDEX, const MapPortal> mapPortal;
	typedef map<TINDEX, MapPortal>::iterator mapIterPortal;
public:
	void init(string mapKey, int portalKey);

	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	void addObject(TINDEX index);
	virtual void rebuild(string mapKey);
	void effectSound(eSoundType type);
	bool isCollisionTile(RectF rectF);

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
	void setPlayerMoveAfter(function<void()> playerMoveAfterFunc) { mPlayerMoveAfterFunc = playerMoveAfterFunc;};
	void setRenderSubObj(function<void(int level)> renderSubObj) { mRenderSubObj = renderSubObj;};

	Map() {};
	virtual ~Map() {};
protected:
	tagTile** mMapTile;
	ImageGp** mCurPalette;

	vector<OBJTILE>* mVObjectGroup;

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
	TINDEX mStartIndex;

	bool bFixedXCamera;
	bool bFixedYCamera;

	bool bInitPortal;
private:
	function<void()> mPlayerGrapFunc;
	function<void()> mPlayerActionFunc;
	function<void(eGameDirection)> mPlayerMoveFunc;
	function<void()> mPlayerMoveAfterFunc;
	function<void(int y)> mRenderSubObj;

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
	typedef struct tagDropItem {
		const Item* TargetItem;

		float Gravity;
		int DropDirection;

		bool IsEndDrop;
		bool IsPickUp;

		float CurX;
		float CurY;

		bool ToPlayer;

		tagDropItem(const Item* item, float curX, float curY) : TargetItem(item), Gravity(4.0f), DropDirection(1), IsEndDrop(false), IsPickUp(false), CurX(curX), CurY(curY) {};
	} DropItem;
public:
	typedef map<TINDEX, Rock*> mapRock;
	typedef map<TINDEX, Rock*>::iterator mapIterRock;

	typedef map<TINDEX, Crop*> mapCrop;
	typedef map<TINDEX, Crop*>::iterator mapIterCrop;

	typedef map<TINDEX, Tree*> mapTree;
	typedef map<TINDEX, Tree*>::iterator mapIterTree;

	typedef map<TINDEX, Weed*> mapWeed;
	typedef map<TINDEX, Weed*>::iterator mapIterWeed;

	typedef map<TINDEX, DropItem*> mapItem;
	typedef map<TINDEX, DropItem*>::iterator mapIterItem;
public:
	HRESULT init(const string mapKey, int portalKey);
	
	void update(void) override;
	void render(void) override;
	void release(void) override;

	int stage;

	FarmMap() {};
	~FarmMap() {};
private:
	mapRock mRockList;
	mapIterRock miRockList;
	mapIterRock miRRockList;

	mapTree mTreeList;
	mapIterTree miTreeList;
	mapIterTree miRTreeList;
	
	mapCrop mCropList;
	mapIterCrop miCropList;
	mapIterCrop miRCropList;

	mapItem mItemList;
	mapIterItem miItemList;
	mapIterItem miRItemList;

	mapWeed mWeedList;
	mapIterWeed miWeedList;
	mapIterWeed miRWeedList;


	int mRockCount;
	int mTreeCount;
	int mWeedCount;
};

class ShopMap : public Map {
public:
	HRESULT init(const string mapKey, int portalKey);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	ImageGp* getSaleNpcPortraitImg(void);
	vector<string> getSaleItemIdList(void);

	bool getReqSaleListUI() {
		return bReqSaleListUI;
	};

	void setReqShopListUI(bool flag) {
		bReqSaleListUI = flag;
	}

	ShopMap() {};
	~ShopMap() {};
private:
	bool bReqSaleListUI;
	eShopType mShopType;
	eNpcs mMasterNPC;
};

class HomeMap : public Map {
public:
	HRESULT init(const string mapKey, int portalKey);
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

	HRESULT init(string mapKey, int portalKey);

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
	HRESULT init(const string mapKey, int portalKey);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	LoadMap() {};
	~LoadMap() {};
};

