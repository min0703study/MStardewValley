#include "Stdafx.h"
#include "Map.h"

void Map::init(eLocation location)
{
	switch (location)
	{
	case L_MINE_1:
		mCurSprite = eMapSprite::MS_MINE_1TO30;
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_1);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->MINE_1);
		break;
	case L_MINE_2:
		mCurSprite = eMapSprite::MS_MINE_1TO30;
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->MINE_2);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->MINE_2);
		break;
	case L_FARM:
		mCurPalette = MAPPALETTE->getPalette(eMapSprite::MS_OUTDOOR_SPRING);
		mCurSprite = eMapSprite::MS_OUTDOOR_SPRING;
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->FARM);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->FARM);
		break;
	case L_SHOP:
		mCurSprite = eMapSprite::MS_TOWN_INTERIOR;
		mCurPalette = MAPPALETTE->getPalette(eMapSprite::MS_TOWN_INTERIOR);
		mTileInfo = MAPTILEMANAGER->findInfo(MAPTILECLASS->Shop);
		mMapTile = MAPTILEMANAGER->findTile(MAPTILECLASS->Shop);
		break;
	default:
		break;
	}

	mTileXCount = mTileInfo.XCount;
	mTileYCount = mTileInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	mPlayerActionFunc = [](){};
	mPlayerGrapFunc = [](){};


#if	DEBUG_MODE
	GameObject::Init("", 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);

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
		PLAYER->changeDirection(GD_LEFT);
		PLAYER->changeActionStat(PS_WALK);
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_LEFT))) {
			PLAYER->moveTo(GD_LEFT);
		}
	}

	if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
		PLAYER->changeDirection(GD_RIGHT);
		PLAYER->changeActionStat(PS_WALK);
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_RIGHT))) {
			PLAYER->moveTo(GD_RIGHT);
		}
	}

	if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
		if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
			PLAYER->changeDirection(GD_UP);		
		}
		PLAYER->changeActionStat(PS_WALK);
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_UP))) {
			PLAYER->moveTo(GD_UP);
		}
	}

	if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
		if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
			PLAYER->changeDirection(GD_DOWN);
		}
		PLAYER->changeActionStat(PS_WALK);
		if (!isCollisionTile(PLAYER->getTempMoveBoxRectF(GD_DOWN))) {
			PLAYER->moveTo(GD_DOWN);
		}
	}

	if (KEYMANAGER->isAllKeysUp(4, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY)) {
		if (!PLAYER->isActing()) {
			PLAYER->changeActionStat(PS_IDLE);
		}
	}

	if (!UIMANAGER->isClickUI()) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			PLAYER->attack();
			mPlayerActionFunc();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			PLAYER->grap();
			mPlayerGrapFunc();
			mMapTile[PLAYER->getAttackIndexY()][PLAYER->getAttackIndexX()].toString();
		}
	}
}

void Map::render(void)
{
	for (int y = 0; y < mTileYCount; y++) {
		for (int x = 0; x < mTileXCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
			}

			if (tile.Object != OBJ_NULL) {
				mCurPalette[tile.ObjectFrameY][tile.ObjectFrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
			}

			if (tile.SubObject != SOBJ_NULL) {
				mSubObjRenderFunc(&tile);
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
	Map::init(location);

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
	else if (location == eLocation::L_FARM) {
		mFloor = 0;
		mMineLevel = 0;
		mRockCount = 0;
		mMonsterCount = 0;
	}

	int tempIndex = 0;

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mVMonster.size() < mMonsterCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		auto& curTile = mMapTile[tempIndexY][tempIndexX];
		if (curTile.IsCanMove) {
			Grub* monster = new Grub;
			monster->init("����", 
				curTile.X,
				curTile.Y,
				50.0f, 
				50.0f, 
				XS_LEFT, 
				YS_TOP);

			curTile.SubObject = SOBJ_MONSTER;
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

HRESULT FarmMap::init()
{
	Map::init(eLocation::L_FARM);

	CAMERA->setToCenterX(10 * TILE_SIZE);
	CAMERA->setToCenterY(10 * TILE_SIZE);

	stage = 0;
	mRockCount = 0;
	
	setSubObjRenderFunc([this](tagTile* tile) {
		switch (tile->SubObject) {
		case SOBJ_ROCK:
			mRockList.find(tile)->second->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			break;
		case SOBJ_HOED:
			HOEDSPRITE->getNormalHoed(0, 0)->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			break;
		case SOBJ_HOED_WET:
			HOEDSPRITE->getWetHoed(0,0)->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			break;
		case SOBJ_SEED:
			HOEDSPRITE->getNormalHoed(0, 0)->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			mCropList.find(tile)->second->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			break;
		}
	});
	setPlayerActionFunc([this](void){
		if (!PLAYER->getHoldItemBox().IsEmpty) {
			Item* holdItem = PLAYER->getHoldItemBox().Item;
			eItemType itemType = holdItem->getItemType();

			int tileX = PLAYER->getAttackIndexX();
			int tileY = PLAYER->getAttackIndexY();

			switch (itemType)
			{
			case ITP_SEED: {
				PLAYER->useItem();
				mMapTile[tileY][tileX].SubObject = SOBJ_SEED;
				Crop* crop = new Crop();
				crop->init(eCropType::CT_PARSNIP, tileX, tileY);
				mCropList.insert(make_pair(&mMapTile[tileY][tileX], crop));
				break;
			}
			case ITP_TOOL: {
				PLAYER->useItem();
				if (holdItem->getItemId() == ITEMCLASS->WATERING_CAN) {
					mMapTile[tileY][tileX].SubObject = SOBJ_HOED_WET;
				}
				else if (holdItem->getItemId() == ITEMCLASS->HOE) {
					mMapTile[tileY][tileX].SubObject = SOBJ_HOED;
				}
				else if (holdItem->getItemId() == ITEMCLASS->PICK) {
					mMapTile[tileY][tileX].SubObject = SOBJ_NULL;
					//Crop* crop = mCropList.find(&mMapTile[tileY][tileX])->second;
					//crop->release();
					mCropList.erase(&mMapTile[tileY][tileX]);
				}

				break;
			}
			default:
				break;
			}
		}
	});
	setPlayerGrapFunc([this](void) {
		int tileX = PLAYER->getAttackIndexX();
		int tileY = PLAYER->getAttackIndexY();

		if (mMapTile[tileY][tileX].SubObject == SOBJ_SEED) {
			mMapTile[tileY][tileX].SubObject = SOBJ_HOED;
			((Toolbar*)UIMANAGER->getFixedUI(GFU_TOOLBAR))->addItem(ITEMCLASS->PARSNIP, PLAYER->addItem(ITEMCLASS->PARSNIP));
		}
	});

	while (mRockList.size() < mRockCount) {
		int tempIndexX = RND->getInt(mTileXCount);
		int tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object == OBJ_NULL) {
			Rock* createRock = new Rock;
			createRock->init(eRockType::RT_NORMAL_2, tempIndexX, tempIndexY);
			curTile->IsCanMove = false;
			curTile->SubObject = SOBJ_ROCK;
			mRockList.insert(make_pair(curTile, createRock));
		}
	}

	return S_OK;
}

void FarmMap::update(void)
{
	Map::update();

	for (mapIterRock iRockList = mRockList.begin(); iRockList != mRockList.end(); iRockList++) {
		iRockList->second->update();
	}

	if (KEYMANAGER->isOnceKeyDown('P')) {
		for (mapIterCrop iCropList = mCropList.begin(); iCropList != mCropList.end(); iCropList++) {
			iCropList->second->upStage();
		}
	}
}

void FarmMap::render(void)
{
	Map::render();
}

void FarmMap::release(void)
{

}

HRESULT ShopMap::init()
{
	Map::init(eLocation::L_SHOP);
	
	CAMERA->setToCenterX(10 * TILE_SIZE);
	CAMERA->setToCenterY(10 * TILE_SIZE);

	return S_OK;
}

void ShopMap::update(void)
{
	Map::update();
}

void ShopMap::render(void)
{
	Map::render();

}

void ShopMap::release(void)
{
	Map::release();
}
