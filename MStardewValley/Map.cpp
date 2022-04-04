#include "Stdafx.h"
#include "Map.h"

bool Map::isCollisionWall(RectF rectF)
{
	for (vector<MapTile*>::iterator iVMapTile = mVTileMap.begin(); iVMapTile != mVTileMap.end(); iVMapTile++)
	{
		if ((*iVMapTile)->getAbsRectF().IntersectsWith(rectF)) {
			if (!(*iVMapTile)->isCanMove()) {
				return true;
			};
		}
	}

	return false;
}

void Map::init(string id, string mapSpriteId)
{
	mSpriteImg = GDIPLUSMANAGER->findAndCloneImage(mapSpriteId);

	mTileXCount = (*JSONMANAGER->findJsonValue(JSONCLASS->MapInfo))["map_tile_x_count"].asInt();
	mTileYCount = (*JSONMANAGER->findJsonValue(JSONCLASS->MapInfo))["map_tile_y_count"].asInt();

	mTileAllCount = mTileXCount * mTileYCount;

	float mines1To30PaletteW = (mSpriteImg->getMaxFrameX() + 1) * TILE_SIZE;
	float mines1To30PaletteH = (mSpriteImg->getMaxFrameY() + 1) * TILE_SIZE;

	//초기화
	for (int i = 0; i < mTileAllCount; i++) {
		mVTagTile.push_back(tagTile());
	}

	tagTile *thearray = &mVTagTile[0];
	LoadFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * mTileAllCount);

	int index = 0;

	bool isUpdate = false;
	
	for (vector<tagTile>::iterator iVtagTile = mVTagTile.begin(); iVtagTile != mVTagTile.end(); iVtagTile++, index++)
	{
		MapTile* mapTile = new MapTile;
		ImageGp* imgGp = new ImageGp;
		imgGp->init(getMemDc(), TILE_SIZE, TILE_SIZE);
		isUpdate = false;

		if ((*iVtagTile).Terrain != TR_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).TerrainFrameX, (*iVtagTile).TerrainFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		if ((*iVtagTile).Object != OBJ_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).ObjectFrameX, (*iVtagTile).ObjectFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		if ((*iVtagTile).SubObject != OBJ_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).SubObjectFrameX, (*iVtagTile).SubObjectFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		imgGp->rebuildChachedBitmap();

		float xPos = ((index % mTileXCount)) * TILE_SIZE;
		float yPos = (index / mTileXCount) * TILE_SIZE;

		mapTile->Init(id, (*iVtagTile).Index, xPos, yPos, TILE_SIZE, TILE_SIZE, &(*iVtagTile), imgGp);
		mVTileMap.push_back(mapTile);
	}
}

void Map::update(void)
{
}

void Map::render(void)
{
	for (vector<MapTile*>::iterator iVMapTile = mVTileMap.begin(); iVMapTile != mVTileMap.end(); iVMapTile++)
	{
		(*iVMapTile)->render();
	}
}

void Map::release(void)
{
}

bool Map::ptInCollsionTile(int aX, int aY)
{
	return !mVTileMap[aX + aY * mTileXCount]->isCanMove();
}

bool Map::InCollsionTile(int index)
{
	return !mVTileMap[index]->isCanMove();
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(string id, int floor, eMineLevel level)
{
	Map::init(id, IMGCLASS->MapMines1To30);

	int entranceIndex = (*JSONMANAGER->findJsonValue(JSONCLASS->MapInfo))["entrance_point_index"].asInt();

	mEntranceTile = mVTileMap[entranceIndex];

	CAMERA->setToCenterX(mEntranceTile->getAbsX());
	CAMERA->setToCenterY(mEntranceTile->getAbsY());

	mFloor = floor;
	mMineLevel = level;

	int mineCount = 0;
	int monsterCount = 0;

	int tempIndex = 0;
	while (mineCount < 20) {
		tempIndex = RND->getInt(mTileAllCount);
		if (!InCollsionTile(tempIndex)) {
			MineRock* mR = new MineRock;
			mR->init("광물", 
				(eMineStoneType)RND->getInt(5), 
				mVTileMap[tempIndex]->getAbsX(),
				mVTileMap[tempIndex]->getAbsY(),
				ROCK_WIDTH, 
				ROCK_HEIGHT, 
				XS_CENTER, YS_CENTER);
			mVRocks.push_back(mR);
			mineCount++;
		}
	}

	while (monsterCount < 2) {
		tempIndex = RND->getInt(mTileAllCount);
		if (!InCollsionTile(tempIndex)) {
			Grub* monster = new Grub;
			monster->init("몬스터", 
				mVTileMap[tempIndex]->getAbsX(),
				mVTileMap[tempIndex]->getAbsY(),
				50.0f, 
				50.0f, 
				XS_LEFT, 
				YS_TOP);
			mVMonster.push_back(monster);
			monsterCount++;
		}
	}
}

void MineMap::update(void)
{
	Map::update();

	for (mViRocks = mVRocks.begin(); mViRocks != mVRocks.end(); mViRocks++) {
		(*mViRocks)->update();
	}

	for (mViMonster = mVMonster.begin(); mViMonster != mVMonster.end(); mViMonster++) {
		(*mViMonster)->move(eGameDirection::GD_DOWN);
	}
}

void MineMap::render(void)
{
	Map::render();

	for (mViRocks = mVRocks.begin(); mViRocks != mVRocks.end(); mViRocks++) {
		(*mViRocks)->render();
	}

	for (mViMonster = mVMonster.begin(); mViMonster != mVMonster.end(); mViMonster++) {
		(*mViMonster)->render();
	}
}

void MineMap::release(void)
{
	Map::release();

	for (mViRocks = mVRocks.begin(); mViRocks != mVRocks.end(); mViRocks++) {
		(*mViRocks)->release();
	}
}

bool MineMap::isCollisionRock(RectF rectF)
{
	return false;
}

