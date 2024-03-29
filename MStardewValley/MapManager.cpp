#include "Stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init(void)
{
	LOG::d_blue("===================맵 타일 매니저 시작 ==========================");
	Json::Value mapInfoJson = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);

	for (auto iter = mapInfoJson["map_info_list"].begin(); iter != mapInfoJson["map_info_list"].end(); iter++) {
		MapTileInfo mapTileInfo;
		mapTileInfo.FileName = (*iter)["file_name"].asString();
		mapTileInfo.FilePath = (*iter)["file_path"].asString();
		mapTileInfo.XCount = (*iter)["map_tile_x_count"].asInt();
		mapTileInfo.YCount = (*iter)["map_tile_y_count"].asInt();
		mapTileInfo.PortalCount = (*iter)["portal_count"].asInt();

		if ((*iter)["map_type"].asInt() == MT_MINE) {
			mapTileInfo.MapType = MT_MINE;
			mapTileInfo.PaletteKey = MAPCLASS->MINE_P;
			mapTileInfo.EnterenceIndex = (*iter)["entrance_point_index"].asInt();
			mapTileInfo.Floor = (*iter)["floor"].asInt();
			mapTileInfo.MonsterCount = (*iter)["monster_count"].asInt();
			mapTileInfo.RockCount = (*iter)["rock_count"].asInt();
		}

		if ((*iter)["map_type"].asInt() == MT_TOWN) {
			mapTileInfo.MapType = MT_TOWN;
			mapTileInfo.PaletteKey = MAPCLASS->TOWN_INTERIOR_P;
			mapTileInfo.EnterenceIndex = (*iter)["entrance_point_index"].asInt();
		}

		if ((*iter)["map_type"].asInt() == MT_FARM) {
			mapTileInfo.MapType = MT_FARM;
			mapTileInfo.PaletteKey = MAPCLASS->OUTDOOR_P;
			mapTileInfo.EnterenceIndex = (*iter)["entrance_point_index"].asInt();
		}


		mVMapInfoAll.push_back(mapTileInfo);
	}

	LOG::d_blue("===================맵 타일 매니저 종료 ==========================");
	return S_OK;
}

tagTile** MapManager::addMap(string key, int mapTileInfoIndex)
{
	MapTileInfo mapTileInfo = mVMapInfoAll[mapTileInfoIndex];
	int mapTileAllCount = mapTileInfo.XCount * mapTileInfo.YCount;

	tagTile* original = new tagTile[mapTileAllCount];
	LoadFile<tagTile*>((MAP_FILE_PATH + mapTileInfo.FileName).c_str(), original, sizeof(tagTile) * mapTileAllCount);

	tagTile** tempMapTile = new tagTile*[mapTileInfo.YCount];
	for (int i = 0; i < mapTileInfo.YCount; i++) {
		tempMapTile[i] = new tagTile[mapTileInfo.XCount];
	}

	int i = 0;
	for (int y = 0; y < mapTileInfo.YCount; y++) {
		for (int x = 0; x < mapTileInfo.XCount; x++) {
			tempMapTile[y][x] = original[i++];
		}
	}

	if (mapTileInfo.MapType == MT_MINE) {
		mMineMapIndex.insert(make_pair(mapTileInfo.Floor, key));
	}

	mMapInfo.insert(make_pair(key, mapTileInfo));
	mMapTile.insert(make_pair(key, tempMapTile));

	LOG::d("맵 생성 성공 : " + key);

	return nullptr;
}

void MapManager::addPortal(string strKey, int index, TINDEX tIndex, TINDEX startIndex, string toSceneKey, string toMapKey, int toPortalKey)
{
	MapTileInfo mapTileInfo = findInfo(strKey);

	auto portalKey = mMapPortal.find(strKey);
	if (portalKey != mMapPortal.end()) {
		portalKey->second[index] = MapPortal(tIndex, startIndex, toSceneKey, toMapKey, toPortalKey);
	} else {
		MapPortal* portalList = new MapPortal[mapTileInfo.PortalCount];
		portalList[index] = MapPortal(tIndex, startIndex, toSceneKey, toMapKey, toPortalKey);
		mMapPortal.insert(make_pair(strKey, portalList));
	}
}

bool MapManager::makeMap(tagTile* saveTagTile, MapTileInfo mapInfo)
{	
	Json::Value mapInfoJson;

	mapInfoJson["file_name"] = mapInfo.FileName;
	mapInfoJson["file_path"] = mapInfo.FilePath;
	mapInfoJson["map_type"] = mapInfo.MapType;
	mapInfoJson["map_tile_x_count"] = mapInfo.XCount;
	mapInfoJson["map_tile_y_count"] = mapInfo.YCount;

	mVMapInfoAll.push_back(mapInfo);

	Json::Value jsonValue = JSONMANAGER->findJsonValue(JSONCLASS->MapInfo);
	jsonValue["map_info_list"].append(mapInfoJson);
	
	JSONMANAGER->saveJsonFile(JSONCLASS->MapInfo, jsonValue);

	SaveFile<tagTile*>((MAP_FILE_PATH + mapInfo.FileName).c_str(), saveTagTile, sizeof(tagTile) * (mapInfo.XCount * mapInfo.YCount));

	return true;
}

bool MapManager::updateMap(string strKey, tagTile* saveTagTile, MapTileInfo mapInfo)
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

MapPortal* MapManager::findPortalList(string strKey, bool isCreate)
{
	auto tempMapPair = mMapPortal.find(strKey);

	if (tempMapPair != mMapPortal.end())
	{
		return tempMapPair->second;
	}
	else if (!isCreate) {
		LOG::d(LOG_IMG_BASE_TAG, "맵 정보 검색 실패 : " + strKey);
	}

	return nullptr;
}

MapTileInfo MapManager::findInfo(string strKey, bool isCreate)
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

tagTile** MapManager::findMapTile(string strKey, bool isCreate)
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

string MapManager::findMineMapIdToFloor(int floor)
{
	auto key = mMineMapIndex.find(floor);
	if (key != mMineMapIndex.end()) {
		return key->second;
	}

	return "";
}

void MapManager::release(void)
{
}
