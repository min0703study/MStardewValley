#include "Stdafx.h"
#include "MapTileManager.h"

HRESULT MapTileManager::init(void)
{
	Json::Value mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);

	for (auto iter = mapInfoJson["map_info_list"].begin(); iter != mapInfoJson["map_info_list"].end(); iter++) {
		MapTileInfo mapTileInfo;
		mapTileInfo.FileName = (*iter)["file_name"].asString();
		mapTileInfo.XCount = (*iter)["map_tile_x_count"].asInt();
		mapTileInfo.YCount = (*iter)["map_tile_y_count"].asInt();
		if ((*iter)["map_type"].asInt() == MT_MINE) {
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

tagTile** MapTileManager::addMap(string key, int mapTileInfoIndex)
{
	MapTileInfo mapTileInfo = mVMapInfoAll[mapTileInfoIndex];
	int mapTileAllCount = mapTileInfo.XCount * mapTileInfo.YCount;

	tagTile* tagTileArray = new tagTile[mapTileAllCount];
	LoadFile<tagTile*>((MAP_FILE_PATH + mapTileInfo.FileName).c_str(), tagTileArray, sizeof(tagTile) * mapTileAllCount);

	tagTile** tempMapTile = new tagTile*[mapTileInfo.XCount];
	for (int i = 0; i < mapTileInfo.XCount; i++) {
		tempMapTile[i] = new tagTile[mapTileInfo.YCount];
	}

	int i = 0;
	for (int y = 0; y < mapTileInfo.YCount; y++) {
		for (int x = 0; x < mapTileInfo.XCount; x++) {
			tempMapTile[y][x] = tagTileArray[i++];
			tempMapTile[y][x].X = x;
			tempMapTile[y][x].Y = y;
		}
	}

	mMapInfo.insert(make_pair(key, mapTileInfo));
	mMapTile.insert(make_pair(key, tempMapTile));

	LOG::d("맵 생성 성공 : " + key);

	return tempMapTile;
}

bool MapTileManager::addNewMap(tagTile* saveTagTile, MapTileInfo mapInfo)
{	
	Json::Value mapInfoJson;

	mapInfoJson["file_name"] = mapInfo.FileName;
	mapInfoJson["map_type"] = mapInfo.MapType;
	mapInfoJson["map_tile_x_count"] = mapInfo.XCount;
	mapInfoJson["map_tile_y_count"] = mapInfo.YCount;
	mapInfoJson["entrance_point_index"] = mapInfo.EnterenceIndex;

	mVMapInfoAll.push_back(mapInfo);

	SaveFile<tagTile*>((MAP_FILE_PATH + mapInfo.FileName).c_str(), saveTagTile, sizeof(tagTile) * mapInfo.XCount * mapInfo.YCount);

	Json::Value jsonValue = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);
	jsonValue["map_info_list"].append(mapInfoJson);
	
	JSONMANAGER->saveJsonFile(JSONCLASS->MapInfo, jsonValue);

	return true;
}

bool MapTileManager::updateMap(string strKey, tagTile* saveTagTile, MapTileInfo mapInfo)
{
	Json::Value mapInfoJson;

	mapInfoJson["file_name"] = mapInfo.FileName;
	mapInfoJson["map_type"] = mapInfo.MapType;
	mapInfoJson["map_tile_x_count"] = mapInfo.XCount;
	mapInfoJson["map_tile_y_count"] = mapInfo.YCount;
	mapInfoJson["entrance_point_index"] = mapInfo.EnterenceIndex;

	mVMapInfoAll.push_back(mapInfo);

	SaveFile<tagTile*>((MAP_FILE_PATH + mapInfo.FileName).c_str(), saveTagTile, sizeof(tagTile) * mapInfo.XCount * mapInfo.YCount);

	Json::Value jsonValue = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);
	jsonValue["map_info_list"].append(mapInfoJson);

	JSONMANAGER->saveJsonFile(JSONCLASS->MapInfo, jsonValue);

	return true;
}

void MapTileManager::addNewMapInfo(MapTileInfo mapInfo)
{
	Json::Value mapInfoJson;

	mapInfoJson["file_name"] = mapInfo.FileName;
	mapInfoJson["map_type"] = mapInfo.MapType;
	mapInfoJson["map_tile_x_count"] = mapInfo.XCount;
	mapInfoJson["map_tile_y_count"] = mapInfo.YCount;
	mapInfoJson["map_tile_y_count"] = mapInfo.EnterenceIndex;

	mVMapInfoAll.push_back(mapInfo);

	JSONMANAGER->saveJsonFile(JSONCLASS->MapInfo, JSONMANAGER->findJsonValue(JSONCLASS->MapInfo).append(mapInfoJson));
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

MapTileInfo MapTileManager::findInfoToFileName(string fileName)
{
	for (vector<MapTileInfo>::iterator iter = mVMapInfoAll.begin(); iter != mVMapInfoAll.end(); iter++) {
		if ((*iter).FileName == fileName) {
			return *iter;
		}
	}

	return MapTileInfo();
}

