#include "Stdafx.h"
#include "Map.h"
#include "Monster.h"
#include "Environment.h"
#include "Item.h"

void Map::init(string mapKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);
	mCurPalette = MAPPALETTEMANAGER->findPalette(mMapInfo.PaletteKey);
	mPortalList = MAPTILEMANAGER->findPortalList(mapKey);

	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	mPlayerActionFunc = []() {};
	mPlayerGrapFunc = []() {};
	mPlayerMoveFunc = [this](eGameDirection direction) {
		PLAYER->moveTo(direction);
	};

	bReqChangeScene = false;

	mVObjectGroup = new OBJTILE[MAX_OBJECT_COUNT];
	for (int i = 0; i < MAX_OBJECT_COUNT; i++) {
		mVObjectGroup[i] = OBJTILE();
	}

	for (int y = mMapInfo.YCount - 1; y >= 0; y--) {
		for (int x = 0; x < mMapInfo.XCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Object[0] != OBJ_NULL) {
				int groupId = tile.ObjectLevel[0];
				if (groupId == -1) {
					groupId = 0;
				}

				if (mVObjectGroup[groupId].GroupId == -1) {
					mVObjectGroup[groupId].GroupId = tile.ObjectLevel[0];
					mVObjectGroup[groupId].Level = y;
					mVObjectGroup[groupId].Object = tile.Object[0];
				}

				mVObjectGroup[groupId].IndexList.push_back(TINDEX(x, y));
			}
		}
	}

	for (int i = 0; i < mMapInfo.PortalCount; i++) {
		TINDEX a = mPortalList[i].TIndex;
		mPortalMap.insert(make_pair(mPortalList[i].TIndex, mPortalList[i]));
		mMapTile[mPortalList[i].TIndex.Y][mPortalList[i].TIndex.X].SubObject[0] = SOBJ_PORTAL;
	}

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
			if (KEYMANAGER->isStayKeyDown(LEFT_KEY)) {
				PLAYER->changeDirection(GD_LEFT);
				PLAYER->changeActionStat(PS_WALK);
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_LEFT))) {
					mPlayerMoveFunc(GD_LEFT);
				}
			}

			if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
				PLAYER->changeDirection(GD_RIGHT);
				PLAYER->changeActionStat(PS_WALK);
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_RIGHT))) {
					mPlayerMoveFunc(GD_RIGHT);
				}
			}

			if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					PLAYER->changeDirection(GD_UP);
				}
				PLAYER->changeActionStat(PS_WALK);
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_UP))) {
					mPlayerMoveFunc(GD_UP);
				}
			}

			if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					PLAYER->changeDirection(GD_DOWN);
				}
				PLAYER->changeActionStat(PS_WALK);
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_DOWN))) {
					mPlayerMoveFunc(GD_DOWN);
				}
			}
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

	for (int y = getStartY(); y < getEndY(); y++) {
		for (int x = getStartX(); x < getEndX(); x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].render(getMemDc(), getTileRelX(x), getTileRelY(y));
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		int a = PLAYER->getEndIndexY();
		if (mVObjectGroup[i].Level < PLAYER->getEndIndexY()) {
			for (TINDEX tIndex : mVObjectGroup[i].IndexList) {
				auto& tile = mMapTile[tIndex.Y][tIndex.X];
				for (int x = 0; x < OBJ_C; x++) {
					if (tile.Object[x] != OBJ_NULL) {
						mCurPalette[tile.ObjectFrameY[x]][tile.ObjectFrameX[x]].render(getMemDc(), getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
					}
				}
			}
		};
	}

	PLAYER->render();

	for (int i = 0; i < 20; i++) {
		int a = PLAYER->getEndIndexY();
		if (mVObjectGroup[i].Level >= PLAYER->getEndIndexY()) {
			for (TINDEX tIndex : mVObjectGroup[i].IndexList) {
				auto& tile = mMapTile[tIndex.Y][tIndex.X];
				for (int x = 0; x < OBJ_C; x++) {
					if (tile.Object[x] != OBJ_NULL) {
						mCurPalette[tile.ObjectFrameY[x]][tile.ObjectFrameX[x]].render(getMemDc(), getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
					}
				}
			}
		};
	}

#if DEBUG_MODE
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		GDIPLUSMANAGER->render(getMemDc(), mDebugCBitmap, getRelRectF().GetLeft(), getRelRectF().GetTop());

		//player
		GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(PLAYER->getIndexX() * TILE_SIZE), getRelY(PLAYER->getIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(0, 0, 255), 2.0f);
		GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(PLAYER->getAttackIndexX() * TILE_SIZE), getRelY(PLAYER->getAttackIndexY() * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(255, 0, 0), 2.0f);

		vector<TINDEX> player = PLAYER->getAttackIndexList();
		for (vector<TINDEX>::iterator iter = player.begin(); iter != player.end(); iter++) {
			GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(iter->X * TILE_SIZE), getRelY(iter->Y * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(255, 0, 0), 2.0f);
		}

		GDIPLUSMANAGER->drawRectFLine(getMemDc(),PLAYER->getTempMoveRelRectF(PLAYER->getDirection()), Color(255, 0, 255), 2.0f);

		for (int y = getStartY(); y < getEndY(); y++) {
			for (int x = getStartX(); x < getEndX(); x++) {
				auto& tile = mMapTile[y][x];
				if (tile.SubObject[0] != SOBJ_NULL) {
					GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(getRelX(x * TILE_SIZE), getRelY(y * TILE_SIZE), TILE_SIZE, TILE_SIZE), CR_NONE, CR_RED);
				}
			}
		}
	}
#endif
}

void Map::release(void)
{
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

void Map::addObject(TINDEX tIndex) {
	auto& tile = mMapTile[tIndex.Y][tIndex.X];
	if (mVObjectGroup[9].GroupId == -1) {
		mVObjectGroup[9].GroupId = 9;
		mVObjectGroup[9].Level = tIndex.Y;
		mVObjectGroup[9].Object = tile.Object[0];
		mVObjectGroup[9].IndexList.push_back(tIndex);
	}
}

void Map::rebuild(string mapKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);

	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	//SAFE_DELETE(mVObjectGroup);
	mVObjectGroup = new OBJTILE[MAX_OBJECT_COUNT];

	for (int y = mMapInfo.YCount - 1; y > 0; y--) {
		for (int x = 0; x < mMapInfo.XCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Object[0] != OBJ_NULL) {
				int groupId = tile.ObjectLevel[0];
				if (groupId == -1) {
					groupId = 0;
				}

				if (mVObjectGroup[groupId].GroupId == -1) {
					mVObjectGroup[groupId].GroupId = tile.ObjectLevel[0];
					mVObjectGroup[groupId].Level = y;
					mVObjectGroup[groupId].Object = tile.Object[0];
				}

				mVObjectGroup[groupId].IndexList.push_back(TINDEX(x, y));
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(int floor)
{
	Map::init(MAPTILEMANAGER->findMineMapIdToFloor(floor));

	bReqRebuild = false;

	CAMERA->setToCenterX(9 * TILE_SIZE);
	CAMERA->setToCenterY(9 * TILE_SIZE);

	mLadderTileDef = MAPPALETTEMANAGER->findObjectTile(mMapInfo.PaletteKey, OBJ_MINE_LADDER);

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mMonsterList.size() < mMapInfo.MonsterCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->IsCanMove) {
			auto* monster = MonsterFactory::getMonster(RND->getFlag() ? MST_GRUB : MST_SLIME, tempIndexX * TILE_SIZE, tempIndexY * TILE_SIZE);
			curTile->SubObject[0] = SOBJ_MONSTER;
			mMonsterList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), monster));
		}
	}
	while (mRockList.size() < mMapInfo.RockCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->IsCanMove) {
			Rock* rock = new Rock;
			rock->init(eRockType::RT_NORMAL_1, tempIndexX, tempIndexY);
			curTile->SubObject[0] = SOBJ_ROCK;
			curTile->IsCanMove = false;
			mRockList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), rock));
			if (mLadderIndex.X == -1) {
				mLadderIndex = TINDEX(tempIndexX, tempIndexY);
				addObject(TINDEX(tempIndexX, tempIndexY));
			}
		}
	}

	setPlayerActionFunc([this](void) {
		eItemType itemType = PLAYER->getHoldItemType();
		switch (itemType)
		{
			case ITP_WEAPON: {
				vector<TINDEX> indexList = PLAYER->getAttackIndexList();
				for (vector<TINDEX>::iterator iter = indexList.begin(); iter != indexList.end(); iter++) {
					if (mMapTile[iter->Y][iter->X].SubObject[0] == SOBJ_MONSTER) {
						Monster* monster = mMonsterList.find(*iter)->second;
						monster->hit(PLAYER->getPower());
					}
				}
				break;
			}
			case ITP_TOOL: {
				auto key = mRockList.find(PLAYER->getTIndex());
				if (key != mRockList.end()) {
					key->second->hit(PLAYER->getPower());
				}
			}
		}
	});
	setPlayerMoveFunc([this](eGameDirection direction) {
		PLAYER->moveTo(direction);
		TINDEX playerPos = PLAYER->getTIndex();
		tagTile* playerTile = getTile(playerPos);
		if(playerTile->SubObject[0] == SOBJ_ITEM) {
			auto itemTileKey = mItemList.find(playerPos);
			if (itemTileKey != mItemList.end()) {
				Item* item = itemTileKey->second;
				PLAYER->addItem(item->getItemId());
				mItemList.erase(itemTileKey);
			}
		}
	});
	setPlayerGrapFunc([this]() {
		tagTile* playerTile = getTile(PLAYER->getAttackTIndex());
		if (playerTile->Object[0] == OBJ_MINE_LADDER) {
			bReqRebuild = true;
			mReqFloor = mMapInfo.Floor;
		}
	});
}

void MineMap::update(void)
{
	Map::update();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end();) {
		Monster* monster = miMonsterList->second;
		TINDEX keyIndex = miMonsterList->first;

		RectF tempRectF = monster->getCanMoveRectF();
		if (isCollisionTile(tempRectF)) {
			monster->movePatternChange();
			++miMonsterList;
		} else {
			monster->move();
			TINDEX changeIndex = monster->getTIndex();
			if (keyIndex != changeIndex) {
				mMapTile[keyIndex.Y][keyIndex.X].SubObject[0] = SOBJ_NULL;
				mMonsterList.erase(miMonsterList++);
				mMapTile[changeIndex.Y][changeIndex.X].SubObject[0] = SOBJ_MONSTER;
				mMonsterList.insert(make_pair(changeIndex, monster));
			}
			else {
				++miMonsterList;
			}
		};
	}

	for (miRockList = mRockList.begin(); miRockList != mRockList.end();) {
		Rock* curRock = miRockList->second;
		TINDEX keyIndex = miRockList->first;

		if (curRock->isBroken()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			curRock->release();
			SAFE_DELETE(curRock);
			mRockList.erase(miRockList++);

			//temp
			mItemList.insert(make_pair(keyIndex, ITEMMANAGER->findItem(ITEMCLASS->STONE_NORMAL)));
			curTile.SubObject[0] = SOBJ_ITEM;

			if (keyIndex == mLadderIndex) {
				curTile.Object[0] = mLadderTileDef->Object;
				curTile.ObjectFrameX[0] = mLadderTileDef->ObjectFrameX;
				curTile.ObjectFrameY[0] = mLadderTileDef->ObjectFrameY;
				curTile.IsCanMove = false;
			}
			break;
		}
		else {
			curRock->update();
			++miRockList;
		}
	}

	for (miItemList = mItemList.begin(); miItemList != mItemList.end(); miItemList++) {
		(*miItemList).second->update();
	}
}

void MineMap::render(void)
{
	Map::render();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end(); miMonsterList++) {
		(*miMonsterList).second->render();
	}

	for (miRockList = mRockList.begin(); miRockList != mRockList.end(); miRockList++) {
		(*miRockList).second->render();
	}

	for (miItemList = mItemList.begin(); miItemList != mItemList.end(); miItemList++) {
		TINDEX index = (*miItemList).first;
		(*miItemList).second->render(getTileRelX(index.X), getTileRelY(index.Y));
	}
}

void MineMap::release(void)
{
	Map::release();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end(); miMonsterList++) {
		Monster* monster = (*miMonsterList).second;
		monster->release();
		SAFE_DELETE(monster);
	}
	
	mMonsterList.clear();

	for (miRockList = mRockList.begin(); miRockList != mRockList.end(); miRockList++) {
		Rock* rock = (*miRockList).second;
		rock->release();
		SAFE_DELETE(rock);
	}
	
	mRockList.clear();
	mItemList.clear();
}

void MineMap::rebuild(int floor)
{
	Map::rebuild(MAPTILEMANAGER->findMineMapIdToFloor(floor));

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end(); miMonsterList++) {
		Monster* monster = (*miMonsterList).second;
		monster->release();
		SAFE_DELETE(monster);
	}

	for (miRockList = mRockList.begin(); miRockList != mRockList.end(); miRockList++) {
		Rock* rock = (*miRockList).second;
		rock->release();
		SAFE_DELETE(rock);
	}

	mMonsterList.clear();
	mRockList.clear();
	mItemList.clear();

	mLadderIndex = TINDEX();

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mMonsterList.size() < mMapInfo.MonsterCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->IsCanMove) {
			Grub* monster = new Grub;

			curTile->SubObject[0] = SOBJ_MONSTER;
			mMonsterList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), monster));
		}
	}
	while (mRockList.size() < mMapInfo.RockCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->IsCanMove) {
			Rock* rock = new Rock;
			rock->init(eRockType::RT_NORMAL_1, tempIndexX, tempIndexY);
			curTile->SubObject[0] = SOBJ_ROCK;
			curTile->IsCanMove = false;
			mRockList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), rock));
			if (mLadderIndex.X == -1) {
				mLadderIndex = TINDEX(tempIndexX, tempIndexY);
				addObject(TINDEX(tempIndexX, tempIndexY));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////awdww////////

HRESULT FarmMap::init()
{
	Map::init(MAPCLASS->FARM);

	stage = 0;
	mRockCount = 0;
	mTreeCount = 0;

	//CAMERA->setToCenterX(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE);
	//CAMERA->setToCenterY(mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE);

	//PLAYER->changePos(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE, mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE, XS_LEFT, YS_TOP);

	//setSubObjRenderFunc([this](tagTile* tile) {
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
	//});

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
				LOG::e("수확 에러");
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

HRESULT ShopMap::init(const string mapKey, int portalKey)
{
	Map::init(mapKey);

	const TINDEX startIndex = mPortalList[portalKey].TIndex;

	CAMERA->setToCenterX(startIndex.X * TILE_SIZE);
	CAMERA->setToCenterY(startIndex.Y * TILE_SIZE);

	PLAYER->movePosByPortal(startIndex.X * TILE_SIZE, startIndex.Y * TILE_SIZE);

	bReqShopUI = false;

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

vector<string> ShopMap::getSaleItemIdList(void)
{
	return vector<string>();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT HomeMap::init()
{
	Map::init(MAPCLASS->HOME);

	//CAMERA->setToCenterX(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE);
	//CAMERA->setToCenterY(mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE);

	//PLAYER->changePos(mPortalList[PLAYER->getToPortalKey()].X * TILE_SIZE, mPortalList[PLAYER->getToPortalKey()].Y * TILE_SIZE, XS_LEFT, YS_TOP);

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

//////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT TownMap::init()
{
	Map::init(MAPCLASS->TOWN);

	CAMERA->setToCenterX(7 * TILE_SIZE);
	CAMERA->setToCenterY(7* TILE_SIZE);

	return S_OK;
}

void TownMap::update(void)
{
	Map::update();
}

void TownMap::render(void)
{
	Map::render();
}

void TownMap::release(void)
{
}

/////////////////////////////////////////////////

HRESULT LoadMap::init()
{
	Map::init(MAPCLASS->LOAD);

	CAMERA->setToCenterX(0 * TILE_SIZE);
	CAMERA->setToCenterY(7 * TILE_SIZE);

	PLAYER->setAbsX(1 * TILE_SIZE);
	PLAYER->setAbsY(8 * TILE_SIZE);
	setPlayerMoveFunc([this](eGameDirection direction) {
		PLAYER->moveTo(direction);
		tagTile* playerTile = getTile(PLAYER->getTIndex());
		if (playerTile->SubObject[0] == SOBJ_PORTAL) {
			bReqChangeScene = true;
			mReqChangeScene = mPortalMap.find(PLAYER->getTIndex())->second;
		}
	});

	return S_OK;
}

void LoadMap::update(void)
{
	Map::update();
}

void LoadMap::render(void)
{
	Map::render();
}

void LoadMap::release(void)
{
}
