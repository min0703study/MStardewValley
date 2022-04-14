#include "Stdafx.h"
#include "MapPaletteManager.h"

HRESULT MapPaletteManager::init(void)
{	
	return S_OK;
}

void MapPaletteManager::addMapPalette(string strKey, string fileName, string imgKey)
{
	ImageGp* spriteImg = GDIPLUSMANAGER->cloneImage(imgKey);

	int spriteXCount = spriteImg->getMaxFrameX() + 1;
	int spriteYCount = spriteImg->getMaxFrameY() + 1;

	tagTile* mine = new tagTile[spriteXCount * spriteYCount];
	LoadFile<tagTile*>(fileName.c_str(), mine, sizeof(tagTile) *  spriteXCount * spriteYCount);

	vector<tagTile*> vMine;
	for (int y = 0; y < spriteXCount * spriteYCount; y++) {
		vMine.push_back(new tagTile(mine[y]));
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

vector<tagTile*> MapPaletteManager::findTileNode(string strKey)
{
	auto key = mVTileNode.find(strKey);

	if (key != mVTileNode.end())
	{
		LOG::d("¸Ê °Ë»ö ¼º°ø : " + strKey);
		return key->second;
	}

	return vector<tagTile*>();
}

/*

Bitmap* MapPaletteManager::getBitmap(eMapPalette mapSprite, int startX, int startY, int xCount, int yCount)
{
	return mRebuildSpriteList[mapSprite]->getFrameBitmapToIndex(startX, startY, xCount, yCount);
}
*/

