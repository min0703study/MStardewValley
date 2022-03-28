#include "Stdafx.h"
#include "Map.h"

#define TILE_SIZE		50.0f

void Map::Init(string id, string mapId)
{
	TILECLASS->findTileNodeLIst(mapId, mCurTilePalette);
	mSpriteImg = GDIPLUSMANAGER->findAndCloneImage(mapId);
	
	float mines1To30PaletteW = (mSpriteImg->getMaxFrameX() + 1) * TILE_SIZE;
	float mines1To30PaletteH = (mSpriteImg->getMaxFrameY() + 1) * TILE_SIZE;

	mTilePalette = new GameUI;
	mTilePalette->init("±§ªÍ ≈∏¿œ ∆»∑π∆Æ", 0, 0, mines1To30PaletteW, mines1To30PaletteH, mSpriteImg);

	for (int x = 0; x < 30; x++) {
		for (int y = 0; y < 30; y++) {
			mCurTagTile.push_back(tagTile());
		}
	}

	int i = 0;

	tagTile *thearray = &mCurTagTile[0];
	LoadFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * 30 * 30);

	for (vector<tagTile>::iterator iVtagTile = mCurTagTile.begin(); iVtagTile != mCurTagTile.end(); iVtagTile++)
	{
		MapTile* mapTile = new MapTile;
		ImageGp* imgGp = new ImageGp;

		imgGp->init(getMemDc(), TILE_SIZE, TILE_SIZE);

		if ((*iVtagTile).Terrain != TR_NULL) {
			imgGp->coverBitmap(
				0,0,
				mSpriteImg->getFrameBitmap((*iVtagTile).TerrainFrameX, (*iVtagTile).TerrainFrameY)
			);
		}

		if ((*iVtagTile).Object != OBJ_NULL) {
			imgGp->coverBitmap(
				0,0,
				mSpriteImg->getFrameBitmap((*iVtagTile).ObjectFrameX, (*iVtagTile).ObjectFrameY)
			);
		}


		if ((*iVtagTile).SubObject != OBJ_NULL) {
			imgGp->coverBitmap(
				0,0,
				mSpriteImg->getFrameBitmap((*iVtagTile).SubObjectFrameX, (*iVtagTile).SubObjectFrameY)
			);
		}

		imgGp->rebuildChachedBitmap();
		mapTile->Init(id, i++, (*iVtagTile).X * TILE_SIZE, (*iVtagTile).Y * TILE_SIZE, TILE_SIZE, TILE_SIZE, &(*iVtagTile), imgGp);
		mVTileMap.push_back(mapTile);
	}

}

void Map::update(void)
{
}

void Map::render(void)
{
	for (vector<MapTile*>::iterator iVMapTile = mVTileMap.begin(); iVMapTile != mVTileMap.end(); iVMapTile++)
	{
		(*iVMapTile)->render();
	}
}

void Map::release(void)
{
}
