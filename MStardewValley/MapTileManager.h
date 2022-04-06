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

	tagTile** addMap(string key, string fileName, int mapInfoIndex);

	ImageGp*** findImg(string key, bool isCreate = false);
	MapTileInfo findInfo(string strKey, bool isCreate = false);
	tagTile** findTile(string strKey, bool isCreate = false);
};

