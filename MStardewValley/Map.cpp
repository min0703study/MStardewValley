#include "Stdafx.h"
#include "Map.h"

bool Map::isCollisionWall(RectF rectF)
{
	for (vector<MapTile*>::iterator iVMapTile = mVTileMap.begin(); iVMapTile != mVTileMap.end(); iVMapTile++)
	{
		if ((*iVMapTile)->getAbsRectF().IntersectsWith(rectF)) {
			if (!(*iVMapTile)->isCanMove()) {
				return true;
			};
		}
	}

	return false;
}

void Map::Init(string id, string mapId)
{
	mSpriteImg = GDIPLUSMANAGER->findAndCloneImage(mapId);
	
	float mines1To30PaletteW = (mSpriteImg->getMaxFrameX() + 1) * TILE_SIZE;
	float mines1To30PaletteH = (mSpriteImg->getMaxFrameY() + 1) * TILE_SIZE;

	//√ ±‚»≠
	for (int x = 0; x < 30; x++) {
		for (int y = 0; y < 30; y++) {
			mVTagTile.push_back(tagTile());
		}
	}

	tagTile *thearray = &mVTagTile[0];
	LoadFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * 30 * 30);

	int index = 0;
	bool isUpdate = false;
	for (vector<tagTile>::iterator iVtagTile = mVTagTile.begin(); iVtagTile != mVTagTile.end(); iVtagTile++, index++)
	{
		MapTile* mapTile = new MapTile;
		ImageGp* imgGp = new ImageGp;
		imgGp->init(getMemDc(), TILE_SIZE, TILE_SIZE);
		isUpdate = false;

		if ((*iVtagTile).Terrain != TR_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).TerrainFrameX, (*iVtagTile).TerrainFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		if ((*iVtagTile).Object != OBJ_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).ObjectFrameX, (*iVtagTile).ObjectFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		if ((*iVtagTile).SubObject != OBJ_NULL) {
			imgGp->overlayBitmap(0.0f, 0.0f, mSpriteImg->getFrameBitmap((*iVtagTile).SubObjectFrameX, (*iVtagTile).SubObjectFrameY, TILE_SIZE, TILE_SIZE));
			isUpdate = true;
		}

		if (isUpdate) {
			imgGp->rebuildChachedBitmap();
			mapTile->Init(id, index, (*iVtagTile).X * TILE_SIZE, (*iVtagTile).Y * TILE_SIZE, TILE_SIZE, TILE_SIZE, &(*iVtagTile), imgGp);
			mVTileMap.push_back(mapTile);
		}
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
