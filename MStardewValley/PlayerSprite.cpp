#include "Stdafx.h"
#include "PlayerSprite.h"

HRESULT PlayerSprite::init()
{
	this->uploadJson();

	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteMan);
	mHairSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteHair);
	mClothSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->PlayerSpriteCloth);

	mShadow = new ImageGp;
	mShadow->init(getMemDc(), 
		GDIPLUSMANAGER->getDrawElipseToBitmap(0.0f, 0.0f, PLAYER_WIDTH * 0.8, PLAYER_HEIGHT * 0.2, Color(100, 0, 0, 0)),
		PLAYER_WIDTH * 0.8, 
		PLAYER_HEIGHT * 0.2);
	
	mHairIndex = 4;
	mClothIndex = 8;

	int hairIndexX = mHairIndex % mHairSprite->getMaxFrameX();
	int hairIndexY = mHairIndex / mHairSprite->getMaxFrameX();

	for (int i = 0; i < 4; i++) {
		ImageGp* tempHairImg = new ImageGp;
		tempHairImg->init(getMemDc(), mHairSprite->getFrameBitmap(hairIndexX, hairIndexY + i, PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT), PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT);

		mHairAni.insert(make_pair((eGameDirection)i, tempHairImg));
	}

	int clothIndexX = mClothIndex % mClothSprite->getMaxFrameX();
	int clothIndexY = mClothIndex / mClothSprite->getMaxFrameX();

	for (int i = 0; i < 4; i++) {
		ImageGp* tempClothImg = new ImageGp;
		tempClothImg->init(getMemDc(), mClothSprite->getFrameBitmap(clothIndexX, clothIndexY + i, PLAYER_CLOTH_WIDTH, PLAYER_CLOTH_HEIGHT), PLAYER_CLOTH_WIDTH, PLAYER_CLOTH_HEIGHT);

		mClothAni.insert(make_pair((eGameDirection)i, tempClothImg));
	}

	
	for (vector<tagSpriteInfoDetail>::iterator iVSInfo = mVTagSpriteInfo.begin(); iVSInfo != mVTagSpriteInfo.end(); iVSInfo++) {
		vector<ImageGp*> tempVImageGp;

		for (int i = 0; i < 3; i++) { 
			int spriteInterval = mSpriteInfo[iVSInfo->Stat].SpriteInterval[i];
			for (int index = 0; index < mSpriteInfo[iVSInfo->Stat].MaxFrameCount; index++) {
				ImageGp* tempImageGp = new ImageGp;
				tempImageGp->init(getMemDc(), 
					mBaseSprite->getFrameBitmap(
						iVSInfo->SpriteIndexX[index] + spriteInterval, 
						iVSInfo->SpriteIndexY[index], 
						PLAYER_WIDTH, PLAYER_HEIGHT), 
					PLAYER_WIDTH, PLAYER_HEIGHT);
				if (iVSInfo->IsFlipX) {
					tempImageGp->flipX();
				}

				tempVImageGp.push_back(tempImageGp);
			}
		}

		auto mKeyMapAni = mActionAni.find(iVSInfo->Direction);
		if (mKeyMapAni == mActionAni.end())
		{
			mapAni* tempMapAni = new mapAni;
			tempMapAni->insert(make_pair(iVSInfo->Stat, tempVImageGp));
			mActionAni.insert(make_pair(iVSInfo->Direction, tempMapAni));
		}
		else {
			mKeyMapAni->second->insert(make_pair(iVSInfo->Stat, tempVImageGp));
		}
	}

	for (int stat = ePlayerStat::PS_HOLD_WALK; stat <= ePlayerStat::PS_HOLD_WALK; stat++) {
		for (int direction = eGameDirection::GD_UP; direction <= eGameDirection::GD_DOWN; direction++) {
			SpriteInfoT sInfo = mSpriteInfoList[stat][direction];
			for (int i = 0; i < sInfo.FrameCount; i++) {

				LOG::d(to_string(i));
				int curX = sInfo.BaseIndexXList[i];
				int curY = sInfo.BaseIndexYList[i];

				ImageGp* tempBaseImg = new ImageGp;
				tempBaseImg->init(getMemDc(),
					mBaseSprite->getFrameBitmap(curX, curY, PLAYER_WIDTH, PLAYER_HEIGHT),
					PLAYER_WIDTH, PLAYER_HEIGHT);
				mPlayerBaseImgList[stat].push_back(tempBaseImg);
				mPlayerAniHeight[stat].push_back(GDIPLUSMANAGER->getAlphaHeightToTop(mBaseSprite->getFrameBitmap(curX, curY)));

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
				if (direction == GD_RIGHT) {
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
	mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount = 5;
	mSpriteInfo[ePlayerStat::PS_WALK].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_WALK].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_WALK].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_WALK].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_WALK].SpriteInterval = new int[3]{ 0, 6, 18 };

	mSpriteInfo[ePlayerStat::PS_IDLE].MaxFrameCount = 1;
	mSpriteInfo[ePlayerStat::PS_IDLE].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_IDLE].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_IDLE].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_IDLE].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_IDLE].SpriteInterval = new int[3]{ 0, 6, 18 };

	mSpriteInfo[ePlayerStat::PS_ATTACK_1].MaxFrameCount = 5;
	mSpriteInfo[ePlayerStat::PS_ATTACK_1].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_1].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_1].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_1].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_1].SpriteInterval = new int[3]{ 0, 6, 18 };

	mSpriteInfo[ePlayerStat::PS_ATTACK_2].MaxFrameCount = 6;
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].SpriteInterval = new int[3]{ 0, 12, 18 };

	mSpriteInfo[ePlayerStat::PS_ATTACK_2].MaxFrameCount = 6;
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_ATTACK_2].SpriteInterval = new int[3]{ 0, 12, 18 };

	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].MaxFrameCount = 1;
	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_IDLE].SpriteInterval = new int[3]{ 0, 12, 18 };

	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].MaxFrameCount = 5;
	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].HairPtX = new float[mSpriteInfo[ePlayerStat::PS_HOLD_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].HairPtY = new float[mSpriteInfo[ePlayerStat::PS_HOLD_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].ClothPtX = new float[mSpriteInfo[ePlayerStat::PS_HOLD_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].ClothPtY = new float[mSpriteInfo[ePlayerStat::PS_HOLD_WALK].MaxFrameCount]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	mSpriteInfo[ePlayerStat::PS_HOLD_WALK].SpriteInterval = new int[3]{ 0, 12, 18 };

	tagSpriteInfoDetail tempSpriteInfo;

	tempSpriteInfo.Stat = ePlayerStat::PS_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2 };

	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 1 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 1 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,1,0,2,3 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,1,1,1,3 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,1,0,2,3 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,1,1,1,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);
	
	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,1,0,2,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,2,2,2,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);
	
	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,0,2,1 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,0,0,0,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,1,0,2,3 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,1,1,1,3 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,1,0,2,3 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,1,1,1,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);
	
	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,1,0,2,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,2,2,2,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);
	
	tempSpriteInfo.Stat = ePlayerStat::PS_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,0,2,1 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,0,0,0,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	/////
	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_1;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 8,8,8,8,8 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_1;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 8,8,8,8,8 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_1;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,3,4,4,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 6,6,6,6,6 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_1;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,4,4,4,4 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	///// attack_2
	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_2;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 5,5,5,5,5,5 };

	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_2;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 5,5,5,5,5,5 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_2;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 6,6,6,6,6,6 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_ATTACK_2;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,2,3,4,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,4,4,4,4,4 };

	//hold idle
	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2 };

	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 1 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 1 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_IDLE;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0 };
	tempSpriteInfo.IsFlipX = false;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	//HOLD WALK
	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_DOWN;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 0,1,0,2,1 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,0,0,0,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_LEFT;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 2,1,0,2,3 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,1,1,1,3 };
	tempSpriteInfo.IsFlipX = true;

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_RIGHT;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,1,0,2,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,2,2,2,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	tempSpriteInfo.Stat = ePlayerStat::PS_HOLD_WALK;
	tempSpriteInfo.Direction = eGameDirection::GD_UP;
	tempSpriteInfo.IsFlipX = false;

	tempSpriteInfo.SpriteIndexX = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 4,1,0,2,5 };
	tempSpriteInfo.SpriteIndexY = new int[mSpriteInfo[tempSpriteInfo.Stat].MaxFrameCount]{ 3,2,2,2,3 };

	mVTagSpriteInfo.push_back(tempSpriteInfo);

	mSpriteInfoList[PS_HOLD_WALK][GD_UP].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].BaseIndexXList = new int[5]{ 4,1,0,2,5 };
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].BaseIndexYList = new int[5]{ 3,2,2,2,3 };
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].ArmIndexInterval = 12;
	mSpriteInfoList[PS_HOLD_WALK][GD_UP].LegIndexInterval = 18;

	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].FrameCount = 5;
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].BaseIndexXList = new int[5]{ 4,1,0,2,5 };
	mSpriteInfoList[PS_HOLD_WALK][GD_RIGHT].BaseIndexYList = new int[5]{ 3,2,2,2,3 };
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
}

void PlayerSprite::release(void)
{
}

vector<ImageGp*> PlayerSprite::getVAni(eGameDirection direction, int stat)
{
	auto mKeyMapAni = mActionAni.find(direction);
	if (mKeyMapAni != mActionAni.end())
	{
		auto mKeyAniList = mKeyMapAni->second->find(stat);
		if (mKeyAniList != mKeyMapAni->second->end()) {
			return mKeyAniList->second;
		}
	}

	return vector<ImageGp*>();
}

vector<ImageGp*> PlayerSprite::getVHairAni(eGameDirection direction, int stat)
{
	auto mKeyMapAni = mActionAni.find(direction);
	if (mKeyMapAni != mActionAni.end())
	{
		auto mKeyAniList = mKeyMapAni->second->find(stat);
		if (mKeyAniList != mKeyMapAni->second->end()) {
			return mKeyAniList->second;
		}
	}

	return vector<ImageGp*>();
}


int PlayerSprite::getMaxFrameCount(int stat)
{
	return mSpriteInfo[stat].MaxFrameCount;
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
