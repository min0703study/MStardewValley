#include "Stdafx.h"
#include "Map.h"
#include "Monster.h"
#include "Environment.h"
#include "Item.h"

void Map::init(string mapKey, int portalKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	
	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	GameObject::Init("", 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);

	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);
	mCurPalette = MAPPALETTEMANAGER->findPalette(mMapInfo.PaletteKey);
	mPortalList = MAPTILEMANAGER->findPortalList(mapKey);

	if (CAMERA->getWidth() > mWidth) {
		bFixedXCamera = true;
		CAMERA->setToCenterX(mWidth / 2.0f);
	}
	else {
		bFixedXCamera = false;
	}
	if (CAMERA->getHeight() > mHeight) {
		bFixedYCamera = true;
		CAMERA->setToCenterY(mHeight / 2.0f);
	}
	else {
		bFixedYCamera = false;
	}

	mPlayerActionFunc = []() {};
	mPlayerGrapFunc = []() {};
	mPlayerMoveFunc = [this](eGameDirection direction) {
		PLAYER->moveTo(direction);
		if (!bFixedXCamera) {
			CAMERA->setToCenterX(PLAYER->getAbsX());
			if (CAMERA->getX() < 0) {
				CAMERA->setX(0);
			}
			if (CAMERA->getX() + CAMERA->getWidth() > mWidth) {
				CAMERA->setX(mWidth - CAMERA->getWidth());
			}
		}
		if (!bFixedYCamera) {
			CAMERA->setToCenterY(PLAYER->getAbsY());

			if (CAMERA->getY() < 0) {
				CAMERA->setY(0);
			}

			if (CAMERA->getY() + CAMERA->getHeight() > mHeight) {
				CAMERA->setY(mHeight - CAMERA->getHeight());
			}
		}
	};
	mPlayerMoveAfterFunc = [this]() {
		TINDEX playerIndex = PLAYER->getTIndex();
		tagTile* playerTile = getTile(PLAYER->getTIndex());
		if (bInitPortal) {
			if (playerIndex != mStartIndex) {
				bInitPortal = false;
			}
		} else {
			if (playerTile->SubObject[0] == SOBJ_PORTAL) {
				bReqChangeScene = true;
				mReqChangeScene = mPortalMap.find(playerIndex)->second;
			}
		}
	};

	bReqChangeScene = false;

	mVObjectGroup = new vector<OBJTILE>[mTileYCount];

	for (int y = mMapInfo.YCount - 1; y >= 0; y--) {
		for (int x = 0; x < mMapInfo.XCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Object[0] != OBJ_NULL) {
				auto& vObjLevel = mVObjectGroup[y];
				int groupId = tile.ObjectLevel[0];
				bool isAreadyIn = false;

				if (groupId == -1) {
					groupId = 0;
				}

				for (auto iObj = vObjLevel.begin(); iObj != vObjLevel.end(); iObj++) {
					if (iObj->GroupId == groupId) {
						iObj->IndexList.push_back(TINDEX(x, y));
						isAreadyIn = true;
						break;
					}
				}

				if (!isAreadyIn) {
					OBJTILE objTile;
					objTile.GroupId = tile.ObjectLevel[0];
					objTile.Level = y;
					objTile.Object = tile.Object[0];
					objTile.IndexList.push_back(TINDEX(x, y));
					vObjLevel.push_back(objTile);
				}
			}
		}
	}

	for (int i = 0; i < mMapInfo.PortalCount; i++) {
		mPortalMap.insert(make_pair(mPortalList[i].TIndex, mPortalList[i]));
		mMapTile[mPortalList[i].TIndex.Y][mPortalList[i].TIndex.X].SubObject[0] = SOBJ_PORTAL;
	}

	if (portalKey != -1) {
		bInitPortal = true;

		mStartIndex = mPortalList[portalKey].TIndex;
		PLAYER->setAbsXYToTile(mStartIndex.X, mStartIndex.Y);
		if (!bFixedXCamera) {
			CAMERA->setToCenterX(PLAYER->getAbsX());
			if (CAMERA->getX() < 0) {
				CAMERA->setX(0);
			}
			if (CAMERA->getX() + CAMERA->getWidth() > mWidth) {
				CAMERA->setX(mWidth - CAMERA->getWidth());
			}
		}
		if (!bFixedYCamera) {
			CAMERA->setToCenterY(PLAYER->getAbsY());

			if (CAMERA->getY() < 0) {
				CAMERA->setY(0);
			}
			if (CAMERA->getY() + CAMERA->getHeight() > mHeight) {
				CAMERA->setY(mHeight - CAMERA->getHeight());
			}
		}
	}

#if	DEBUG_MODE
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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		PLAYER->attackAni();
		mPlayerActionFunc();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		PLAYER->grapAni();
		mPlayerGrapFunc();
	}

	if (!PLAYER->isActing()) {
		if (KEYMANAGER->isAllKeysUp(4, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY)) {
			PLAYER->changeActionStat(PS_IDLE);
		} else {
			eGameDirection aniDirection = GD_END;
			eGameDirection moveDirection = GD_END;

			if (KEYMANAGER->isStayKeyDown(LEFT_KEY)) {
				aniDirection = GD_LEFT;
				moveDirection = GD_LEFT;
			}

			if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
				aniDirection = GD_RIGHT;
				moveDirection = GD_RIGHT;
			}

			if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					aniDirection = GD_UP;
				}
				moveDirection = GD_UP;
			}

			if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					aniDirection = GD_DOWN;
				}
				moveDirection = GD_DOWN;
			}

			if (aniDirection != GD_END) {
				PLAYER->changeDirection(aniDirection);
				PLAYER->changeActionStat(PS_WALK);
			}

			if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(moveDirection))) {
				mPlayerMoveFunc(moveDirection);
				mPlayerMoveAfterFunc();
			}
		}
	}
}

void Map::render(void)
{
	bool playerRenderFlag = false;

	int startY = CAMERA->getY() / TILE_SIZE;
	int endY = startY + CAMERA->getYTileCount();

	int startX = CAMERA->getX() / TILE_SIZE;
	int endX = startX + CAMERA->getXTileCount();

	for (int y = startY; y < endY; y++) {
		if (y < 0 || y >= mTileYCount) continue;
		for (int x = startX; x < endX; x++) {
			if (x < 0 || x >= mTileXCount) continue;
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].renderMap(getTileRelX(x), getTileRelY(y));
			}
		}
	}

	int playerIndex = PLAYER->getEndIndexY() - 1;
	for (int y = 0; y < mTileYCount; y++) {
		if (y == playerIndex) { PLAYER->render(); };
		for (auto iter = mVObjectGroup[y].begin(); iter != mVObjectGroup[y].end(); iter++) {
			for (TINDEX tIndex : iter->IndexList) {
				auto& tile = mMapTile[tIndex.Y][tIndex.X];
				for (int x = 0; x < OBJ_C; x++) {
					if (tile.Object[x] != OBJ_NULL) {
						mCurPalette[tile.ObjectFrameY[x]][tile.ObjectFrameX[x]].render(getMemDc(), getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
					}
				}
			}
		}
	}

#if DEBUG_MODE
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		GDIPLUSMANAGER->render(getMemDc(), mDebugCBitmap, getRelRectF().GetLeft(), getRelRectF().GetTop());

		//player
		GDIPLUSMANAGER->drawRectFRelTile(getMemDc(), PLAYER->getTIndex(), CR_A_RED);
		if (KEYMANAGER->isStayKeyDown('T')) {
			vector<TINDEX> player = PLAYER->getAttackIndexList();
			for (vector<TINDEX>::iterator iter = player.begin(); iter != player.end(); iter++) {
				GDIPLUSMANAGER->drawRectFLine(getMemDc(), RectFMake(getRelX(iter->X * TILE_SIZE), getRelY(iter->Y * TILE_SIZE), TILE_SIZE, TILE_SIZE), Color(255, 0, 0), 2.0f);
			}
		} 
		else {
			GDIPLUSMANAGER->drawRectFRelTile(getMemDc(), PLAYER->getAttackTIndex(), CR_NONE, CR_RED);
		}

		GDIPLUSMANAGER->drawRectFLine(getMemDc(),PLAYER->getTempMoveRelRectF(PLAYER->getDirection()), Color(255, 0, 255), 2.0f);

		for (int y = 0; y < mTileYCount; y++) {
			if (y == playerIndex) { PLAYER->render(); };
			for (auto iter = mVObjectGroup[y].begin(); iter != mVObjectGroup[y].end(); iter++) {
				for (TINDEX tIndex : iter->IndexList) {
					GDIPLUSMANAGER->drawTextRelTile(getMemDc(), to_wstring(y), tIndex, CR_BLACK);
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
	if (!getAbsRectF().Contains(rectF)) return true;
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
	
	OBJTILE objTile;
	objTile.GroupId = 19;
	objTile.Level = tIndex.Y;
	objTile.Object = tile.Object[0];
	objTile.IndexList.push_back(tIndex);

	mVObjectGroup[tIndex.Y].push_back(objTile);
}

void Map::rebuild(string mapKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);

	for (int y = 0; y < mTileYCount; y++) {
		mVObjectGroup[y].clear();
		SAFE_DELETE(mVObjectGroup);
	}

	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;
	
	mVObjectGroup = new vector<OBJTILE>[mTileYCount];


	for (int y = mMapInfo.YCount - 1; y >= 0; y--) {
		for (int x = 0; x < mMapInfo.XCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Object[0] != OBJ_NULL) {
				auto& vObjLevel = mVObjectGroup[y];
				int groupId = tile.ObjectLevel[0];
				bool isAreadyIn = false;

				if (groupId == -1) {
					groupId = 0;
				}

				for (auto iObj = vObjLevel.begin(); iObj != vObjLevel.end(); iObj++) {
					if (iObj->GroupId == groupId) {
						iObj->IndexList.push_back(TINDEX(x, y));
						isAreadyIn = true;
						break;
					}
				}

				if (!isAreadyIn) {
					OBJTILE objTile;
					objTile.GroupId = tile.ObjectLevel[0];
					objTile.Level = y;
					objTile.Object = tile.Object[0];
					objTile.IndexList.push_back(TINDEX(x, y));
					vObjLevel.push_back(objTile);
				}
			}
		}
	}
}

void Map::effectSound(eSoundType type) {
	switch (type)
	{
	case SDT_WALK: {
		tagTile* curTile = getTile(PLAYER->getTIndex());
		switch (curTile->Terrain)
		{
		case TR_WOOD:
			//if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->StepWood)) {
				//SOUNDMANAGER->play(SOUNDCLASS->StepWood);
			//}
			break;
		default:
			break;
		}
		//SOUNDMANAGER->play(curTile->Terrain);
		break;
	}

	case SDT_ACTION:
		break;
	case SDT_END:
		break;
	default:
		break;
	}

};

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(int floor)
{
	Map::init(MAPTILEMANAGER->findMineMapIdToFloor(floor), 0);

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

	if (floor == 1) {
		mLadderIndex = TINDEX(9, 9);
		addObject(TINDEX(9, 9));
	}

	setPlayerActionFunc([this](void) {
		eItemType itemType = PLAYER->getHoldItemType();
		switch (itemType)
		{
			case ITP_WEAPON: {
				PLAYER->attackAni();
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
				PLAYER->attackAni();
				auto key = mRockList.find(PLAYER->getAttackTIndex());
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
			mReqFloor = mMapInfo.Floor + 1;
		}
	});
}

void MineMap::update(void)
{
	Map::update();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end();) {
		Monster* monster = miMonsterList->second;
		TINDEX keyIndex = miMonsterList->first;

		if (monster->isDie()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			monster->release();
			SAFE_DELETE(monster);
			mMonsterList.erase(miMonsterList++);

			continue;
		}

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

	for (miItemList = mItemList.begin(); miItemList != mItemList.end(); ++miItemList) {
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
		//(*miItemList).second->render(getTileRelX(index.X), getTileRelY(index.Y));
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
}

/////////////////////////////////////////////////////////////////////////////////////////awdww////////

HRESULT FarmMap::init(const string mapKey, int portalKey)
{
	Map::init(mapKey, portalKey);

	mRockCount = 10;
	mTreeCount = 0;

	int tempIndexX = 0;
	int tempIndexY = 0;

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
		}
	}

	setPlayerActionFunc([this](void){
		const Item* holdItem = PLAYER->getHoldItem();
		if (holdItem != nullptr) {
			TINDEX attackIndex = PLAYER->getAttackTIndex();

			switch (holdItem->getItemType())
			{
			case ITP_SEED: {
				TINDEX indexTile = PLAYER->getAttackTIndex();
				tagTile* attackTile = getTile(indexTile);
				if (attackTile->Terrain == TR_NORMAL) {
					PLAYER->useItem();
					attackTile->SubObject[0] = SOBJ_CROP;

					Crop* crop = new Crop();
					crop->init(((Seed*)holdItem)->getCropType(), attackIndex.X, attackIndex.Y);
					mCropList.insert(make_pair(indexTile, crop));
				}
				break;
			}
			case ITP_TOOL: {
				auto key = mRockList.find(PLAYER->getAttackTIndex());
				if (key != mRockList.end()) {
					key->second->hit(PLAYER->getPower());
				}
				break;
			}
			}
		}
	});

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
	setPlayerGrapFunc([this](void) {
		TINDEX attackIndex = PLAYER->getAttackTIndex();
		tagTile* attackTile = getTile(attackIndex);
		if (attackTile->SubObject[0] == SOBJ_CROP) {
			auto key = mCropList.find(attackIndex);
			if (key != mCropList.end()) {
				PLAYER->harvesting(key->second->harvesting());
			}
		}
	});

	return S_OK;
}

void FarmMap::update(void)
{
	Map::update();

	for (mapIterCrop iCropList = mCropList.begin(); iCropList != mCropList.end();) {
		Crop* curCrop = iCropList->second;
		if (curCrop->isHarvested()) {
			curCrop->release();
			mCropList.erase(iCropList++);
		}
		else {
			curCrop->update();
			++iCropList;
		}
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

			mItemList.insert(make_pair(keyIndex, ITEMMANAGER->findItemReadOnly(ITEMCLASS->STONE_NORMAL)));
			curTile.SubObject[0] = SOBJ_ITEM;
			break;
		}
		else {
			curRock->update();
			++miRockList;
		}
	}


	for (mapIterTree iTreeList = mTreeList.begin(); iTreeList != mTreeList.end(); ++iTreeList) {
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

	for (miRockList = mRockList.begin(); miRockList != mRockList.end(); miRockList++) {
		(*miRockList).second->render();
	}

	for (miCropList = mCropList.begin(); miCropList != mCropList.end(); ++miCropList) {
		TINDEX index = (*miCropList).first;
		(*miCropList).second->render();
	}

	for (miItemList = mItemList.begin(); miItemList != mItemList.end(); miItemList++) {
		TINDEX index = (*miItemList).first;
		(*miItemList).second->render();
	}
}

void FarmMap::release(void)
{
	Map::release();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT ShopMap::init(const string mapKey, int portalKey)
{
	Map::init(mapKey, portalKey);
	bReqSaleListUI = false;

	mShopType = mapKey == MAPCLASS->SHOP_SEED ? eShopType::SPT_PIERRE_SHOP : eShopType::SPT_GILL_SHOP;

	setPlayerGrapFunc([this](void) {
		tagTile* targetTile = getTile(PLAYER->getAttackTIndex());

		if (targetTile->Object[0] == OBJ_SALE_STAND) {
			bReqSaleListUI = true;
		}
	});

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
	vector<string> saleList;

	if (mShopType == eShopType::SPT_PIERRE_SHOP) {
		saleList.push_back(ITEMCLASS->PARSNIP_SEED);
		saleList.push_back(ITEMCLASS->POTATO_SEED);
		saleList.push_back(ITEMCLASS->BEEN_SEED);
		saleList.push_back(ITEMCLASS->CAULIFLOWER_SEED);
		saleList.push_back(ITEMCLASS->PARSNIP_SEED);
		saleList.push_back(ITEMCLASS->POTATO_SEED);
	}
	else if (mShopType == eShopType::SPT_GILL_SHOP) {
		saleList.push_back(ITEMCLASS->WOODEN_BLADE);
		saleList.push_back(ITEMCLASS->IRON_DIRCT);
		saleList.push_back(ITEMCLASS->PIRATES_SWORD);
		saleList.push_back(ITEMCLASS->WOOD_MALLET);
		saleList.push_back(ITEMCLASS->BONE_SWORD);
		saleList.push_back(ITEMCLASS->INSECT_HEAD);
	}

	return saleList;
}

ImageGp* ShopMap::getSaleNpcPortraitImg(void)
{
	return NPCSPRITE->getPortraits(eNpcs::NPC_PIERRE)[eNpcPortraitsType::NPT_IDLE];
}

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT HomeMap::init(const string mapKey, int portalKey)
{
	Map::init(mapKey, portalKey);

	if (portalKey == -1) {
		PLAYER->setAbsXYToTile(9, 11);
	}

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

HRESULT TownMap::init(string mapKey, int portalKey)
{
	Map::init(mapKey, portalKey);
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

HRESULT LoadMap::init(const string mapKey, int portalKey)
{
	Map::init(mapKey, portalKey);
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
