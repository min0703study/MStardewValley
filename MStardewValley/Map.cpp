#include "Stdafx.h"
#include "Map.h"

bool Map::isCollisionWall(RectF rectF)
{
	int startX = getPtToIndexX(rectF.GetLeft());
	int toX = getPtToIndexX(rectF.GetRight());
	int startY = getPtToIndexY(rectF.GetTop());
	int endY = getPtToIndexY(rectF.GetBottom());

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < toX; x++) {
			if (!mTagTile[x][y].IsCanMove) {
				return false;
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

void Map::init(string id, string mapSpriteId)
{
	mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_2);
	mTileImgList = MAPTILEMANAGER->findImg(MAPTILECLASS->MINE_2);
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
			mTileImgList[x][y]->render(getMemDc(), mTagTile[x][y].X, mTagTile[x][y].Y);
		}
	}
}

void Map::release(void)
{
}

bool Map::ptInCollsionTile(int indexX, int indexY)
{
	return mTagTile[indexX][indexY].IsCanMove;
}

bool Map::InCollsionTile(int index)
{
	return mTagTile[index % 19][index / 19].IsCanMove;
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

	while (mineCount < 20) {
		tempIndex = RND->getInt(mTileAllCount);
		if (!InCollsionTile(tempIndex)) {
			MineRock* mR = new MineRock;
			mR->init("±¤¹°", 
				(eMineStoneType)RND->getInt(5), 
				0,
				0,
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
			monster->init("¸ó½ºÅÍ", 
				0.0f,0.0f,
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

