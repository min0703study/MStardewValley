#include "Stdafx.h"
#include "Map.h"
#include "Monster.h"
#include "Environment.h"
#include "Item.h"
#include "CraftObject.h"

void Map::init(string mapKey)
{
	mMapInfo = MAPTILEMANAGER->findInfo(mapKey);
	
	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	mTileAllCount = mTileXCount * mTileYCount;

	GameObject::Init("", 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);

	mMapTile = MAPTILEMANAGER->findMapTile(mapKey);
	mCurPalette = MAPPALETTEMANAGER->findPalette(mMapInfo.PaletteKey);
	mPortalList = MAPTILEMANAGER->findPortalList(mapKey);

	bFixedXCamera = CAMERA->getWidth() > mWidth;
	bFixedYCamera = CAMERA->getHeight() > mHeight;

	mRenderSubObj = [this](int level) {};

	mPlantCropFunc = [this](eCropType cropType, TINDEX tIndex) { return nullptr; };
	mCraftObjectPlace = [this](eCraftablesType craftablesType, TINDEX tIndex) { };

	mAttackRockFunc = [this](TINDEX index) { return nullptr;};
	mAttackCraftObjectFunc = [this](TINDEX index) { return nullptr;};
	mAttackTreeFunc = [this](TINDEX index) {return nullptr;};
	mAttackWeedFunc = [this](TINDEX index) {return nullptr;};
	mAttackMonsterFunc = [this](TINDEX index) {return nullptr;};
	mUseWeteringCanFunc = [this](TINDEX index) {return nullptr;};

	bReqChangeScene = false;
	bReqShowEventBox = false;

	mVObjectGroup = new vector<OBJTILE>[mTileYCount];

	int tempList[MAX_OBJECT_COUNT] = {0, };

	for (int y = mMapInfo.YCount - 1; y >= 0; y--) {
		for (int x = 0; x < mMapInfo.XCount; x++) {
			auto& tile = mMapTile[y][x];
			if (tile.Object[0] != OBJ_NULL) {
				int groupId = tile.ObjectLevel[0];

				if (groupId == -1) {
					groupId = 0;
				}

				if (tempList[groupId] == 0) {
					tempList[groupId] = y;
				}

				bool isAreadyIn = false;
				auto& vObjLevel = mVObjectGroup[tempList[groupId]];

				for (auto iObj = vObjLevel.begin(); iObj != vObjLevel.end(); iObj++) {
					if (iObj->GroupId == groupId) {
						iObj->IndexList.push_back(TINDEX(x, y));
						isAreadyIn = true;
						break;
					}
				}

				if (!isAreadyIn) {
					OBJTILE objTile;
					objTile.GroupId = groupId;
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

	mPlayerGrapFunc = []() {};
	mPlayerMoveFunc = [this](eGameDirection direction) {
		PLAYER->move(direction);

		switch (getTile(PLAYER->getTIndex())->Terrain) {
		case TR_WOOD:
			EFFECTMANAGER->playRegularSound(eEffectSoundType::EST_WALK_WOOD);
			break;
		case TR_NORMAL:
			EFFECTMANAGER->playRegularSound(eEffectSoundType::EST_WALK_NORMAL);
			break;
		case TR_GRASS:
			EFFECTMANAGER->playRegularSound(eEffectSoundType::EST_WALK_GRASS);
			break;
		case TR_STONE:
			EFFECTMANAGER->playRegularSound(eEffectSoundType::EST_WALK_STONE);
			break;
		}

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
		if (!bReqChangeScene) {
			TINDEX pIndex = PLAYER->getAttackTIndex();
			tagTile* pTile = getTile(pIndex);

			if (pTile->SubObject[0] == SOBJ_PORTAL) {
				bReqChangeScene = true;
				mReqChangeScenePortal = mPortalMap.find(pIndex)->second;
			}
		}

	};

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
	//action
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		PLAYER->changeActionAni();
		const Item* holdItem = PLAYER->getHoldItem();
		if (holdItem != nullptr) {
			eItemType playerItemType = holdItem->getItemType();

			if (playerItemType == ITP_WEAPON) {
				vector<TINDEX> indexList = PLAYER->getAttackIndexList();
				for (vector<TINDEX>::iterator iter = indexList.begin(); iter != indexList.end(); iter++) {
					auto& curIndex = mMapTile[iter->Y][iter->X];
					if (curIndex.SubObject[0] == SOBJ_WEED) {
						EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_ATTACK_WEED);
						EFFECTMANAGER->playEffectOneTime(iter->X * TILE_SIZE, iter->Y * TILE_SIZE, eEffectAniType::EAT_WEED_CRUSH);
						Weed* weed = mAttackWeedFunc(*iter);
						weed->hit();
						PLAYER->useHoldItem();
					}

					if (curIndex.SubObject[0] == SOBJ_MONSTER) {
						EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_USE_WEAPON);
						Monster* monster = mAttackMonsterFunc(*iter);
						monster->hit(PLAYER->getWeaponPower());
						PLAYER->useHoldItem();
					}
				}
			}
			else if (playerItemType == ITP_CRAFTING) {
				TINDEX attackIndex = PLAYER->getAttackTIndex();
				tagTile* attackTile = getTile(attackIndex);
				mCraftObjectPlace(((Craftable*)holdItem)->getCraftingType(), attackIndex);
				
				attackTile->SubObject[0] = SOBJ_CRAFT_OBJ;
				attackTile->IsCanMove = false;

				PLAYER->useHoldItem();
			} 
			else {
				TINDEX attackIndex = PLAYER->getAttackTIndex();
				tagTile* attackTile = getTile(attackIndex);
				switch (holdItem->getItemType())
				{
				case ITP_SEED: {
					if (attackTile->Terrain == TR_NORMAL && attackTile->Object[0] == OBJ_HOED) {
						attackTile->SubObject[0] = SOBJ_CROP;
						mPlantCropFunc(((Seed*)holdItem)->getCropType(), attackIndex);
					}
					break;
				}
				case ITP_TOOL: {
					switch (((Tool*)holdItem)->getToolType()) {
					case TT_PICK: {
						if (attackTile->SubObject[0] == SOBJ_ROCK) {
							Rock* rock = mAttackRockFunc(attackIndex);

							if (rock != nullptr) {
								EFFECTMANAGER->playEffectOneTime(attackIndex.X * TILE_SIZE, attackIndex.Y * TILE_SIZE, eEffectAniType::EAT_ROCK_CRUSH);
								EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_ATTACK_ROCK);

								rock->hit(PLAYER->getToolPower());
								PLAYER->useHoldItem();
							}
						}

						if (attackTile->SubObject[0] == SOBJ_CRAFT_OBJ) {
							CraftObject* craftObject = mAttackCraftObjectFunc(attackIndex);
							if (craftObject != nullptr) {
								EFFECTMANAGER->playEffectOneTime(attackIndex.X * TILE_SIZE, attackIndex.Y * TILE_SIZE, eEffectAniType::EAT_ROCK_CRUSH);
								EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_ATTACK_ROCK);

								attackTile->SubObject[0] = SOBJ_NULL;
								attackTile->IsCanMove = true;

								craftObject->hit();
								PLAYER->useHoldItem();
							}
						}

						break;
					}
					case TT_AXE: {
						if (attackTile->SubObject[0] == SOBJ_TREE_ATTACK) {
							Tree* tree = mAttackTreeFunc(attackIndex);
							if (tree != nullptr) {
								EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_ATTACK_TREE);
								tree->hit(PLAYER->getToolPower());
							}
						}
						break;
					}
					case TT_HOE: {
						EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_USE_HOE);
						attackTile->Object[0] = OBJ_HOED;
						addObject(attackIndex);
						break;
					}
					case TT_WATERING_CAN: {
						EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_USE_WATERING_CAN);
						EFFECTMANAGER->playEffectOneTime(attackIndex.X * TILE_SIZE, attackIndex.Y * TILE_SIZE, eEffectAniType::EAT_USE_WATERING_CAN);
						attackTile->Object[1] = OBJ_HOED_WET;
						if (attackTile->SubObject[0] == SOBJ_CROP) {
							Crop* crop = mUseWeteringCanFunc(attackIndex);
							if (crop != nullptr) {
								crop->upStage();
							}
						}
						break;
					}
					};
				}
				}
			}
		}
	}

	//grap
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		PLAYER->changeGrapAni();
		mPlayerGrapFunc();
	}

	//move
	if (!PLAYER->isActing()) {
		if (KEYMANAGER->isAllKeysUp(4, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY)) {
			PLAYER->changeActionStat(PS_IDLE);
		} else {
			eGameDirection aniDirection = GD_END;

			if (KEYMANAGER->isStayKeyDown(LEFT_KEY)) {
				aniDirection = GD_LEFT;
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_LEFT))) {
					mPlayerMoveFunc(GD_LEFT);
					mPlayerMoveAfterFunc();
				}
			}

			if (KEYMANAGER->isStayKeyDown(RIGHT_KEY)) {
				aniDirection = GD_RIGHT;
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_RIGHT))) {
					mPlayerMoveFunc(GD_RIGHT);
					mPlayerMoveAfterFunc();
				}
			}

			if (KEYMANAGER->isStayKeyDown(UP_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					aniDirection = GD_UP;
				}
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_UP))) {
					mPlayerMoveFunc(GD_UP);
					mPlayerMoveAfterFunc();
				}
			}

			if (KEYMANAGER->isStayKeyDown(DOWN_KEY)) {
				if (KEYMANAGER->isAllKeysUp(2, LEFT_KEY, RIGHT_KEY)) {
					aniDirection = GD_DOWN;
				}
				if (!isCollisionTile(PLAYER->getTempMoveAbsRectF(GD_DOWN))) {
					mPlayerMoveFunc(GD_DOWN);
					mPlayerMoveAfterFunc();
				}
			}

			if (aniDirection != GD_END) {
				PLAYER->changeDirection(aniDirection);
				PLAYER->changeActionStat(PS_WALK);
			}
		}
	}
}

void Map::render(void)
{
	bool playerRenderFlag = false;

	int startY = (CAMERA->getY()) / TILE_SIZE;
	int endY = startY + CAMERA->getYTileCount();

	int startX = CAMERA->getX() / TILE_SIZE;
	int endX = startX + CAMERA->getXTileCount();

	for (int y = startY; y < endY; y++) {
		if (y < 0 || y >= mTileYCount) continue;
		for (int x = startX; x < endX; x++) {
			if (x < 0 || x >= mTileXCount) continue;
			auto& tile = mMapTile[y][x];
			if (tile.Terrain != TR_NULL) {
				mCurPalette[tile.TerrainFrameY][tile.TerrainFrameX].render(getTileRelX(x), getTileRelY(y));
			}
		}
	}

	int playerIndex = PLAYER->getEndIndexY();

	for (int y = 0; y < mTileYCount; y++) {
		for (auto iter = mVObjectGroup[y].begin(); iter != mVObjectGroup[y].end(); iter++) {
			for (TINDEX tIndex : iter->IndexList) {
				auto& tile = mMapTile[tIndex.Y][tIndex.X];
				for (int x = 0; x < OBJ_C; x++) {
					if (tile.Object[x] != OBJ_NULL) {
						if (tile.Object[x] == OBJ_HOED) {
							HOEDSPRITE->getNormalHoed(0, 0)->render(getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
						} else if (tile.Object[x] == OBJ_HOED_WET) {
							HOEDSPRITE->getWetHoed(0, 0)->render(getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
						}
						else {
							mCurPalette[tile.ObjectFrameY[x]][tile.ObjectFrameX[x]].render(getTileRelX(tIndex.X), getTileRelY(tIndex.Y));
						}
					}
				}
			}
		}

		mRenderSubObj(y);
		
		if (y == playerIndex) { 
			EFFECTMANAGER->render();
			PLAYER->render(); 
		};
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

void Map::inToPlayer(int portalKey)
{
	if (portalKey != -1) {
		mStartIndex = mPortalList[portalKey].StartIndex;

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
		else {
			CAMERA->setToCenterX(mWidth / 2.0f);
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
		else {
			CAMERA->setToCenterY(mHeight / 2.0f);
		}
	}
}

void Map::inToPlayer(TINDEX tIndex)
{
	mStartIndex = tIndex;

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
	else {
		CAMERA->setToCenterX(mWidth / 2.0f);
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
	else {
		CAMERA->setToCenterY(mHeight / 2.0f);
	}
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

	mTileXCount = mMapInfo.XCount;
	mTileYCount = mMapInfo.YCount;

	GameObject::Init("", 0.0f, 0.0f, TILE_SIZE * mTileXCount, TILE_SIZE * mTileYCount, XS_LEFT, YS_TOP);

	for (int y = 0; y < mTileYCount; y++) {
		mVObjectGroup[y].clear();
	}
	
	SAFE_DELETE_ARRAY(mVObjectGroup);

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

//////////////////////////////////////////////////////////////////////////////////////////////////

void MineMap::init(int floor)
{
	Map::init(MAPTILEMANAGER->findMineMapIdToFloor(floor));

	bReqRebuild = false;

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
			rock->init((eRockType)RND->getInt(eRockType::RT_END), tempIndexX, tempIndexY);
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

	mPickUpItemFunc = [this](TINDEX attackIndex) {
		auto key = mItemList.find(attackIndex);
		if (key != mItemList.end()) {
			return key->second;
		}
	};

	mAttackRockFunc = [this](TINDEX attackIndex) {
		auto key = mRockList.find(attackIndex);
		if (key != mRockList.end()) {
			return key->second;
		}
	};

	mAttackMonsterFunc = [this](TINDEX attackIndex) {
		auto key = mMonsterList.find(attackIndex);
		if (key != mMonsterList.end()) {
			return key->second;
		}
	};

	setPlayerGrapFunc([this]() {
		tagTile* playerTile = getTile(PLAYER->getAttackTIndex());
		if (playerTile->Object[0] == OBJ_MINE_LADDER) {
			bReqRebuild = true;
			mReqFloor = mMapInfo.Floor + 1;
			EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_LADDER_DOWN);
		}
	});

	setRenderSubObj([this](int level) {
		if (level == 0) {
			miRItemList = mItemList.begin();
			miRRockList = mRockList.begin();
		}

		for (; miRItemList != mItemList.end(); ++miRItemList) {
			if (miRItemList->first.Y != level) break;
			DropItem* dItem = (*miRItemList).second;
			if (dItem->IsPickUp) continue;
			dItem->TargetItem->render(getRelX(dItem->CurX), getRelY(dItem->CurY));
		}

		for (; miRRockList != mRockList.end(); ++miRRockList) {
			if (miRRockList->first.Y != level) break;
			(*miRRockList).second->render();
		}
	});
}

void MineMap::update(void)
{
	Map::update();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end();) {
		Monster* monster = miMonsterList->second;
		TINDEX keyIndex = miMonsterList->first;
		
		//죽었는지 검사
		if (monster->isDie()) {
			EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_MONSTER_DEAD);
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			monster->release();
			SAFE_DELETE(monster);
			mMonsterList.erase(miMonsterList++);
		}
		else {
			monster->update();

			RectF tempRectF = monster->getCanMoveRectF();
			if (isCollisionTile(tempRectF)) {
				monster->movePatternChange();
				++miMonsterList;
			}
			else {
				monster->move();

				if (PLAYER->getAbsRectF().Intersect(monster->getAbsRectF())) {
					EFFECTMANAGER->playRegularSound(eEffectSoundType::EST_PLAYER_HIT);
					PLAYER->hit(monster->attack());
				}

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
	}

	for (miRockList = mRockList.begin(); miRockList != mRockList.end();) {
		Rock* curRock = miRockList->second;
		TINDEX keyIndex = miRockList->first;

		if (curRock->isBroken()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;

			mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(((Rock*)curRock)->getHarvestItem().ItemId), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			curTile.SubObject[0] = SOBJ_ITEM;

			curRock->release();
			SAFE_DELETE(curRock);
			mRockList.erase(miRockList++);

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

	for (miItemList = mItemList.begin(); miItemList != mItemList.end();) {
		TINDEX keyIndex = (*miItemList).first;
		DropItem* dItem = (*miItemList).second;

		if (!dItem->IsPickUp) {
			if (!dItem->IsEndDrop) {
				dItem->CurX += 2.0f * dItem->DropDirection;
				dItem->CurY -= 3.0f * dItem->Gravity;
				dItem->Gravity -= 0.4f;
				dItem->DropAniTime += 0.1f;
				if (dItem->DropAniTime > 2.5f) dItem->IsEndDrop = true;
			}
			if (dItem->ToPlayer) {
				TINDEX playerIndex = PLAYER->getTIndex();

				dItem->CurX += (3.0f * (PLAYER->getAbsX() > dItem->CurX ? 1 : -1));
				dItem->CurY += (3.0f *  (PLAYER->getAbsY() > dItem->CurY ? 1 : -1));

				if (PLAYER->getAbsRectF().Contains(dItem->CurX, dItem->CurY)) {
					dItem->IsPickUp = true;
					bReqShowEventBox = true;
					mReqShowEventBoxItemId = dItem->TargetItem->getItemId();
					EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_PICKUP_ITEM);
					PLAYER->addItem(dItem->TargetItem->getItemId());
				}
			}
			else {
				if (keyIndex == PLAYER->getAttackTIndex()) {
					dItem->ToPlayer = true;
				}
			}

			++miItemList;
		}
		else {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			SAFE_DELETE(dItem);
			mItemList.erase(miItemList++);
		}
	}
}

void MineMap::render(void)
{
	Map::render();

	for (miMonsterList = mMonsterList.begin(); miMonsterList != mMonsterList.end(); miMonsterList++) {
		(*miMonsterList).second->render();
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
	
	for (miRockList = mRockList.begin(); miRockList != mRockList.end(); miRockList++) {
		Rock* rock = (*miRockList).second;
		rock->release();
		SAFE_DELETE(rock);
	}
	
	mMonsterList.clear();
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
			rock->init((eRockType)RND->getInt(eRockType::RT_END), tempIndexX, tempIndexY);
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

HRESULT FarmMap::init(const string mapKey)
{
	Map::init(mapKey);

	mRockCount = 10;
	mTreeCount = 10;
	mWeedCount = 10;

	int tempIndexX = 0;
	int tempIndexY = 0;

	while (mRockList.size() < mRockCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object[0] == OBJ_NULL && curTile->IsCanMove) {
			Rock* rock = new Rock;
			rock->init((eRockType)RND->getInt(eRockType::RT_NORMAL_6), tempIndexX, tempIndexY);
			curTile->SubObject[0] = SOBJ_ROCK;
			curTile->IsCanMove = false;
			mRockList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), rock));
		}
	}

	while (mTreeList.size() < mTreeCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object[0] == OBJ_NULL && curTile->IsCanMove) {
			Tree* tree = new Tree;
			tree->init((eTreeType)RND->getInt(eTreeType::TTP_END), tempIndexX, tempIndexY);
			curTile->SubObject[0] = SOBJ_TREE_ATTACK;
			curTile->IsCanMove = false;
			mTreeList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), tree));
		}
	}

	while (mWeedList.size() < mWeedCount) {
		tempIndexX = RND->getInt(mTileXCount);
		tempIndexY = RND->getInt(mTileYCount);
		tagTile* curTile = &mMapTile[tempIndexY][tempIndexX];
		if (curTile->Terrain == TR_NORMAL && curTile->Object[0] == OBJ_NULL && curTile->IsCanMove) {
			Weed* weed = new Weed;
			weed->init((eWeedType)RND->getInt(eWeedType::WDT_END), tempIndexX, tempIndexY);
			curTile->SubObject[0] = SOBJ_WEED;
			curTile->IsCanMove = false;
			mWeedList.insert(make_pair(TINDEX(tempIndexX, tempIndexY), weed));
		}
	}

	mPlantCropFunc = [this](eCropType cropType, TINDEX attackIndex) {
		Crop* crop = new Crop();
		crop->init(cropType, attackIndex.X, attackIndex.Y);
		mCropList.insert(make_pair(attackIndex, crop));
		return crop;
	};

	mCraftObjectPlace = [this](eCraftablesType type, TINDEX attackIndex) {
		if (type == eCraftablesType::CBT_FURNACE) {
			Furance* furance = new Furance;
			furance->init(attackIndex.X, attackIndex.Y);
			mCraftObjectList.insert(make_pair(attackIndex, furance));
		}
	};

	mAttackCraftObjectFunc = [this](TINDEX attackIndex) {
		auto key = mCraftObjectList.find(attackIndex);
		if (key != mCraftObjectList.end()) {
			return key->second;
		}
	};

	mAttackRockFunc = [this](TINDEX attackIndex) {
		auto key = mRockList.find(attackIndex);
		if (key != mRockList.end()) {
			return key->second;
		}
	};

	mAttackTreeFunc = [this](TINDEX attackIndex) {
		auto key = mTreeList.find(attackIndex);
		if (key != mTreeList.end()) {
			return key->second;
		}
	};

	mAttackWeedFunc = [this](TINDEX attackIndex) {
		auto key = mWeedList.find(attackIndex);
		if (key != mWeedList.end()) {
			return key->second;
		}
	};

	mUseWeteringCanFunc = [this](TINDEX attackIndex) {
		auto key = mCropList.find(attackIndex);
		if (key != mCropList.end()) {
			return key->second;
		}
	};

	setPlayerGrapFunc([this](void) {
		TINDEX attackIndex = PLAYER->getAttackTIndex();
		tagTile* attackTile = getTile(attackIndex);
		if (attackTile->SubObject[0] == SOBJ_CROP) {
			EFFECTMANAGER->playEffectSound(EST_HARVESTING);
			EFFECTMANAGER->playEffectSound(EST_PICKUP_ITEM);
			auto key = mCropList.find(attackIndex);
			if (key != mCropList.end()) {
				PLAYER->harvesting(key->second->harvesting());
			}
		}

		if (attackTile->SubObject[0] == SOBJ_CRAFT_OBJ) {
			auto key = mCraftObjectList.find(attackIndex);
			Furance* furance = (Furance*)key->second;
			if (key != mCraftObjectList.end()) {
				if (furance->getCurStat() == eFuranceStat::FS_NONE) {
					furance->reqStartSmelting();
				}
				else {
					PLAYER->addItem(furance->pickUpItem());
				}
			}
		}
	});

	setRenderSubObj([this](int level) {
		if (level == 0) {
			miRCropList = mCropList.begin();
			miRRockList = mRockList.begin();
			miRTreeList = mTreeList.begin();
			miRItemList = mItemList.begin();
			miRWeedList = mWeedList.begin();
			miRCraftObjectList = mCraftObjectList.begin();
		}

		for (; miRCropList != mCropList.end(); ++miRCropList) {
			if (miRCropList->first.Y != level) break;
			(*miRCropList).second->render();
		}

		for (; miRRockList != mRockList.end(); ++miRRockList) {
			if (miRRockList->first.Y != level) break;
			(*miRRockList).second->render();
		}

		for (; miRTreeList != mTreeList.end(); ++miRTreeList) {
			if (miRTreeList->first.Y != level) break;
			(*miRTreeList).second->render();
		}

		for (; miRItemList != mItemList.end(); ++miRItemList) {
			if (miRItemList->first.Y != level) break;
			DropItem* dItem = (*miRItemList).second;
			if (dItem->IsPickUp) continue;
			dItem->TargetItem->render(getRelX(dItem->CurX), getRelY(dItem->CurY));
		}

		for (; miRWeedList != mWeedList.end(); ++miRWeedList) {
			if (miRWeedList->first.Y != level) break;
			(*miRWeedList).second->render();
		}

		for (; miRCraftObjectList != mCraftObjectList.end(); ++miRCraftObjectList) {
			if (miRCraftObjectList->first.Y != level) break;
			(*miRCraftObjectList).second->render();
		}
	});

	return S_OK;
}

void FarmMap::update(void)
{
	Map::update();

	for (miCropList = mCropList.begin(); miCropList != mCropList.end();) {
		Crop* curCrop = miCropList->second;
		if (curCrop->isHarvested()) {
			curCrop->release();
			mCropList.erase(miCropList++);
		}
		else {
			curCrop->update();
			++miCropList;
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

			mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(ITEMCLASS->STONE_NORMAL), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			curTile.SubObject[0] = SOBJ_ITEM;
			break;
		}
		else {
			curRock->update();
			++miRockList;
		}
	}

	for (miTreeList = mTreeList.begin(); miTreeList != mTreeList.end();) {
		Tree* curTree = miTreeList->second;
		TINDEX keyIndex = miTreeList->first;

		curTree->setTrans(curTree->collisionCheck());

		if (curTree->isStumpBroken()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			curTree->release();
			SAFE_DELETE(curTree);
			mTreeList.erase(miTreeList++);

			mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(ITEMCLASS->WOOD), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			curTile.SubObject[0] = SOBJ_ITEM;
			break;
		} else if(curTree->isTopBroken()) {
			if (!curTree->isHarvested()) {
				HarvestItem item = curTree->getHarvestItem();
				mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(item.ItemId), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			}
		}else {
			curTree->update();
			++miTreeList;
		}
	}

	for (miWeedList = mWeedList.begin(); miWeedList != mWeedList.end();) {
		Weed* curWeed = miWeedList->second;
		TINDEX keyIndex = miWeedList->first;

		if (curWeed->isCutOff()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			curWeed->release();
			SAFE_DELETE(curWeed);
			mWeedList.erase(miWeedList++);

			mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(ITEMCLASS->FIBER), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			curTile.SubObject[0] = SOBJ_ITEM;
			break;
		}
		else {
			curWeed->update();
			++miWeedList;
		}
	}

	for (miCraftObjectList = mCraftObjectList.begin(); miCraftObjectList != mCraftObjectList.end();) {
		CraftObject* craftObject = miCraftObjectList->second;
		TINDEX keyIndex = miCraftObjectList->first;

		if (!craftObject->isPlaced()) {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			curTile.SubObject[0] = SOBJ_NULL;
			curTile.IsCanMove = true;
			craftObject->release();
			SAFE_DELETE(craftObject);
			mCraftObjectList.erase(miCraftObjectList++);

			mItemList.insert(make_pair(keyIndex, new DropItem(ITEMMANAGER->findItemReadOnly(ITEMCLASS->FURNACE), keyIndex.X * TILE_SIZE, keyIndex.Y * TILE_SIZE)));
			curTile.SubObject[0] = SOBJ_ITEM;
			break;
		}
		else {
			craftObject->update();
			++miCraftObjectList;
		}
	}

	for (miItemList = mItemList.begin(); miItemList != mItemList.end();) {
		TINDEX keyIndex = (*miItemList).first;
		DropItem* dItem = (*miItemList).second;

		if (!dItem->IsPickUp) {
			if (!dItem->IsEndDrop) {
				dItem->CurX += 2.0f * dItem->DropDirection;
				dItem->CurY -= 3.0f * dItem->Gravity;
				dItem->Gravity -= 0.4f;
				dItem->DropAniTime += 0.1f;
				if (dItem->DropAniTime > 2.5f) dItem->IsEndDrop = true;
			}
			if (dItem->ToPlayer) {
				TINDEX playerIndex = PLAYER->getTIndex();

				dItem->CurX += (3.0f * (PLAYER->getAbsX() > dItem->CurX ? 1 : -1));
				dItem->CurY += (3.0f *  (PLAYER->getAbsY() > dItem->CurY ? 1 : -1));

				if (PLAYER->getAbsRectF().Contains(dItem->CurX, dItem->CurY)) {
					dItem->IsPickUp = true;
					bReqShowEventBox = true;
					mReqShowEventBoxItemId = dItem->TargetItem->getItemId();
					EFFECTMANAGER->playEffectSound(eEffectSoundType::EST_PICKUP_ITEM);
					PLAYER->addItem(dItem->TargetItem->getItemId());
				}
			}
			else {
				if (keyIndex == PLAYER->getAttackTIndex()) {
					dItem->ToPlayer = true;
				}
			}

			++miItemList;
		} else {
			tagTile& curTile = mMapTile[keyIndex.Y][keyIndex.X];
			SAFE_DELETE(dItem);
			mItemList.erase(miItemList++);
		}
	}
}

void FarmMap::render(void)
{
	Map::render();
}

void FarmMap::release(void)
{
	Map::release();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT ShopMap::init(const string mapKey, const eShopType shopType)
{
	Map::init(mapKey);

	mShopType = shopType;
	bReqSaleListUI = false;

	if (shopType == eShopType::SPT_PIERRE_SHOP) {
		mMasterNPC = NPCMANAGER->findNpc("피에르");
		mMasterNPCIndex = TINDEX(4, 3);
		mMasterNPC->setAbsXYToTile(4, 3);
	} else if(shopType == eShopType::SPT_GILL_SHOP) {
		mMasterNPC = NPCMANAGER->findNpc("말론");
		mMasterNPCIndex = TINDEX(4, 3);
		mMasterNPC->setAbsXYToTile(4, 3);
	} else if (shopType == eShopType::SPT_CLINT_SHOP) {
		 mMasterNPC = NPCMANAGER->findNpc("클린트");
		 mMasterNPCIndex = TINDEX(2, 5);
		 mMasterNPC->setAbsXYToTile(2, 5);
	}

	getTile(mMasterNPCIndex)->SubObject[0] = SOBJ_NPC;

	setPlayerGrapFunc([this](void) {
		tagTile* targetTile = getTile(PLAYER->getAttackTIndex());

		if (targetTile->Object[0] == OBJ_SALE_STAND) {
			bReqSaleListUI = true;
		}
	});

	setRenderSubObj([this](int level) {
		if (level == mMasterNPCIndex.Y) {
			mMasterNPC->render();
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
	else if (mShopType == eShopType::SPT_CLINT_SHOP) {
		saleList.push_back(ITEMCLASS->PICK);
		saleList.push_back(ITEMCLASS->AXE);
		saleList.push_back(ITEMCLASS->WATERING_CAN);
		saleList.push_back(ITEMCLASS->FURNACE);
		saleList.push_back(ITEMCLASS->BONE_SWORD);
		saleList.push_back(ITEMCLASS->INSECT_HEAD);
	}

	return saleList;
}

ImageGp* ShopMap::getSaleNpcPortraitImg(void)
{
	return mMasterNPC->getPortraitImg(eNpcPortraitsType::NPT_IDLE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT HomeMap::init(const string mapKey)
{
	Map::init(mapKey);
	mBedIndex = TINDEX(9, 10);

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

HRESULT TownMap::init(string mapKey)
{
	Map::init(mapKey);
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

HRESULT LoadMap::init(const string mapKey)
{
	Map::init(mapKey);
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
