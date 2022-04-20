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
	
	void initPortal();
public:
	HRESULT init(void);

	tagTile ** addMap(string strKey, int mapTileInfoIndex);

	bool updateMap(string strKey, tagTile * saveTagTile, MapTileInfo mapInfo);
	bool makeMap(tagTile * saveTagTile, MapTileInfo mapInfo);

	MapTileInfo findInfo(string strKey, bool isCreate = false);
	tagTile** findMapTile(string strKey, bool isCreate = false);
	
	void release(void);
};

