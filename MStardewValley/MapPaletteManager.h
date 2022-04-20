#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MapPaletteManager : public GameNode, public SingletonBase<MapPaletteManager>
{
private:
	map<string, vector<tagTileDef*>> mVTileNode;
	map<string, ImageGp**> mVPalette;
	map<string, ImageGp*> mVBasePalette;
public:
	HRESULT init(void);
	void release(void);
	
	void addMapPalette(string strKey, string fileName, string imgKey);

	ImageGp* findBaseSprite(string strKey);
	ImageGp** findPalette(string strKey);
	
	ImageGp* findHoed(int hoedType);
	ImageGp* findHoedWet(int wetType);
	
	vector<tagTileDef*> findTileNode(string mapKey);
private:
};
