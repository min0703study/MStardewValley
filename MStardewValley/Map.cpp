#include "Stdafx.h"
#include "Map.h"

void Map::init(string id, eLocation location)
{
	switch (location)
	{
	case L_MINE_1:
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_1);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->MINE_1);
		break;
	case L_MINE_2:
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_2);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->MINE_2);
		break;
	default:
		break;
	}

	mTileXCount = mTileInfo.XCount;
	mTileYCount = mTileInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;


#if	DEBUG_MODE
	//DEBUG
	GameObject::Init(id, 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);

	Bitmap* tempIndexBitmap = GDIPLUSMANAGER->getBlankBitmap(mWidth, mHeight);
	for (int y = 0; y < mTileYCount; y++) {
		for (int x = 0; x < mTileXCount; x++) {
			GDIPLUSMANAGER->drawTextToBitmap(tempIndexBitmap, to_wstring(y) + L" / " + to_wstring(x), x * TILE_SIZE, y * TILE_SIZE, 15, Color(255, 255, 255));
		}
	}
	mMapIndexBitmap = GDIPLUSMANAGER->bitmapToCachedBitmap(getMemDc(), tempIndexBitmap);
#endif
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
		
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		if (mMapTile[PLAYER->getAttackIndexY()][PLAYER->getAttackIndexX()].Object == OBJ_DOOR) {
			PLAYER->setToLoaction((eLocation)(PLAYER->getCurLoaction() + 1));
			SCENEMANAGER->changeScene("mine");
		}

		mMapTile[PLAYER->getAttackIndexY()][PLAYER->getAttackIndexX()].toString();
	}
}

void Map::render(void)
{
	for (int y = 0; y < mTileYCount; y++) {
		for (int x = 0; x < mTileXCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				MAPPALETTE->getPalette()[tile.TerrainFrameY][tile.TerrainFrameX].render(getMemDc(), getRelX(tile.X), getRelY(tile.Y));
			}

			if (tile.Object != OBJ_NULL) {
				MAPPALETTE->getPalette()[tile.ObjectFrameY][tile.ObjectFrameX].render(getMemDc(), getRelX(tile.X), getRelY(tile.Y));
			}
		}
	}

#if DEBUG_MODE
	GDIPLUSMANAGER->render(getMemDc(), mMapIndexBitmap, getRelRectF().GetLeft(), getRelRectF().GetTop());
	GDIPLUSMANAGER->drawText(getMemDc(), to_wstring(PLAYER->getIndexY()) + L" / " + to_wstring(PLAYER->getIndexX()), 10.0f, 70.0f,7, Color(255,255,255));
	GDIPLUSMANAGER->drawRectF(getMemDc(), RectF(getRelX(PLAYER->getIndexX() * TILE_SIZE), getRelY(PLAYER->getIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(100, 255, 255, 0));
	GDIPLUSMANAGER->drawRectF(getMemDc(), RectF(getRelX(PLAYER->getAttackIndexX() * TILE_SIZE), getRelY(PLAYER->getAttackIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(100, 255, 0, 0));
	
#endif
}

bool Map::isCollisionWall(RectF rectF)
{
	int startX = getPtToIndexX(rectF.GetLeft());
	int toX = getPtToIndexX(rectF.GetRight());
	int startY = getPtToIndexY(rectF.GetTop());
	int endY = getPtToIndexY(rectF.GetBottom());

	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= toX; x++) {
			if (!mMapTile[x][y].IsCanMove) {
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
			if (!mMapTile[x][y].IsCanMove) {
				return true;
			}
		}
	}

	return false;
}

bool Map::ptInCollsionTile(int indexX, int indexY)
{
	return mMapTile[indexX][indexY].IsCanMove;
}

bool Map::InCollsionTile(int index)
{
	return mMapTile[index % 19][index / 19].IsCanMove;
}

void Map::release(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(string id, eLocation location)
{
	Map::init(id, location);

	mEntranceIndexX = mTileInfo.EnterenceIndex % mTileInfo.XCount;
	mEntranceIndexY = mTileInfo.EnterenceIndex / mTileInfo.YCount;

	CAMERA->setToCenterX(mEntranceIndexX * TILE_SIZE);
	CAMERA->setToCenterY(mEntranceIndexY * TILE_SIZE);

	if (location == eLocation::L_MINE_1) {
		mFloor = 1;
		mMineLevel = 1;
		mRockCount = 0;
		mMonsterCount = 0;
	}
	else if (location == eLocation::L_MINE_2) {
		mFloor = 2;
		mMineLevel = 1;
		mRockCount = 10;
		mMonsterCount = 2;
	}

	int tempIndex = 0;

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mVRocks.size() < mRockCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		auto& curTile = mMapTile[tempIndexY][tempIndexX];
		if (curTile.IsCanMove) {
			MineRock* mR = new MineRock;
			mR->init("±¤¹°", 
				(eMineStoneType)RND->getInt(5), 
				curTile.X,
				curTile.Y,
				ROCK_WIDTH, 
				ROCK_HEIGHT, 
				XS_LEFT, YS_TOP);
			curTile.SubObject = OBJ_ROCK;
			curTile.IsCanMove = false;
			mVRocks.push_back(mR);
		}
	}

	while (mVMonster.size() < mMonsterCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		auto& curTile = mMapTile[tempIndexY][tempIndexX];
		if (curTile.IsCanMove) {
			Grub* monster = new Grub;
			monster->init("¸ó½ºÅÍ", 
				curTile.X,
				curTile.Y,
				50.0f, 
				50.0f, 
				XS_LEFT, 
				YS_TOP);

			curTile.SubObject = OBJ_MONSTER;
			mVMonster.push_back(monster);
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

/////////////////////////////////////////////////////////////////////////////////////////////////
