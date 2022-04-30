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

	tagTileDef* getTileDef = new tagTileDef[spriteXCount * spriteYCount];
	vector<tagTileDef*> vTileDef;

	LoadFile<tagTileDef*>(fileName.c_str(), getTileDef, sizeof(tagTileDef) *  spriteXCount * spriteYCount);
	//�ȷ�Ʈ �и� ����
	ImageGp** palletImg = new ImageGp*[spriteYCount];
	for (int y = 0; y < spriteYCount; y++) {
		palletImg[y] = new ImageGp[spriteXCount];
	}

	for (int y = 0, index = 0; y < spriteYCount; y++) {
		for (int x = 0; x < spriteXCount; x++, index++) {
			tagTileDef* tileDef = new tagTileDef(getTileDef[index]);
			vTileDef.push_back(tileDef);
			palletImg[y][x].init(getMemDc(), spriteImg->getFrameBitmap(x, y));
			palletImg[y][x].setSize(TILE_SIZE, TILE_SIZE);
			if (tileDef->Terrain != TR_NULL) {
				palletImg[y][x].setRenderBitBlt();
			}
		}
	}

	//���� �� �������,  �ȷ�Ʈ �̹��� �ٽ� ����
	Bitmap* rebuildBitmap = GDIPLUSMANAGER->getBlankBitmap(TILE_SIZE * spriteXCount, TILE_SIZE * spriteYCount);
	for (int x = 0; x < spriteXCount; x++) {
		for (int y = 0; y < spriteYCount; y++) {
			GDIPLUSMANAGER->combindBitmap(rebuildBitmap, palletImg[y][x].getBitmap(), x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	ImageGp* baseImg = new ImageGp;
	baseImg->init(getMemDc(), rebuildBitmap, spriteXCount * TILE_SIZE, spriteYCount * TILE_SIZE, spriteXCount, spriteYCount);

	mVTileNode.insert(make_pair(strKey, vTileDef));
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
		LOG::d("�� �ȷ�Ʈ �˻� ���� : " + strKey);
		return key->second;
	}

	return new ImageGp;
}

ImageGp** MapPaletteManager::findPalette(string strKey)
{
	auto key = mVPalette.find(strKey);

	if (key != mVPalette.end())
	{
		LOG::d("�� �ȷ�Ʈ �˻� ���� : " + strKey);
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
		LOG::d("�� �˻� ���� : " + strKey);
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
