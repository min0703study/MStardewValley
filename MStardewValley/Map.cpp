#include "Stdafx.h"
#include "Map.h"

void Map::init(string mapKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);
	mCurPalette = MAPPALETTEMANAGER->findPalette(mMapInfo.PaletteKey);

	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	mPlayerActionFunc = [](){};
	mPlayerGrapFunc = [](){};
	mPlayerMoveFunc = [this]() {
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

		if (mMapTile[PLAYER->getIndexY()][PLAYER->getIndexX()].SubObject == SOBJ_PORTAL) {
			for (int i = 0; i < mPortalCount; i++) {
				if (mPortalList[i].X == PLAYER->getIndexX() && mPortalList[i].Y == PLAYER->getIndexY()) {
					PLAYER->setToMapKey(mPortalList[i].ToMapKey);
					PLAYER->setToPortalKey(mPortalList[i].ToPortal);
					SCENEMANAGER->changeScene(mPortalList[i].ToSceneName);
				}
			}
		}
	};

	mSubObjRenderFunc = [](tagTile* tile) {};

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
	if (KEYMANAGER->isAllKeysUp(4, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY)) {
		if (!PLAYER->isActing()) {
			PLAYER->changeActionStat(PS_IDLE);
		}
	}
	else {
		mPlayerMoveFunc();
	}

	if (!UIMANAGER->isClickUI()) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			PLAYER->attack();
			mPlayerActionFunc();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			PLAYER->grap();
			mPlayerGrapFunc();
//			mMapTile[PLAYER->getAttackIndexY()][PLAYER->getAttackIndexX()].toString();
		}
	}
}

void Map::render(void)
{
	for (int y = getStartY(); y < getEndY(); y++) {
		for (int x = getStartX(); x < getEndX(); x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
			}

			if (tile.Object != OBJ_NULL) {
				mCurPalette[tile.ObjectFrameY][tile.ObjectFrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
			}

			if (tile.Object2 != OBJ_NULL) {
				mCurPalette[tile.Object2FrameY][tile.Object2FrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
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

void Map::release(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(string mapKey)
{
	Map::init(mapKey);

	mEntranceIndexX = mMapInfo.EnterenceIndex % mMapInfo.XCount;
	mEntranceIndexY = mMapInfo.EnterenceIndex / mMapInfo.YCount;

	CAMERA->setToCenterX(mEntranceIndexX * TILE_SIZE);
	CAMERA->setToCenterY(mEntranceIndexY * TILE_SIZE);

	if (mMapInfo.Floor == 1) {
		mFloor = 1;
		mMineLevel = 1;
		mRockCount = 0;
		mMonsterCount = 0;
	}
	else if (mMapInfo.Floor == 2) {
		mFloor = 2;
		mMineLevel = 1;
		mRockCount = 10;
		mMonsterCount = 2;
	}
	else if (mMapInfo.Floor == 3) {
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
			monster->init("몬스터", 
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
		if (!isCollisionTile((*mViMonster)->getTempMoveAbsRectF())) {
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
	Map::init(MAPCLASS->FARM);

	CAMERA->setToCenterX(10 * TILE_SIZE);
	CAMERA->setToCenterY(10 * TILE_SIZE);

	stage = 0;
	mRockCount = 0;

	mPortalList = new PORTAL[1];
	mPortalList[0].X = 5;
	mPortalList[0].Y = 7;
	mPortalList[0].ToPortal = 0;
	mPortalList[0].ToMapKey = MAPCLASS->Shop;
	mPortalList[0].ToSceneName = "shop";
	mPortalCount = 1;

	mMapTile[7][5].SubObject = SOBJ_PORTAL;

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
		case SOBJ_PORTAL:
			GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(getTileRelX(tile->X), getTileRelY(tile->Y), TILE_SIZE, TILE_SIZE), Color(), Color(100, 255,0,255));
			break;
		}
	});
	setPlayerActionFunc([this](void){
		if (!PLAYER->getHoldItemBox().IsEmpty) {
			PLAYER->useItem();

			Item* holdItem = PLAYER->getHoldItemBox().Item;
			eItemType itemType = holdItem->getItemType();

			int tileX = PLAYER->getAttackIndexX();
			int tileY = PLAYER->getAttackIndexY();

			switch (itemType)
			{
			case ITP_SEED: {
				mMapTile[tileY][tileX].SubObject = SOBJ_SEED;
				Crop* crop = new Crop();
				crop->init(((Seed*)holdItem)->getCropType(), tileX, tileY);
				mCropList.insert(make_pair(&mMapTile[tileY][tileX], crop));
				break;
			}
			case ITP_TOOL: {
				if (holdItem->getItemId() == ITEMCLASS->WATERING_CAN) {
					mMapTile[tileY][tileX].SubObject = SOBJ_HOED_WET;
				}
				else if (holdItem->getItemId() == ITEMCLASS->HOE) {
					mMapTile[tileY][tileX].SubObject = SOBJ_HOED;
				}
				else if (holdItem->getItemId() == ITEMCLASS->PICK) {
					mMapTile[tileY][tileX].SubObject = SOBJ_NULL;
					Crop* crop = mCropList.find(&mMapTile[tileY][tileX])->second;
					crop->release();
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

		tagTile* targetTile = &mMapTile[tileY][tileX];

		if (targetTile->SubObject == SOBJ_SEED) {
			auto mapKey = mCropList.find(targetTile);
			if (mapKey != mCropList.end()) {
				Crop* curCrop = mapKey->second;
				string fruitId = curCrop->harvesting();
				((Toolbar*)UIMANAGER->getFixedUI(GFU_TOOLBAR))->addItem(fruitId, PLAYER->addItem(fruitId));
				mCropList.erase(mapKey);
				SAFE_DELETE(curCrop);
				targetTile->SubObject = SOBJ_HOED;
			}
			else {
				LOG::e("수확 에러");
			}
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
			Crop* curCrop = iCropList->second;
			if (curCrop != nullptr) {
				curCrop->upStage();
			}
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

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT ShopMap::init()
{
	Map::init(MAPCLASS->Shop);
	
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

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT HomeMap::init()
{
	Map::init(MAPCLASS->HOME);

	CAMERA->setToCenterX(10 * TILE_SIZE);
	CAMERA->setToCenterY(10 * TILE_SIZE);

	mPortalList = new PORTAL[1];
	mPortalList[0].X = 3;
	mPortalList[0].Y = 11;
	mPortalList[0].ToPortal = 0;
	mPortalList[0].ToMapKey = MAPCLASS->FARM;
	mPortalList[0].ToSceneName = "farm";
	mPortalCount = 1;

	mMapTile[11][3].SubObject = SOBJ_PORTAL;

	setSubObjRenderFunc([this](tagTile* tile) {
		switch (tile->SubObject) {
		case SOBJ_PORTAL:
			GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(getTileRelX(tile->X), getTileRelY(tile->Y), TILE_SIZE, TILE_SIZE), Color(), Color(100, 255, 0, 255));
			break;
		}
	});

	setPlayerActionFunc([this](void) {
	});

	setPlayerGrapFunc([this](void) {
	});

	return S_OK;
}

void HomeMap::update(void)
{
	Map::update();
}

void HomeMap::render(void)
{
	Map::render();
}

void HomeMap::release(void)
{
}
