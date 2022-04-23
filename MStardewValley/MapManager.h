#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class MapManager: public GameNode, public SingletonBase<MapManager>
{
private:
	vector<MapTileInfo> mVMapInfoAll;

	map<string, MapTileInfo> mMapInfo;
	map<string, MapTileInfo>::iterator miMapInfo;

	map<string, MapPortal*> mMapPortal;
	map<string, MapPortal*>::iterator miMapPortal;

	map<string, tagTile**> mMapTile;
	map<int, string> mMineMapIndex;
public:
	HRESULT init(void);

	tagTile ** addMap(string strKey, int mapTileInfoIndex);
	void addPortal(string strKey, int index, TINDEX tIndex, string toSceneKey, string toMapKey, int toPortalKey);

	bool updateMap(string strKey, tagTile * saveTagTile, MapTileInfo mapInfo);
	bool makeMap(tagTile * saveTagTile, MapTileInfo mapInfo);
	
	MapTileInfo findInfo(string strKey, bool isCreate = false);
	MapPortal* findPortalList(string strKey, bool isCreate = false);
	tagTile** findMapTile(string strKey, bool isCreate = false);
	string findMineMapIdToFloor(int floor);
	
	void release(void);
};

