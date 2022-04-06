#include "Stdafx.h"
#include "MapTileManager.h"

HRESULT MapTileManager::init(void)
{
	Json::Value* mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);

	for (auto iter = (*mapInfoJson).begin(); iter != (*mapInfoJson).end(); iter++) {
		MapTileInfo mapTileInfo;
		mapTileInfo.XCount = (*iter)["map_tile_x_count"].asInt();
		mapTileInfo.YCount = (*iter)["map_tile_y_count"].asInt();
		string mapType = (*iter)["map_type"].asString();
		if (mapType == "mine") {
			mapTileInfo.MapType = MT_MINE;
			mapTileInfo.EnterenceIndex = (*iter)["entrance_point_index"].asInt();
		}

		mVMapInfoAll.push_back(mapTileInfo);
	}

	return E_NOTIMPL;
}

void MapTileManager::release(void)
{
}

tagTile** MapTileManager::addMap(string key, string fileName, int mapTileInfoIndex)
{
	MapTileInfo mapTileInfo = mVMapInfoAll[mapTileInfoIndex];

	ImageGp* spriteImg = nullptr;
	switch (mapTileInfo.MapType)
	{
	case MT_MINE:
		spriteImg = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);
		break;
	default:
		//DO NOTHING
		break;
	}

	int mapTileAllCount = mapTileInfo.XCount * mapTileInfo.YCount;

	tagTile* tagTileArray = new tagTile[mapTileAllCount];
	LoadFile<tagTile*>(fileName.c_str(), tagTileArray, sizeof(tagTile) * mapTileAllCount);

	ImageGp*** resultMapImg = new ImageGp**[mapTileInfo.XCount];
	for (int i = 0; i < mapTileInfo.XCount; i++) {
		resultMapImg[i] = new ImageGp*[mapTileInfo.YCount];
	}

	tagTile** tempMapTile = new tagTile*[mapTileInfo.XCount];
	for (int i = 0; i < mapTileInfo.XCount; i++) {
		tempMapTile[i] = new tagTile[mapTileInfo.YCount];
	}
	int i = 0;

	for (int y = 0; y < mapTileInfo.YCount; y++) {
		for (int x = 0; x < mapTileInfo.XCount; x++) {
			ImageGp* imgGp = new ImageGp;

			imgGp->init(getMemDc(), TILE_SIZE, TILE_SIZE);
			
			tempMapTile[x][y] = tagTileArray[i];
			tempMapTile[x][y].X = x * TILE_SIZE;
			tempMapTile[x][y].Y = y * TILE_SIZE;
			tempMapTile[x][y].Y = y * TILE_SIZE;
			if (tempMapTile[x][y].Object != OBJ_NULL || tempMapTile[x][y].SubObject != OBJ_NULL) {
				tempMapTile[x][y].IsCanMove = false;
			}
			else {
				tempMapTile[x][y].IsCanMove = true;
			}
			if (tagTileArray[i].Terrain != TR_NULL) {
				imgGp->overlayBitmap(0.0f, 0.0f, spriteImg->getFrameBitmap(tagTileArray[i].TerrainFrameX, tagTileArray[i].TerrainFrameY, TILE_SIZE, TILE_SIZE));
			}

			if (tagTileArray[i].Object != OBJ_NULL) {
				imgGp->overlayBitmap(0.0f, 0.0f, spriteImg->getFrameBitmap(tagTileArray[i].ObjectFrameX, tagTileArray[i].ObjectFrameY, TILE_SIZE, TILE_SIZE));
			}

			if (tagTileArray[i].SubObject != OBJ_NULL) {
				imgGp->overlayBitmap(0.0f, 0.0f, spriteImg->getFrameBitmap(tagTileArray[i].SubObjectFrameX, tagTileArray[i].SubObjectFrameY, TILE_SIZE, TILE_SIZE));
			}

			imgGp->rebuildChachedBitmap();

			resultMapImg[x][y] = imgGp;

			i++;
			float xPos = ((i % 19)) * TILE_SIZE;
			float yPos = (i / 19) * TILE_SIZE;
		}
	}

	mMapImgList.insert(make_pair(key, resultMapImg));
	mMapInfo.insert(make_pair(key, mapTileInfo));
	mMapTile.insert(make_pair(key, tempMapTile));

	LOG::d("맵 생성 성공 : " + key);

	return tempMapTile;
}

ImageGp*** MapTileManager::findImg(string strKey, bool isCreate)
{
	auto tempMapPair = mMapImgList.find(strKey);

	if (tempMapPair != mMapImgList.end())
	{
		return tempMapPair->second;
	}
	else if (!isCreate) {
		LOG::d(LOG_IMG_BASE_TAG, "맵 이미지 검색 실패 : " + strKey);
	}

	return nullptr;
}

MapTileInfo MapTileManager::findInfo(string strKey, bool isCreate)
{
	auto tempMapPair = mMapInfo.find(strKey);

	if (tempMapPair != mMapInfo.end())
	{
		return tempMapPair->second;
	}
	else if (!isCreate) {
		LOG::d(LOG_IMG_BASE_TAG, "맵 정보 검색 실패 : " + strKey);
	}

	return MapTileInfo();
}

tagTile** MapTileManager::findTile(string strKey, bool isCreate)
{
	auto tempMapPair = mMapTile.find(strKey);

	if (tempMapPair != mMapTile.end())
	{
		return tempMapPair->second;
	}
	else if (!isCreate) {
		LOG::d(LOG_IMG_BASE_TAG, "맵 검색 실패 : " + strKey);
	}

	return nullptr;
}
