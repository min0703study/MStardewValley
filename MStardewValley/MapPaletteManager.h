#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MapPaletteManager : public GameNode, public SingletonBase<MapPaletteManager>
{
private:
	map<string, vector<tagTile*>> mVTileNode;
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
	
	vector<tagTile*> findTileNode(string mapKey);


	//Bitmap* getBitmap(eMapPalette mapSprite, int startX, int startY, int xCount, int yCount);
private:
};
