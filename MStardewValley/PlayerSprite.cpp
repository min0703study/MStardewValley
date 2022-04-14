#include "Stdafx.h"
#include "PlayerSprite.h"

HRESULT PlayerSprite::init()
{
	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteMan);
	mBaseHairSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteHair);
	mBaseClothSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteCloth);

	this->uploadJson();

	mShadow = new ImageGp;
	mShadow->init(getMemDc(), 
		GDIPLUSMANAGER->getDrawElipseToBitmap(0.0f, 0.0f, PLAYER_WIDTH * 0.8, PLAYER_HEIGHT * 0.2, Color(100, 0, 0, 0)),
		PLAYER_WIDTH * 0.8, 
		PLAYER_HEIGHT * 0.2);
	
	mHairIndex = 4;
	mClothIndex = 8;

	int hairIndexX = mHairIndex % mBaseHairSprite->getMaxFrameX();
	int hairIndexY = mHairIndex / mBaseHairSprite->getMaxFrameX();

	mVHair[GD_UP] = new ImageGp;
	mVHair[GD_UP]->init(getMemDc(), mBaseHairSprite->getFrameBitmap(hairIndexX, hairIndexY + 2, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT));
	mVHair[GD_DOWN] = new ImageGp;
	mVHair[GD_DOWN]->init(getMemDc(), mBaseHairSprite->getFrameBitmap(hairIndexX, hairIndexY, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT));
	mVHair[GD_RIGHT] = new ImageGp;
	mVHair[GD_RIGHT]->init(getMemDc(), mBaseHairSprite->getFrameBitmap(hairIndexX, hairIndexY + 1, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT));
	mVHair[GD_LEFT] = new ImageGp;
	mVHair[GD_LEFT]->init(getMemDc(), mBaseHairSprite->getFrameBitmap(hairIndexX, hairIndexY + 1, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT));
	mVHair[GD_LEFT]->flipX();

	int clothIndexX = mClothIndex % mBaseClothSprite->getMaxFrameX();
	int clothIndexY = mClothIndex / mBaseClothSprite->getMaxFrameX();

	for (int stat = ePlayerAniStat::PAS_IDLE; stat < ePlayerAniStat::PAS_END; stat++) {
		for (int direction = eGameDirection::GD_UP; direction < eGameDirection::GD_END; direction++) {
			SpriteInfo sInfo = mSpriteInfoList[stat];
			SpriteDetailInfo sDetail = sInfo.DetailInfo[direction];
			for (int i = 0; i < sInfo.FrameCount; i++) {
				int curX = sDetail.BaseIndexXList[i];
				int curY = sDetail.BaseIndexYList[i];
				ImageGp* tempBaseImg = new ImageGp;
				tempBaseImg->init(getMemDc(),
					mBaseSprite->getFrameBitmap(curX, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerBaseImgList[stat].push_back(tempBaseImg);
				mPlayerAniHeight[stat].push_back(GDIPLUSMANAGER->getAlphaHeightToTop(tempBaseImg->getBitmap()));

				ImageGp* tempArmImg = new ImageGp;
				tempArmImg->init(getMemDc(),
					mBaseSprite->getFrameBitmap(curX + sInfo.ArmIndexInterval, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerArmImgList[stat].push_back(tempArmImg);

				ImageGp* tempLegImg = new ImageGp;
				tempLegImg->init(getMemDc(),
					mBaseSprite->getFrameBitmap(curX + sInfo.LegIndexInterval, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerLegImgList[stat].push_back(tempLegImg);

				if (direction == GD_LEFT) {
					tempBaseImg->flipX();
					tempArmImg->flipX();
					tempLegImg->flipX();
				}
			}
		}
	}

	return S_OK;
}

void PlayerSprite::uploadJson()
{

	SpriteInfo* mCurInfo;

	//HOLD_WALK
	mCurInfo = &mSpriteInfoList[PAS_HOLD_WALK];
	mCurInfo->FrameCount = 5;
	mCurInfo->ArmIndexInterval = 12;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[mCurInfo->FrameCount]{ 4,1,0,2,5 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[mCurInfo->FrameCount]{ 3,2,2,2,3 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 2,1,0,2,3 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 3,1,1,1,3 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 2,1,0,2,3 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 3,1,1,1,3 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[mCurInfo->FrameCount]{ 0,1,0,2,1 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[mCurInfo->FrameCount]{ 3,0,0,0,3 };

	//HOLD
	mCurInfo = &mSpriteInfoList[PAS_HOLD_IDLE];
	mCurInfo->FrameCount = 1;
	mCurInfo->ArmIndexInterval = 12;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[1]{ 2 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[1]{ 1 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[1]{ 1 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[1]{ 0 };

	//IDLE
	mCurInfo = &mSpriteInfoList[PAS_IDLE];
	mCurInfo->FrameCount = 1;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[1]{ 2 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[1]{ 1 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[1]{ 1 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[1]{ 0 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[1]{ 0 };

	//WALK
	mCurInfo = &mSpriteInfoList[PAS_WALK];
	mCurInfo->FrameCount = 5;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[5]{ 4,1,0,2,5 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[5]{ 3,2,2,2,3 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[5]{ 0,1,0,2,1 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[5]{ 3,0,0,0,3 };

	//ATTACK_1
	mCurInfo = &mSpriteInfoList[PAS_ATTACK_1];
	mCurInfo->FrameCount = 5;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[5]{ 2,3,4,4,5 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[5]{ 6,6,6,6,6 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[5]{ 8,8,8,8,8 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[5]{ 8,8,8,8,8 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[5]{ 4,4,4,4,4 };

	//ATTACK_2
	mCurInfo = &mSpriteInfoList[PAS_ATTACK_2];
	mCurInfo->FrameCount = 6;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[6]{ 6,6,6,6,6,6 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[6]{ 5,5,5,5,5,5 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[6]{ 5,5,5,5,5,5 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[6]{ 4,4,4,4,4,4 };

	mCurInfo = &mSpriteInfoList[PAS_HARVESTING];
	mCurInfo->FrameCount = 4;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[mCurInfo->FrameCount]{ 2,3,4,4 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[mCurInfo->FrameCount]{ 10,10,10,10 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 5,5,0,1 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,10,10 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 5,5,0,1 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,10,10 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[mCurInfo->FrameCount]{ 0,1,2,2 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,9,9 };

	mCurInfo = &mSpriteInfoList[PAS_WATER_THE_PLANT];
	mCurInfo->FrameCount = 6;
	mCurInfo->ArmIndexInterval = 6;
	mCurInfo->LegIndexInterval = 18;
	mCurInfo->DetailInfo[GD_UP].BaseIndexXList = new int[mCurInfo->FrameCount]{ 2,3,2,4,4,4 };
	mCurInfo->DetailInfo[GD_UP].BaseIndexYList = new int[mCurInfo->FrameCount]{ 10,10,7,7,7,7 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 4,5,3,3,3,3 };
	mCurInfo->DetailInfo[GD_RIGHT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,7,7,7,7 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexXList = new int[mCurInfo->FrameCount]{ 4,5,3,3,3,3 };
	mCurInfo->DetailInfo[GD_LEFT].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,7,7,7,7 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexXList = new int[mCurInfo->FrameCount]{ 0,1,1,1,1,1 };
	mCurInfo->DetailInfo[GD_DOWN].BaseIndexYList = new int[mCurInfo->FrameCount]{ 9,9,4,4,4,4 };
}

void PlayerSprite::release(void)
{
	/*
		Á¦°Å
		vector<ImageGp*> mVAni[ePlayerStat::PS_END];
		vector<Bitmap*> mVHair[eGameDirection::GD_END];
		vector<Bitmap*> mVCloth[eGameDirection::GD_END];
		ImageGp* mShadow;
		ImageGp* mBaseHairSprite;
		ImageGp* mBaseClothSprite;
		ImageGp* mBaseSprite;
	*/
}

int PlayerSprite::getMaxFrameCount(int stat)
{
	return mSpriteInfoList[stat].FrameCount;
}

ImageGp** PlayerSprite::getHairImg()
{
	return mVHair;
}

ImageGp* PlayerSprite::getClothImg(eGameDirection direction)
{
	auto keyCloth = mClothAni.find(direction);
	if (keyCloth != mClothAni.end())
	{
		return keyCloth->second;
	}

	return nullptr;
}
