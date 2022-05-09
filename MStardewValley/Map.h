#pragma once

#include "GameNode.h"
#include "Environment.h"
#include "CraftObject.h"
#include "NPC.h"

class Item;
class Monster;

typedef struct tagDropItem {
	const Item* TargetItem;

	float Gravity;
	int DropDirection;

	bool IsEndDrop;
	bool IsPickUp;

	float CurX;
	float CurY;

	float DropAniTime;
	bool ToPlayer;

	tagDropItem(const Item* item, float curX, float curY) : TargetItem(item), Gravity(4.0f), DropDirection(1), IsEndDrop(false), IsPickUp(false), DropAniTime(1.0f), ToPlayer(false), CurX(curX), CurY(curY) {};
} DropItem;

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

	virtual void inToPlayer(int portal);
	virtual void inToPlayer(TINDEX tIndex);

	void addObject(TINDEX index);
	virtual void rebuild(string mapKey);
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
	inline const MapPortal getReqSceneChangePortal() { return mReqChangeScenePortal; }

	inline int getReqShowEventBox() const { return bReqShowEventBox; }
	inline void setReqShowEventBox(bool flag) { bReqShowEventBox = flag; }
	inline string getReqShowEventBoxItemId() const { return mReqShowEventBoxItemId; };

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
	MapPortal mReqChangeScenePortal;

	bool bReqShowEventBox;
	string mReqShowEventBoxItemId;
	TINDEX mStartIndex;

	bool bFixedXCamera;
	bool bFixedYCamera;

	function<Rock* (TINDEX tIndex)>		mAttackRockFunc;
	function<Tree* (TINDEX tIndex)>		mAttackTreeFunc;
	function<Weed* (TINDEX tIndex)>		mAttackWeedFunc;
	function<Monster* (TINDEX tIndex)>	mAttackMonsterFunc;
	function<CraftObject* (TINDEX tIndex)>	mAttackCraftObjectFunc;
	function<Crop* (TINDEX tIndex)>		mUseWeteringCanFunc;
	function<DropItem* (TINDEX tIndex)>		mPickUpItemFunc;

	function<void()> mPlayerGrapFunc;
	function<void()> mPlayerActionFunc;
	function<void(eGameDirection)> mPlayerMoveFunc;
	function<void()> mPlayerMoveAfterFunc;
	function<void(int y)> mRenderSubObj;

	function<Crop* (eCropType cropType, TINDEX tIndex)> mPlantCropFunc;
	function<void (eCraftablesType craftablesType, TINDEX tIndex)> mCraftObjectPlace;

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

	typedef map<TINDEX, DropItem*> mapItem;
	typedef map<TINDEX, DropItem*>::iterator mapIterItem;
public:
	void init(int floor);
	void update(void) override;
	void render(void) override;
	void release(void) override;
	void rebuild(int floor);
	void down();

	inline bool getRebuildRequest() const { return bReqRebuild; };
	inline void setRebuildRequest(bool flag) { bReqRebuild = flag; };
	inline int getRequestFloor() const { return mReqFloor; };

	MineMap() {};
	~MineMap() {};
private:
	mapMonster mMonsterList;
	mapIterMonster miRMonsterList;
	mapIterMonster miMonsterList;

	mapRock mRockList;
	mapIterRock miRockList;
	mapIterRock miRRockList;

	mapItem mItemList;
	mapIterItem miRItemList;
	mapIterItem miItemList;

	tagTileDef* mLadderTileDef;

	TINDEX mLadderIndex;

	bool bReqRebuild;
	int mReqFloor;

	bool bReqElevatorUi;
};

class FarmMap : public Map {
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

	typedef map<TINDEX, CraftObject*> mapCraftObject;
	typedef map<TINDEX, CraftObject*>::iterator mapIterCraftObject;
public:
	HRESULT init(const string mapKey);
	
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

	mapCraftObject mCraftObjectList;
	mapIterCraftObject miCraftObjectList;
	mapIterCraftObject miRCraftObjectList;

	int mRockCount;
	int mTreeCount;
	int mWeedCount;
};

class ShopMap : public Map {
public:
	HRESULT init(const string mapKey, const eShopType shopType);

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
	NPC* mMasterNPC;
	TINDEX mMasterNPCIndex;
};

class HomeMap : public Map {
public:
	HRESULT init(const string mapKey);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	inline TINDEX getBedIndex(void) const { return mBedIndex; }

	HomeMap() {};
	~HomeMap() {};
private:
	TINDEX mBedIndex;
};

class TownMap : public Map {
public:
	typedef map<tagTile*, Monster*> mapMonster;
	typedef map<tagTile*, Monster*>::iterator mapIterMonster;

	typedef map<TINDEX, CraftObject*> mapCraftObject;
	typedef map<TINDEX, CraftObject*>::iterator mapIterCraftObject;
public:
	mapMonster mMonsterList;
	mapIterMonster miMonsterList;

	mapCraftObject mCraftObjectList;
	mapIterCraftObject miCraftObjectList;
	mapIterCraftObject miRCraftObjectList;

	HRESULT init(string mapKey);
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
	HRESULT init(const string mapKey);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	LoadMap() {};
	~LoadMap() {};
};

