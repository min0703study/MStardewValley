#pragma once
#include "GameNode.h"

typedef struct tagOverlayPosition {
	float HairX;
	float HairY;
	float ClothX;
	float ClothY;

	tagOverlayPosition(float hX, float hY, float cX, float cY) {
		HairX = hX;
		HairY = hY;
		ClothX = cX;
		ClothY = cY;
	}

	tagOverlayPosition() {};
};


class PlayerSprite: public GameNode
{
public:

	typedef map<eGameDirection, ImageGp*> mapDirectionImg;

	typedef map<int, vector<ImageGp*>> mapAni;
	typedef map<int, vector<tagOverlayPosition>> mapOverlayPostion;

	typedef map<eGameDirection, mapAni*> mapDirectionAni;

	ImageGp* mHairSprite;
	ImageGp* mClothSprite;
	ImageGp* mBaseSprite;

	mapDirectionImg mHairAni;
	mapDirectionImg mClothAni;
	mapDirectionAni mActionAni;

	mapOverlayPostion mActionOverlay;

	int mHairIndex;
	int mClothIndex;

	HRESULT init(void);

	vector<ImageGp*> getSpriteAction(eGameDirection direction, int stat);
	vector<tagOverlayPosition> getOverayAction(int stat);
	ImageGp* getHairImg(eGameDirection direction);
	ImageGp* getClothImg(eGameDirection direction);

private:


};

