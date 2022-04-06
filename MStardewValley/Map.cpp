#include "Stdafx.h"
#include "Map.h"

void Map::init(string id, string mapSpriteId)
{
	mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_2);
	mTagTile = MAPTILEMANAGER->findTile(MAPTILECLASS->MINE_2);

	mTileXCount = mTileInfo.XCount;
	mTileYCount = mTileInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;
}

void Map::update(void)
{
	if (KEYMANAGER->isStayKeyDown(LEFT_KEY)) {
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_LEFT))) {
			PLAYER->move(GD_LEFT);
		}
	}

	if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_RIGHT))) {
			PLAYER->move(GD_RIGHT);
		}
	}

	if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_UP))) {
			PLAYER->move(GD_UP);
		}
	}

	if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_DOWN))) {
			PLAYER->move(GD_DOWN);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		PLAYER->attack();
	}
}

void Map::render(void)
{
	for (int y = 0; y < mTileYCount; y++) {
		for (int x = 0; x < mTileXCount; x++) {
			if (mTagTile[x][y].Terrain != TR_NULL) {
				MAPPALETTE->getPalette()[mTagTile[x][y].TerrainFrameY][mTagTile[x][y].TerrainFrameX].render(getMemDc(), getRelX(mTagTile[x][y].X), getRelY(mTagTile[x][y].Y));
			}

			if (mTagTile[x][y].Object != OBJ_NULL) {
				MAPPALETTE->getPalette()[mTagTile[x][y].ObjectFrameY][mTagTile[x][y].ObjectFrameX].render(getMemDc(), getRelX(mTagTile[x][y].X), getRelY(mTagTile[x][y].Y));
			}

			GDIPLUSMANAGER->drawText(getMemDc(), to_wstring(y) + L" / " +  to_wstring(x), getRelX(mTagTile[x][y].X), getRelY(mTagTile[x][y].Y),20,Color(255,255,255));
		}
	}
}

bool Map::isCollisionWall(RectF rectF)
{
	int startX = getPtToIndexX(rectF.GetLeft());
	int toX = getPtToIndexX(rectF.GetRight());
	int startY = getPtToIndexY(rectF.GetTop());
	int endY = getPtToIndexY(rectF.GetBottom());

	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= toX; x++) {
			if (!mTagTile[x][y].IsCanMove) {
				return true;
			}
		}
	}

	return false;
}

bool Map::isCollisionTile(RectF rectF)
{
	int startX = getPtToIndexX(rectF.GetLeft());
	int toX = getPtToIndexX(rectF.GetRight());
	int startY = getPtToIndexY(rectF.GetTop());
	int endY = getPtToIndexY(rectF.GetBottom());

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < toX; x++) {
			if (!mTagTile[x][y].IsCanMove) {
				return true;
			}
		}
	}

	return false;
}

bool Map::ptInCollsionTile(int indexX, int indexY)
{
	return mTagTile[indexX][indexY].IsCanMove;
}

bool Map::InCollsionTile(int index)
{
	return mTagTile[index % 19][index / 19].IsCanMove;
}

void Map::release(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(string id, int floor, eMineLevel level)
{
	Map::init(id, IMGCLASS->MapMines1To30);

	mEntranceIndexX = mTileInfo.EnterenceIndex % 19;
	mEntranceIndexY = mTileInfo.EnterenceIndex / 19;

	CAMERA->setToCenterX(mEntranceIndexX * TILE_SIZE);
	CAMERA->setToCenterY(mEntranceIndexY * TILE_SIZE);

	mFloor = floor;
	mMineLevel = level;

	int mineCount = 0;
	int monsterCount = 0;

	int tempIndex = 0;

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mineCount < 20) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		if (mTagTile[tempIndexX][tempIndexY].IsCanMove) {
			MineRock* mR = new MineRock;
			mR->init("±¤¹°", 
				(eMineStoneType)RND->getInt(5), 
				mTagTile[tempIndexX][tempIndexY].X,
				mTagTile[tempIndexX][tempIndexY].Y,
				ROCK_WIDTH, 
				ROCK_HEIGHT, 
				XS_LEFT, YS_TOP);
			mTagTile[tempIndexX][tempIndexY].SubObject = OBJ_ROCK;
			mTagTile[tempIndexX][tempIndexY].IsCanMove = false;
			mineCount++;
			mVRocks.push_back(mR);
		}
	}

	while (monsterCount < 2) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		if (mTagTile[tempIndexX][tempIndexY].IsCanMove) {
			Grub* monster = new Grub;
			monster->init("¸ó½ºÅÍ", 
				mTagTile[tempIndexX][tempIndexY].X,
				mTagTile[tempIndexX][tempIndexY].Y,
				50.0f, 
				50.0f, 
				XS_LEFT, 
				YS_TOP);
			mTagTile[tempIndexX][tempIndexY].SubObject = OBJ_MONSTER;
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
		if (!isCollisionWall((*mViMonster)->getTempMoveAbsRectF())) {
			(*mViMonster)->move();
		};
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

