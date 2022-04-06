#pragma once

#include "GameNode.h"
#include "MineRock.h"
#include "Monster.h"

class Map: public GameObject
{
public:
	void init(string id, string mapSpriteId);

	bool isCollisionWall(RectF rectF);
	bool isCollisionTile(RectF rectF);

	inline int getPtToIndexX(float x) {
		return (x - getAbsRectF().GetLeft()) / TILE_SIZE;
	};
	inline int getPtToIndexY(float y) {
		return (y - getAbsRectF().GetTop()) / TILE_SIZE;
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

	ImageGp*** mTileImgList;
	tagTile** mTagTile;

	MapTileInfo mTileInfo;

	int mTileXCount;
	int mTileYCount;

	int mTileAllCount;

	ImageGp* mSpriteImg;
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

	eMineLevel mMineLevel;

	int mFloor;
};

