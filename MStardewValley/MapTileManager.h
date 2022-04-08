#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class MapTileManager: public GameNode, public SingletonBase<MapTileManager>
{
private:
	typedef map<string, MapTileInfo> mapMapInfo;
	typedef map<string, MapTileInfo>::iterator mapMapInfoIter;

	typedef map<string, ImageGp***> mapMapImgGp;
	typedef map<string, ImageGp***>::iterator mapMapImgGpIter;
	
	mapMapInfo mMapInfo;
	mapMapInfoIter miMapInfo;

	mapMapImgGp mMapImgList;
	mapMapImgGpIter miMapImgList;

	vector<MapTileInfo> mVMapInfoAll;
	map<string, tagTile**> mMapTile;
public:
	HRESULT init(void);
	void release(void);

	tagTile** addMap(string key, int mapTileInfoIndex);
	bool addNewMap(tagTile * saveTagTile, MapTileInfo mapInfo);
	bool updateMap(string strKey, tagTile * saveTagTile, MapTileInfo mapInfo);
	void addNewMapInfo(MapTileInfo mapInfo);

	MapTileInfo findInfo(string strKey, bool isCreate = false);
	tagTile** findTile(string strKey, bool isCreate = false);
	MapTileInfo findInfoToFileName(string fileName);
};

