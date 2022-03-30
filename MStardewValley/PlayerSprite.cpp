#include "Stdafx.h"
#include "PlayerSprite.h"
#include "Player.h"

HRESULT PlayerSprite::init()
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->PlayerSpriteMan);
	mHairSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->PlayerSpriteHair);
	mClothSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->PlayerSpriteCloth);
	
	mBaseSprite->setSizeRatio(1.5);

	mHairIndex = 4;
	mClothIndex = 8;

	
	int hairIndexX = mHairIndex % mHairSprite->getMaxFrameX();
	int hairIndexY = mHairIndex / mHairSprite->getMaxFrameX();

	for (int i = 0; i < 4; i++) {
		ImageGp* tempHairImg = new ImageGp;
		tempHairImg->init(getMemDc(), mHairSprite->getFrameBitmap(hairIndexX, hairIndexY + i), PLAYER_HAIR_WIDTH, PLAYER_HAIR_HEIGHT);

		mHairAni.insert(make_pair((eGameDirection)i, tempHairImg));
	}

	int clothIndexX = mClothIndex % mClothSprite->getMaxFrameX();
	int clothIndexY = mClothIndex / mClothSprite->getMaxFrameX();

	for (int i = 0; i < 4; i++) {
		ImageGp* tempHairImg = new ImageGp;
		tempHairImg->init(getMemDc(), mClothSprite->getFrameBitmap(clothIndexX, clothIndexY + i), PLAYER_CLOTH_WIDTH, PLAYER_CLOTH_HEIGHT);

		mClothAni.insert(make_pair((eGameDirection)i, tempHairImg));
	}


	//run
	{
	int indexX[] = { 2,1,0,2,3 };
	int indexY[] = { 3,1,1,1,3 };

	float hairPtX[] = { 0,0,0,0,0 };
	float hairPtY[] = { 0,0,0,0,0 };

	float clothPtX[] = { 0,0,0,0,0 };
	float clothPtY[] = { 0,0,0,0,0 };

	vector<ImageGp*> tempV;

	for (int index = 0; index < 5; index++) {
		ImageGp* tempImageGp = new ImageGp;
		tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index], indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
		tempV.push_back(tempImageGp);
	}

	for (int index = 0; index < 5; index++) {
		ImageGp* tempImageGp = new ImageGp;
		tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 6, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
		tempV.push_back(tempImageGp);
	}

	for (int index = 0; index < 5; index++) {
		ImageGp* tempImageGp = new ImageGp;
		tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 18, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
		tempV.push_back(tempImageGp);
	}

	auto mKeyMapAni = mActionAni.find(GD_RIGHT);
	if (mKeyMapAni == mActionAni.end())
	{
		mapAni* tempMapAni = new mapAni;
		tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
		mActionAni.insert(make_pair(GD_RIGHT, tempMapAni));
	}
	else {
		mapAni* tempMapAni = mKeyMapAni->second;
		tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
	}

	auto mKeyMapOverlay = mActionOverlay.find(Player::eActionStat::WALK);
	if (mKeyMapOverlay == mActionOverlay.end())
	{
		vector<tagOverlayPosition> tempOP;
		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tagOverlayPosition tempOb(hairPtX[index], hairPtY[index], clothPtX[index], clothPtY[index]);
			tempOP.push_back(tempOb);

		}
		mActionOverlay.insert(make_pair(Player::eActionStat::WALK, tempOP));
	}
	}

	//run
	{
		int indexX[] = { 2,1,0,2,3 };
		int indexY[] = { 3,1,1,1,3 };

		float hairPtX[] = { 0,0,0,0,0 };
		float hairPtY[] = { 0,0,0,0,0 };

		float clothPtX[] = { 0,0,0,0,0 };
		float clothPtY[] = { 0,0,0,0,0 };

		vector<ImageGp*> tempV;

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index], indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 6, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 18, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		auto mKeyMapAni = mActionAni.find(GD_LEFT);
		if (mKeyMapAni == mActionAni.end())
		{
			mapAni* tempMapAni = new mapAni;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
			mActionAni.insert(make_pair(GD_LEFT, tempMapAni));
		}
		else {
			mapAni* tempMapAni = mKeyMapAni->second;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
		}
	}

	{

		int indexX[] = { 4,1,0,2,5 };
		int indexY[] = { 3,2,2,2,3 };

		float hairPtX[] = { 0,0,0,0,0 };
		float hairPtY[] = { 0,0,0,0,0 };

		float clothPtX[] = { 0,0,0,0,0 };
		float clothPtY[] = { 0,0,0,0,0 };

		vector<ImageGp*> tempV;

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index], indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 6, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 18, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		auto mKeyMapAni = mActionAni.find(GD_UP);
		if (mKeyMapAni == mActionAni.end())
		{
			mapAni* tempMapAni = new mapAni;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
			mActionAni.insert(make_pair(GD_UP, tempMapAni));
		}
		else {
			mapAni* tempMapAni = mKeyMapAni->second;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
		}
	}

	{

		int indexX[] = { 0,1,0,2,1 };
		int indexY[] = { 3,0,0,0,3 };

		float hairPtX[] = { 0,0,0,0,0 };
		float hairPtY[] = { 0,0,0,0,0 };

		float clothPtX[] = { 0,0,0,0,0 };
		float clothPtY[] = { 0,0,0,0,0 };

		vector<ImageGp*> tempV;

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index], indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 6, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 18, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempImageGp->flipX();
			tempV.push_back(tempImageGp);
		}

		auto mKeyMapAni = mActionAni.find(GD_DOWN);
		if (mKeyMapAni == mActionAni.end())
		{
			mapAni* tempMapAni = new mapAni;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
			mActionAni.insert(make_pair(GD_DOWN, tempMapAni));
		}
		else {
			mapAni* tempMapAni = mKeyMapAni->second;
			tempMapAni->insert(make_pair(Player::eActionStat::WALK, tempV));
		}
	}

	{
		int indexX[] = { 0,1,2,3,4 };
		int indexY[] = { 4,4,4,4,4};

		float hairPtX[] = { 0,0,0,0,0 };
		float hairPtY[] = { 0,0,0,0,0 };

		float clothPtX[] = { 0,0,0,0,0 };
		float clothPtY[] = { 0,0,0,0,0 };

		vector<ImageGp*> tempV;

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index], indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 12, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempV.push_back(tempImageGp);
		}

		for (int index = 0; index < 5; index++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(), mBaseSprite->getFrameBitmap(indexX[index] + 18, indexY[index]), PLAYER_WIDTH, PLAYER_HEIGHT);
			tempV.push_back(tempImageGp);
		}

		auto mKeyMapAni = mActionAni.find(GD_DOWN);
		if (mKeyMapAni == mActionAni.end())
		{
			mapAni* tempMapAni = new mapAni;
			tempMapAni->insert(make_pair(Player::eActionStat::ATTACK, tempV));
			mActionAni.insert(make_pair(GD_DOWN, tempMapAni));
		}
		else {
			mapAni* tempMapAni = mKeyMapAni->second;
			tempMapAni->insert(make_pair(Player::eActionStat::ATTACK, tempV));
		}

		auto mKeyMapOverlay = mActionOverlay.find(Player::eActionStat::ATTACK);
		if (mKeyMapOverlay == mActionOverlay.end())
		{
			vector<tagOverlayPosition> tempOP;
			for (int index = 0; index < 5; index++) {
				ImageGp* tempImageGp = new ImageGp;
				tagOverlayPosition tempOb(hairPtX[index], hairPtY[index], clothPtX[index], clothPtY[index]);
				tempOP.push_back(tempOb);

			}
			mActionOverlay.insert(make_pair(Player::eActionStat::ATTACK, tempOP));
		}
	}

	return S_OK;
}

vector<ImageGp*> PlayerSprite::getSpriteAction(eGameDirection direction, int stat)
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

vector<tagOverlayPosition> PlayerSprite::getOverayAction(int stat)
{
	auto mKeyMapOverlay = mActionOverlay.find(stat);
	if (mKeyMapOverlay != mActionOverlay.end())
	{
		return mKeyMapOverlay->second;
	}

	return vector<tagOverlayPosition>();
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
