#include "Stdafx.h"
#include "PlayerSprite.h"

HRESULT PlayerSprite::init()
{
	mBaseBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteMan);
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

	for (int i = 0; i < 4; i++) {
		ImageGp* tempHairImg = new ImageGp;
		tempHairImg->init(getMemDc(), mBaseHairSprite->getFrameBitmap(hairIndexX, hairIndexY + i, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT), PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT);

		mHairAni.insert(make_pair((eGameDirection)i, tempHairImg));
	}

	int clothIndexX = mClothIndex % mBaseClothSprite->getMaxFrameX();
	int clothIndexY = mClothIndex / mBaseClothSprite->getMaxFrameX();

	for (int stat = ePlayerStat::PS_IDLE; stat < ePlayerStat::PS_END; stat++) {
		for (int direction = eGameDirection::GD_UP; direction < eGameDirection::GD_END; direction++) {
			SpriteInfo sInfo = mSpriteInfoList[stat][direction];
			for (int i = 0; i < sInfo.FrameCount; i++) {
				int curX = sInfo.BaseIndexXList[i];
				int curY = sInfo.BaseIndexYList[i];

				ImageGp* tempBaseImg = new ImageGp;
				tempBaseImg->init(getMemDc(),
					mBaseBaseSprite->getFrameBitmap(curX, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerBaseImgList[stat].push_back(tempBaseImg);
				mPlayerAniHeight[stat].push_back(GDIPLUSMANAGER->getAlphaHeightToTop(mBaseBaseSprite->getFrameBitmap(curX, curY)));

				ImageGp* tempArmImg = new ImageGp;
				tempArmImg->init(getMemDc(),
					mBaseBaseSprite->getFrameBitmap(curX + sInfo.ArmIndexInterval, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerArmImgList[stat].push_back(tempArmImg);

				ImageGp* tempLegImg = new ImageGp;
				tempLegImg->init(getMemDc(),
					mBaseBaseSprite->getFrameBitmap(curX + sInfo.LegIndexInterval, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
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
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].BaseIndexXList = new int[5]{ 4,1,0,2,5 };
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].BaseIndexYList = new int[5]{ 3,2,2,2,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_WALK][GD_LEFT].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_LEFT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_LEFT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_LEFT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_WALK][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_WALK][GD_DOWN].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_DOWN].BaseIndexXList = new int[5]{ 0,1,0,2,1 };
	mSpriteInfoList[PS_HOLD_WALK][GD_DOWN].BaseIndexYList = new int[5]{ 3,0,0,0,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_DOWN].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_WALK][GD_DOWN].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_IDLE][GD_UP].FrameCount = 1;
	mSpriteInfoList[PS_HOLD_IDLE][GD_UP].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_UP].BaseIndexYList = new int[1]{ 2 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_UP].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_IDLE][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].FrameCount = 1;
	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].BaseIndexYList = new int[1]{ 1 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].LegIndexInterval = 18;
	mSpriteInfoList[PS_HOLD_IDLE][GD_RIGHT].FilpX = true;

	mSpriteInfoList[PS_HOLD_IDLE][GD_LEFT].FrameCount = 1;
	mSpriteInfoList[PS_HOLD_IDLE][GD_LEFT].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_LEFT].BaseIndexYList = new int[1]{ 1 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_LEFT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_IDLE][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_IDLE][GD_DOWN].FrameCount = 1;
	mSpriteInfoList[PS_HOLD_IDLE][GD_DOWN].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_DOWN].BaseIndexYList = new int[1]{ 0 };
	mSpriteInfoList[PS_HOLD_IDLE][GD_DOWN].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_IDLE][GD_DOWN].LegIndexInterval = 18;

	//IDLE
	mSpriteInfoList[PS_IDLE][GD_UP].FrameCount = 1;
	mSpriteInfoList[PS_IDLE][GD_UP].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_IDLE][GD_UP].BaseIndexYList = new int[1]{ 2 };
	mSpriteInfoList[PS_IDLE][GD_UP].ArmIndexInterval = 6;
	mSpriteInfoList[PS_IDLE][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_IDLE][GD_RIGHT].FrameCount = 1;
	mSpriteInfoList[PS_IDLE][GD_RIGHT].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_IDLE][GD_RIGHT].BaseIndexYList = new int[1]{ 1 };
	mSpriteInfoList[PS_IDLE][GD_RIGHT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_IDLE][GD_RIGHT].LegIndexInterval = 18;
	mSpriteInfoList[PS_IDLE][GD_RIGHT].FilpX = true;

	mSpriteInfoList[PS_IDLE][GD_LEFT].FrameCount = 1;
	mSpriteInfoList[PS_IDLE][GD_LEFT].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_IDLE][GD_LEFT].BaseIndexYList = new int[1]{ 1 };
	mSpriteInfoList[PS_IDLE][GD_LEFT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_IDLE][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_IDLE][GD_DOWN].FrameCount = 1;
	mSpriteInfoList[PS_IDLE][GD_DOWN].BaseIndexXList = new int[1]{ 0 };
	mSpriteInfoList[PS_IDLE][GD_DOWN].BaseIndexYList = new int[1]{ 0 };
	mSpriteInfoList[PS_IDLE][GD_DOWN].ArmIndexInterval = 6;
	mSpriteInfoList[PS_IDLE][GD_DOWN].LegIndexInterval = 18;

	//WALK
	mSpriteInfoList[PS_WALK][GD_UP].FrameCount = 5;
	mSpriteInfoList[PS_WALK][GD_UP].BaseIndexXList = new int[5]{ 4,1,0,2,5 };
	mSpriteInfoList[PS_WALK][GD_UP].BaseIndexYList = new int[5]{ 3,2,2,2,3 };
	mSpriteInfoList[PS_WALK][GD_UP].ArmIndexInterval = 6;
	mSpriteInfoList[PS_WALK][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_WALK][GD_RIGHT].FrameCount = 5;
	mSpriteInfoList[PS_WALK][GD_RIGHT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mSpriteInfoList[PS_WALK][GD_RIGHT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mSpriteInfoList[PS_WALK][GD_RIGHT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_WALK][GD_RIGHT].LegIndexInterval = 18;
	mSpriteInfoList[PS_WALK][GD_RIGHT].FilpX = true;

	mSpriteInfoList[PS_WALK][GD_LEFT].FrameCount = 5;
	mSpriteInfoList[PS_WALK][GD_LEFT].BaseIndexXList = new int[5]{ 2,1,0,2,3 };
	mSpriteInfoList[PS_WALK][GD_LEFT].BaseIndexYList = new int[5]{ 3,1,1,1,3 };
	mSpriteInfoList[PS_WALK][GD_LEFT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_WALK][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_WALK][GD_DOWN].FrameCount = 5;
	mSpriteInfoList[PS_WALK][GD_DOWN].BaseIndexXList = new int[5]{ 0,1,0,2,1 };
	mSpriteInfoList[PS_WALK][GD_DOWN].BaseIndexYList = new int[5]{ 3,0,0,0,3 };
	mSpriteInfoList[PS_WALK][GD_DOWN].ArmIndexInterval = 6;
	mSpriteInfoList[PS_WALK][GD_DOWN].LegIndexInterval = 18;

	//attack_1
	mSpriteInfoList[PS_ATTACK_1][GD_UP].FrameCount = 5;
	mSpriteInfoList[PS_ATTACK_1][GD_UP].BaseIndexXList = new int[5]{ 2,3,4,4,5 };
	mSpriteInfoList[PS_ATTACK_1][GD_UP].BaseIndexYList = new int[5]{ 6,6,6,6,6 };
	mSpriteInfoList[PS_ATTACK_1][GD_UP].ArmIndexInterval = 6;
	mSpriteInfoList[PS_ATTACK_1][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].FrameCount = 5;
	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].BaseIndexYList = new int[5]{ 8,8,8,8,8 };
	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].LegIndexInterval = 18;
	mSpriteInfoList[PS_ATTACK_1][GD_RIGHT].FilpX = true;

	mSpriteInfoList[PS_ATTACK_1][GD_LEFT].FrameCount = 5;
	mSpriteInfoList[PS_ATTACK_1][GD_LEFT].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mSpriteInfoList[PS_ATTACK_1][GD_LEFT].BaseIndexYList = new int[5]{ 8,8,8,8,8 };
	mSpriteInfoList[PS_ATTACK_1][GD_LEFT].ArmIndexInterval = 6;
	mSpriteInfoList[PS_ATTACK_1][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_ATTACK_1][GD_DOWN].FrameCount = 5;
	mSpriteInfoList[PS_ATTACK_1][GD_DOWN].BaseIndexXList = new int[5]{ 0,1,2,3,4 };
	mSpriteInfoList[PS_ATTACK_1][GD_DOWN].BaseIndexYList = new int[5]{ 4,4,4,4,4 };
	mSpriteInfoList[PS_ATTACK_1][GD_DOWN].ArmIndexInterval = 6;
	mSpriteInfoList[PS_ATTACK_1][GD_DOWN].LegIndexInterval = 18;

	//attack_2
	mSpriteInfoList[PS_ATTACK_2][GD_UP].FrameCount = 6;
	mSpriteInfoList[PS_ATTACK_2][GD_UP].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_UP].BaseIndexYList = new int[6]{ 6,6,6,6,6,6 };
	mSpriteInfoList[PS_ATTACK_2][GD_UP].ArmIndexInterval = 12;
	mSpriteInfoList[PS_ATTACK_2][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].FrameCount = 6;
	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].BaseIndexYList = new int[6]{ 5,5,5,5,5,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].LegIndexInterval = 18;
	mSpriteInfoList[PS_ATTACK_2][GD_RIGHT].FilpX = true;

	mSpriteInfoList[PS_ATTACK_2][GD_LEFT].FrameCount = 6;
	mSpriteInfoList[PS_ATTACK_2][GD_LEFT].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_LEFT].BaseIndexYList = new int[6]{ 5,5,5,5,5,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_LEFT].ArmIndexInterval = 12;
	mSpriteInfoList[PS_ATTACK_2][GD_LEFT].LegIndexInterval = 18;

	mSpriteInfoList[PS_ATTACK_2][GD_DOWN].FrameCount = 6;
	mSpriteInfoList[PS_ATTACK_2][GD_DOWN].BaseIndexXList = new int[6]{ 0,1,2,3,4,5 };
	mSpriteInfoList[PS_ATTACK_2][GD_DOWN].BaseIndexYList = new int[6]{ 4,4,4,4,4,4 };
	mSpriteInfoList[PS_ATTACK_2][GD_DOWN].ArmIndexInterval = 12;
	mSpriteInfoList[PS_ATTACK_2][GD_DOWN].LegIndexInterval = 18;
}

void PlayerSprite::release(void)
{
}

int PlayerSprite::getMaxFrameCount(int stat)
{
	return 0;
}

ImageGp* PlayerSprite::getHairImg(eGameDirection direction)
{
	auto keyHair = mHairAni.find(direction);
	if (keyHair != mHairAni.end())
	{
		return keyHair->second;
	}

	return nullptr;
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
