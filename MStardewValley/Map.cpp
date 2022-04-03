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

	float mines1To30PaletteW = (mSpriteImg->getMaxFrameX() + 1) * TILE_SIZE;
	float mines1To30PaletteH = (mSpriteImg->getMaxFrameY() + 1) * TILE_SIZE;

	//�ʱ�ȭ
	for (int x = 0; x < mTileXCount; x++) {
		for (int y = 0; y < mTileYCount; y++) {
			mVTagTile.push_back(tagTile());
		}
	}

	tagTile *thearray = &mVTagTile[0];
	LoadFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * mTileXCount * mTileYCount);

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

		if (isUpdate) {

		}

		imgGp->rebuildChachedBitmap();

		float indexX = ((index % mTileXCount)) * TILE_SIZE;
		float indexY = (index / mTileXCount) * TILE_SIZE;

		mapTile->Init(id, index, indexX, indexY, TILE_SIZE, TILE_SIZE, &(*iVtagTile), imgGp);
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
	while (mineCount < 5) {
		int x = RND->getInt(mTileXCount);
		int y = RND->getInt(mTileYCount);

		if (!ptInCollsionTile(x, y)) {
			MineRock* mR = new MineRock;
			mR->init("����", (eMineStoneType)RND->getInt(5), x * TILE_SIZE, y * TILE_SIZE, ROCK_WIDTH, ROCK_HEIGHT, XS_LEFT, YS_TOP);
			mVRocks.push_back(mR);
			mineCount++;
		}
	}

	while (monsterCount < 2) {
		int x = RND->getInt(mTileXCount);
		int y = RND->getInt(mTileYCount);

		if (!ptInCollsionTile(x, y)) {
			Monster* monster = new Monster;
			monster->init("����", eMonsterType::MST_BUG_CATERFILLER, x * TILE_SIZE, y * TILE_SIZE, 50.0f, 50.0f, XS_LEFT, YS_TOP);
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

