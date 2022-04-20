#include "Stdafx.h"
#include "Map.h"
#include "Monster.h"
#include "Environment.h"

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
			if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_LEFT))) {
				PLAYER->moveTo(GD_LEFT);
			}
		}

		if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
			PLAYER->changeDirection(GD_RIGHT);
			PLAYER->changeActionStat(PS_WALK);
			if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_RIGHT))) {
				PLAYER->moveTo(GD_RIGHT);
			}
		}

		if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
			if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
				PLAYER->changeDirection(GD_UP);
			}
			PLAYER->changeActionStat(PS_WALK);
			if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_UP))) {
				PLAYER->moveTo(GD_UP);
			}
		}

		if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
			if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
				PLAYER->changeDirection(GD_DOWN);
			}
			PLAYER->changeActionStat(PS_WALK);
			if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_DOWN))) {
				PLAYER->moveTo(GD_DOWN);
			}
		}
		
		/*
		if (mMapTile[PLAYER->getIndexY()][PLAYER->getIndexX()].SubObject == SOBJ_PORTAL) {
			for (int i = 0; i < mPortalCount; i++) {
				if (mPortalList[i].X == PLAYER->getIndexX() && mPortalList[i].Y == PLAYER->getIndexY()) {
					PLAYER->setToMapKey(mPortalList[i].ToMapKey);
					PLAYER->setToPortalKey(mPortalList[i].ToPortal);
					SCENEMANAGER->changeScene(mPortalList[i].ToSceneName);
					break;
				}
			}
		}
		*/
	};
	mSubObjRenderFunc = [](tagTile* tile) {};

#if	DEBUG_MODE
	GameObject::Init("", 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);
	Bitmap* tempDebugBitmap = GDIPLUSMANAGER->getBlankBitmap(mWidth, mHeight);

	for (int y = 0; y < mTileYCount; y++) {
		for (int x = 0; x < mTileXCount; x++) {
			GDIPLUSMANAGER->drawRectFToBitmap(tempDebugBitmap, RectF(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE), mMapTile[y][x].IsCanMove ? Color(100, 0, 0, 255):  Color(100, 255, 0, 0));
			GDIPLUSMANAGER->drawTextToBitmap(tempDebugBitmap, to_string(y) + " / " + to_string(x), RectFMake(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE), 8.0f, Color(255,255,255));
		}
	}

	GDIPLUSMANAGER->drawGridLineToBitmap(tempDebugBitmap, TILE_SIZE, TILE_SIZE, Color(100, 255, 255, 255));
	mDebugCBitmap = GDIPLUSMANAGER->bitmapToCachedBitmap(getMemDc(), tempDebugBitmap);
#endif
}

void Map::update(void)
{
	if (KEYMANAGER->isAllKeysUp(4, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY)) {
		if (!PLAYER->isActing()) {
			PLAYER->changeActionStat(PS_IDLE);
		}
	} else {
		if (!PLAYER->isActing()) {
			mPlayerMoveFunc();
		}
	}

	if (!UIMANAGER->isActiveUI()) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			PLAYER->attack();
			mPlayerActionFunc();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
			PLAYER->grap();
			mPlayerGrapFunc();
		}
	}
}

void Map::render(void)
{
	bool playerRenderFlag = false;

	/*
	for (int y = getStartY(); y < getEndY(); y++) {
		for (int x = getStartX(); x < getEndX(); x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].render(getMemDc(), getTileRelX(tile.X), getTileRelY(tile.Y));
			}
		}
	}
	for (int y = getStartY(); y < getEndY(); y++) {
		for (int x = getStartX(); x < getEndX(); x++) {
			auto& tile = mMapTile[y][x];
			if (PLAYER->getStartIndexX() == x && PLAYER->getStartIndexY() == y) {
				PLAYER->render();
			}

			for (int i = 0; i < OBJ_C; i++)
				if (tile.Object[i] != OBJ_NULL) {
					if (tile.Object[i] == OBJ_HOED) {
						HOEDSPRITE->getNormalHoed(0, 0)->render(getTileRelX(tile.X), getTileRelY(tile.Y));
					}
					else {
						mCurPalette[tile.ObjectFrameY[i]][tile.ObjectFrameX[i]].render(getMemDc(), getTileRelX(x), getTileRelY(y));
					}

					if (tile.SubObject[i] != SOBJ_NULL) {
						mSubObjRenderFunc(&tile);
					}
				}
		}
	}
	*/
#if DEBUG_MODE
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		GDIPLUSMANAGER->render(getMemDc(), mDebugCBitmap, getRelRectF().GetLeft(), getRelRectF().GetTop());

		//player
		GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(PLAYER->getIndexX() * TILE_SIZE), getRelY(PLAYER->getIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(0, 0, 255), 2.0f);
		GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(PLAYER->getAttackIndexX() * TILE_SIZE), getRelY(PLAYER->getAttackIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(255, 0, 0), 2.0f);

		GDIPLUSMANAGER->drawRectFLine(getMemDc(),PLAYER->getTempMoveRelRectF(PLAYER->getDirection()), Color(255, 0, 255), 2.0f);
	}
#endif
}

bool Map::isCollisionTile(RectF rectF)
{
	int startX = getPtToIndexX(rectF.GetLeft());
	int toX = getPtToIndexX(rectF.GetRight());
	int startY = getPtToIndexY(rectF.GetTop());
	int endY = getPtToIndexY(rectF.GetBottom());

	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= toX; x++) {
			if (!mMapTile[y][x].IsCanMove) {
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

	//mEntranceIndexX = mMapInfo.EnterenceIndex % mMapInfo.XCount;
	//mEntranceIndexY = mMapInfo.EnterenceIndex / mMapInfo.YCount;

	CAMERA->setToCenterX(9 * TILE_SIZE);
	CAMERA->setToCenterY(9 * TILE_SIZE);

	PLAYER->changePos(9 * TILE_SIZE, 9 * TILE_SIZE, XS_LEFT, YS_TOP);

	if (mMapInfo.Floor == 1) {
		mFloor = 1;
		mMineLevel = 1;
		mRockCount = 5;
		mMonsterCount = 3;
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


	/*
	while (mRockList.size() < mRockCount) {
		int tempIndexX = RND->getInt(mTileXCount);
		int tempIndexY = RND->getInt(mTileYCount);
		tagTileDef* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object == OBJ_NULL && curTile->IsCanMove) {
			Rock* createRock = new Rock;
			createRock->init(eRockType::RT_NORMAL_1, tempIndexX, tempIndexY);
			curTile->SubObject = SOBJ_ROCK;
			mRockList.insert(make_pair(curTile, createRock));

			curTile->IsCanMove = false;
		}
	}


	while (mVMonster.size() < mMonsterCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		auto& curTile = mMapTile[tempIndexY][tempIndexX];
		if (curTile.IsCanMove) {
			Grub* monster = new Grub;
			monster->init("����", 
				curTile.X * TILE_SIZE,
				curTile.Y * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE, 
				XS_LEFT, 
				YS_TOP);

			curTile.SubObject = SOBJ_MONSTER;
			mVMonster.push_back(monster);
		}
	}
	setPlayerActionFunc([this](void) {
		eItemType itemType = PLAYER->getHoldItemType();

		int tileX = PLAYER->getAttackIndexX();
		int tileY = PLAYER->getAttackIndexY();

		TileDef& tTile = mMapTile[tileY][tileX];

		if (tTile.SubObject == SOBJ_ROCK) {
			eToolType toolType = PLAYER->getHoldItem<Tool*>()->getToolType();
			switch (toolType)
			{
			case TT_PICK:
				Rock& rock = *(mRockList.find(&tTile)->second);
				rock.hit(PLAYER->getPower());
				break;
			}
		}
	});
	setSubObjRenderFunc([this](tagTile* tile) {
		switch (tile->SubObject) {
		case SOBJ_ROCK:
			mRockList.find(tile)->second->render();
			break;
		case SOBJ_TREE_ATTACK:
			//mTreeList.find(tile)->second->render();
			break;
		}
	});
	*/
}

void MineMap::update(void)
{
	Map::update();
	/*
	for (mapIterRock iRockList = mRockList.begin(); iRockList != mRockList.end();) {
		Rock* curRock = iRockList->second;
		if (curRock->isBroken()) {
			iRockList->first->SubObject = SOBJ_NULL;
			iRockList->first->IsCanMove = true;
			curRock->release();
			SAFE_DELETE(curRock);
			iRockList = mRockList.erase(iRockList);
			break;
		}
		else {
			curRock->update();
			iRockList++;
		}
	}

	for (mViMonster = mVMonster.begin(); mViMonster != mVMonster.end(); mViMonster++) {
		if (!isCollisionTile((*mViMonster)->getTempMoveAbsRectF())) {
			(*mViMonster)->move();
		};
	}
	*/
}

void MineMap::render(void)
{
	Map::render();

	for (mViMonster = mVMonster.begin(); mViMonster != mVMonster.end(); mViMonster++) {
		(*mViMonster)->render();
	}
}

void MineMap::release(void)
{
	Map::release();

}

bool MineMap::isCollisionRock(RectF rectF)
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////awdww////////

HRESULT FarmMap::init()
{
	Map::init(MAPCLASS->FARM);

	stage = 0;
	mRockCount = 0;
	mTreeCount = 0;

	CAMERA->setToCenterX(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE);
	CAMERA->setToCenterY(mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE);

	PLAYER->changePos(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE, mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE, XS_LEFT, YS_TOP);

	setSubObjRenderFunc([this](tagTile* tile) {
		/*
		switch (tile->SubObject) {
		case SOBJ_ROCK:
			//mRockList.find(tile)->second->render();
			break;
		case SOBJ_TREE_ATTACK:
			//mTreeList.find(tile)->second->render();
			break;
		case SOBJ_SEED:
			mCropList.find(tile)->second->render(getTileRelX(tile->X), getTileRelY(tile->Y));
			break;
		case SOBJ_PORTAL:
			GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(getTileRelX(tile->X), getTileRelY(tile->Y), TILE_SIZE, TILE_SIZE), Color(), Color(100, 255,0,255));
			break;
		}
		*/
	});
	setPlayerActionFunc([this](void){
		eItemType itemType = PLAYER->getHoldItemType();

		int tileX = PLAYER->getAttackIndexX();
		int tileY = PLAYER->getAttackIndexY();
		
		/*
		TileDef& tTile = mMapTile[tileY][tileX];

		if (tTile.Object == OBJ_TREE_ATTACK) {
			GDIPLUSMANAGER->drawRectF(getMemDc(), getTileRelX(tileX), getTileRelY(tileY), TILE_SIZE, TILE_SIZE, Color(), Color(100, 255, 0, 0));
			eToolType toolType = PLAYER->getHoldItem<Tool*>()->getToolType();
			switch (toolType)
			{
			case TT_AXE:
				Tree& tree = *(mTreeList.find(&tTile)->second);
				tree.hit(PLAYER->getPower());
				break;
			}
		}
		else if (tTile.SubObject == SOBJ_ROCK) {
			eToolType toolType = PLAYER->getHoldItem<Tool*>()->getToolType();
			switch (toolType)
			{
			case TT_PICK:
				Rock& rock = *(mRockList.find(&tTile)->second);
				rock.hit(PLAYER->getPower());
				break;
			}
		}
		else if (tTile.Terrain == TR_NORMAL) {
			switch (itemType)
			{
			case ITP_SEED: {
				if (!PLAYER->getHoldItemIsNull()) {
					eCropType cropType = PLAYER->getHoldItem<Seed*>()->getCropType();
					if (tTile.Object == OBJ_HOED) {
						PLAYER->useItem();
						tTile.SubObject = SOBJ_SEED;

						Crop* crop = new Crop();
						crop->init(cropType, tileX, tileY);
						mCropList.insert(make_pair(&tTile, crop));
					}
				}
				break;
			}
			case ITP_TOOL: {
				eToolType toolType = PLAYER->getHoldItem<Tool*>()->getToolType();
				switch (toolType)
				{
				case TT_PICK:
					if (tTile.Object == OBJ_HOED) {
						tTile.Object = OBJ_NULL;
						tTile.Object2 = OBJ_NULL;
					}
					break;
				case TT_AXE:
					break;
				case TT_HOE:
					tTile.Object = OBJ_HOED;
					break;
				case TT_WATERING_CAN:
					if (tTile.Object == OBJ_HOED) {
						tTile.Object2 = OBJ_HOED_WET;
					}
					break;
				case TT_END:
				default:
					//!DO NOTHING!
					break;
				}
			}
			default:
				break;
			}
		}
	});
	setPlayerGrapFunc([this](void) {
		int tileX = PLAYER->getAttackIndexX();
		int tileY = PLAYER->getAttackIndexY();

		/*
		tagTileDef* targetTile = &mMapTile[tileY][tileX];


		if (targetTile->SubObject == SOBJ_SEED) {
			auto mapKey = mCropList.find(targetTile);
			if (mapKey != mCropList.end()) {
				Crop* curCrop = mapKey->second;
				string fruitId = curCrop->harvesting();
				PLAYER->addItem(fruitId);
				mCropList.erase(mapKey);
				SAFE_DELETE(curCrop);
				targetTile->SubObject = SOBJ_NULL;
				targetTile->Object = OBJ_NULL;
				targetTile->Object2 = OBJ_NULL;
			}
			else {
				LOG::e("��Ȯ ����");
			}
		}
		*/
	});

	/*
	while (mRockList.size() < mRockCount) {
		int tempIndexX = RND->getInt(mTileXCount);
		int tempIndexY = RND->getInt(mTileYCount);
		tagTileDef* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object == OBJ_NULL && curTile->IsCanMove) {
			Rock* createRock = new Rock;
			createRock->init(eRockType::RT_NORMAL_1, tempIndexX, tempIndexY);
			curTile->SubObject = SOBJ_ROCK;
			mRockList.insert(make_pair(curTile, createRock));

			curTile->IsCanMove = false;
		}
	}

	while (mTreeList.size() < mTreeCount) {
		int tempIndexX = RND->getInt(mTileXCount);
		int tempIndexY = RND->getInt(mTileYCount);
		tagTileDef* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object == OBJ_NULL && curTile->IsCanMove) {
			Tree* createTree = new Tree;
			createTree->init(TTP_NORMAL, tempIndexX, tempIndexY);
			curTile->SubObject = SOBJ_TREE_ATTACK;
			mTreeList.insert(make_pair(curTile, createTree));

			curTile->IsCanMove = false;
		}
	}
	*/
	return S_OK;
}

void FarmMap::update(void)
{
	Map::update();

	for (mapIterRock iRockList = mRockList.begin(); iRockList != mRockList.end();) {
		Rock* curRock = iRockList->second;
		/*
		if (curRock->isBroken()) {
			iRockList->first->SubObject = SOBJ_NULL;
			iRockList->first->IsCanMove = true;
			curRock->release();
			SAFE_DELETE(curRock);
			iRockList = mRockList.erase(iRockList);
			break;
		}
		else {
			curRock->update();
			iRockList++;
		}
		*/
	}

	for (mapIterTree iTreeList = mTreeList.begin(); iTreeList != mTreeList.end(); iTreeList++) {
		iTreeList->second->update();
	}

	for (mapIterTree iTreeList = mTreeList.begin(); iTreeList != mTreeList.end(); iTreeList++) {
		iTreeList->second->update();
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
	openUI = false;

	CAMERA->setToCenterX(10 * TILE_SIZE);
	CAMERA->setToCenterY(10 * TILE_SIZE);

	int tileX = PLAYER->getAttackIndexX();
	int tileY = PLAYER->getAttackIndexY();

	/*
	tagTileDef* targetTile = &mMapTile[tileY][tileX];
	setPlayerGrapFunc([this](void) {
		int tileX = PLAYER->getAttackIndexX();
		int tileY = PLAYER->getAttackIndexY();

		tagTileDef* targetTile = &mMapTile[tileY][tileX];

		if (targetTile->Object == OBJ_SALE_STAND) {
			openUI = true;
		}
	});
	*/
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

	CAMERA->setToCenterX(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE);
	CAMERA->setToCenterY(mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE);

	PLAYER->changePos(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE, mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE, XS_LEFT, YS_TOP);
	
	/*
	setSubObjRenderFunc([this](tagTile* tile) {
		switch (tile->SubObject) {
		case SOBJ_PORTAL:
			GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(getTileRelX(tile->X), getTileRelY(tile->Y), TILE_SIZE, TILE_SIZE), Color(), Color(100, 255, 0, 255));
			break;
		}
	});
	*/
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
