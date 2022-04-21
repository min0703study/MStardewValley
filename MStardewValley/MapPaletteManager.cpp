#include "Stdafx.h"
#include "MapPaletteManager.h"

HRESULT MapPaletteManager::init(void)
{	
	return S_OK;
}

void MapPaletteManager::addMapPalette(string strKey, string fileName, string imgKey)
{
	ImageGp* spriteImg = GDIPLUSMANAGER->clone(imgKey);

	int spriteXCount = spriteImg->getMaxFrameX() + 1;
	int spriteYCount = spriteImg->getMaxFrameY() + 1;

	tagTileDef* mine = new tagTileDef[spriteXCount * spriteYCount];
	LoadFile<tagTileDef*>(fileName.c_str(), mine, sizeof(tagTileDef) *  spriteXCount * spriteYCount);

	vector<tagTileDef*> vMine;
	for (int y = 0; y < spriteXCount * spriteYCount; y++) {
		vMine.push_back(new tagTileDef(mine[y]));
	}


	ImageGp** palletImg = new ImageGp*[spriteYCount];
	for (int y = 0; y < spriteYCount; y++) {
		palletImg[y] = new ImageGp[spriteXCount];
	}

	for (int y = 0; y < spriteYCount; y++) {
		for (int x = 0; x < spriteXCount; x++) {
			palletImg[y][x].init(getMemDc(), spriteImg->getFrameBitmap(x, y));
			palletImg[y][x].setSize(TILE_SIZE, TILE_SIZE);
		}
	}

	//»çÀÌÁî ¸ÂÃç¼­ ´Ù½Ã ¸¸µë
	Bitmap* rebuildBitmap = GDIPLUSMANAGER->getBlankBitmap(TILE_SIZE * spriteXCount, TILE_SIZE * spriteYCount);
	for (int x = 0; x < spriteXCount; x++) {
		for (int y = 0; y < spriteYCount; y++) {
			GDIPLUSMANAGER->combindBitmap(rebuildBitmap, palletImg[y][x].getBitmap(), x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	ImageGp* baseImg = new ImageGp;
	baseImg->init(getMemDc(), rebuildBitmap, spriteXCount * TILE_SIZE, spriteYCount * TILE_SIZE, spriteXCount, spriteYCount);

	mVTileNode.insert(make_pair(strKey, vMine));
	mVPalette.insert(make_pair(strKey, palletImg));
	mVBasePalette.insert(make_pair(strKey, baseImg));
}

void MapPaletteManager::release(void)
{
}

ImageGp* MapPaletteManager::findBaseSprite(string strKey)
{
	auto key = mVBasePalette.find(strKey);

	if (key != mVBasePalette.end())
	{
		LOG::d("¸Ê ÆÈ·¹Æ® °Ë»ö ¼º°ø : " + strKey);
		return key->second;
	}

	return new ImageGp;
}

ImageGp** MapPaletteManager::findPalette(string strKey)
{
	auto key = mVPalette.find(strKey);

	if (key != mVPalette.end())
	{
		LOG::d("¸Ê ÆÈ·¹Æ® °Ë»ö ¼º°ø : " + strKey);
		return key->second;
	}

	return nullptr;
}

ImageGp * MapPaletteManager::findHoed(int hoedType)
{
	return nullptr;
}

ImageGp * MapPaletteManager::findHoedWet(int wetType)
{
	return nullptr;
}

vector<tagTileDef*> MapPaletteManager::findTileNode(string strKey)
{
	auto key = mVTileNode.find(strKey);

	if (key != mVTileNode.end())
	{
		LOG::d("¸Ê °Ë»ö ¼º°ø : " + strKey);
		return key->second;
	}

	return vector<tagTileDef*>();
}

tagTileDef* MapPaletteManager::findObjectTile(string strKey, OBJECT obj)
{
	vector<tagTileDef*> curList = findTileNode(strKey);
	for (vector<tagTileDef*>::iterator piTile = curList.begin(); piTile != curList.end(); piTile++) {
		if ((*piTile)->Object == obj) return *piTile;
	}

	return nullptr;
}
