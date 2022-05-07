#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init()
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->EffectSprite);

	EffectAni* effect = &mEffectAniList[EAT_ROCK_CRUSH];
	effect->AniType = EAT_ROCK_CRUSH;
	effect->StartX = 47;
	effect->MaxFrame = 9;
	effect->CurFrame = 0;
	effect->ElapsedSec = 0;
	effect->FrameUpdateSec = 1.0f / 7.0f;

	effect = &mEffectAniList[EAT_USE_WATERING_CAN];
	effect->AniType = EAT_USE_WATERING_CAN;
	effect->StartX = 13;
	effect->MaxFrame = 9;
	effect->CurFrame = 0;
	effect->ElapsedSec = 0;
	effect->FrameUpdateSec = 1.0f / 7.0f;

	effect = &mEffectAniList[EAT_WEED_CRUSH];
	effect->AniType = EAT_WEED_CRUSH;
	effect->StartX = 17;
	effect->MaxFrame = 9;
	effect->CurFrame = 0;
	effect->ElapsedSec = 0;
	effect->FrameUpdateSec = 1.0f / 7.0f;

	effect = &mEffectAniList[EAT_FURANCE_SMELTING];
	effect->AniType = EAT_FURANCE_SMELTING;
	effect->StartX = 30;
	effect->MaxFrame = 4;
	effect->CurFrame = 0;
	effect->ElapsedSec = 0;
	effect->FrameUpdateSec = 1.0f / 7.0f;

	for (int type = 0; type < EAT_END; type++) {
		for (int i = 0; i < mEffectAniList[type].MaxFrame; i++) {
			ImageGp* tempEffectImg = new ImageGp;
			tempEffectImg->init(getMemDc(), mBaseSprite->getFrameBitmap(i, mEffectAniList[type].StartX), TILE_SIZE, TILE_SIZE);
			tempEffectImg->rebuildChachedBitmap();

			mVEffectImg[type].push_back(tempEffectImg);
		}
	}

	mEffectSoundList[EST_WALK_WOOD].EffectKey = SOUNDCLASS->StepWood;
	mEffectSoundList[EST_WALK_NORMAL].EffectKey = SOUNDCLASS->StepSand;
	mEffectSoundList[EST_WALK_GRASS].EffectKey = SOUNDCLASS->StepGrassy;
	mEffectSoundList[EST_WALK_STONE].EffectKey = SOUNDCLASS->StepStone;
	mEffectSoundList[EST_ATTACK_ROCK].EffectKey = SOUNDCLASS->AttackRock;
	mEffectSoundList[EST_ATTACK_TREE].EffectKey = SOUNDCLASS->AttackTree;
	mEffectSoundList[EST_ATTACK_WEED].EffectKey = SOUNDCLASS->AttackWeed;
	mEffectSoundList[EST_USE_HOE].EffectKey = SOUNDCLASS->UseHoe;
	mEffectSoundList[EST_USE_WATERING_CAN].EffectKey = SOUNDCLASS->UseWateringCan;
	mEffectSoundList[EST_USE_WEAPON].EffectKey = SOUNDCLASS->UseWeapon;
	mEffectSoundList[EST_PICKUP_ITEM].EffectKey = SOUNDCLASS->PickUpItem;
	mEffectSoundList[EST_DOOR_OPEN].EffectKey = SOUNDCLASS->DoorOpen;
	mEffectSoundList[EST_MONSTER_DEAD].EffectKey = SOUNDCLASS->MonsterDead;
	mEffectSoundList[EST_PLAYER_HIT].EffectKey = SOUNDCLASS->MonsterDead;
	mEffectSoundList[EST_HARVESTING].EffectKey = SOUNDCLASS->Harvesting;
	mEffectSoundList[EST_LADDER_DOWN].EffectKey = SOUNDCLASS->LadderDown;

	return S_OK;
}

void EffectManager::playEffectOneTime(float absX, float absY, eEffectAniType type)
{
	EffectAni* ani = new EffectAni(mEffectAniList[type]);

	ani->AbsX = absX;
	ani->AbsY = absY;
	
	ani->isOneTimeOver = false;

	mVOneTimeEffectAni.push_back(ani);
}

int EffectManager::playEffectLoop(float absX, float absY, eEffectAniType type)
{
	int tempIndex = RND->getInt(100);
	auto key = mLoopEffectAniList.find(tempIndex);

	EffectAni* ani = new EffectAni(mEffectAniList[type]);

	ani->AbsX = absX;
	ani->AbsY = absY;

	mLoopEffectAniList.insert(make_pair(tempIndex, ani));
	return tempIndex;
}
void EffectManager::pauseEffectLoop(int key)
{
	auto effectKey = mLoopEffectAniList.find(key);

	if (effectKey != mLoopEffectAniList.end()) {
		effectKey->second->IsPause = true;
	};
}
void EffectManager::resumeEffectLoop(int key)
{
	auto effectKey = mLoopEffectAniList.find(key);

	if (effectKey != mLoopEffectAniList.end()) {
		effectKey->second->IsPause = false;
	};
}
void EffectManager::stopEffectLoop(int key)
{
	auto effectKey = mLoopEffectAniList.find(key);

	if (effectKey != mLoopEffectAniList.end()) {
		mLoopEffectAniList.erase(key);
	};
}

bool EffectManager::isPauseAni(int key)
{
	auto effectKey = mLoopEffectAniList.find(key);

	if (effectKey != mLoopEffectAniList.end()) {
		return effectKey->second->IsPause;
	};
}

void EffectManager::playEffectDemage(float x, float y, int damage)
{
	mVPlayingDamage.push_back(EffectDamage(damage, x, y));
}


void EffectManager::playEffectSound(eEffectSoundType type)
{
	SOUNDMANAGER->play(mEffectSoundList[type].EffectKey);
}

void EffectManager::playRegularSound(eEffectSoundType type) {
	if (!SOUNDMANAGER->isPlaySound(mEffectSoundList[type].EffectKey)) {
		SOUNDMANAGER->play(mEffectSoundList[type].EffectKey);
	}
}

void EffectManager::update()
{
	for (miVOneTimeEffectAni = mVOneTimeEffectAni.begin(); miVOneTimeEffectAni != mVOneTimeEffectAni.end();) {
		(*miVOneTimeEffectAni)->ElapsedSec += TIMEMANAGER->getElapsedTime();

		if ((*miVOneTimeEffectAni)->ElapsedSec > (*miVOneTimeEffectAni)->FrameUpdateSec) {
			(*miVOneTimeEffectAni)->ElapsedSec = 0;

			(*miVOneTimeEffectAni)->CurFrame++;
			if ((*miVOneTimeEffectAni)->CurFrame >= (*miVOneTimeEffectAni)->MaxFrame) {
				(*miVOneTimeEffectAni)->isOneTimeOver = true;
			}
		}

		if ((*miVOneTimeEffectAni)->isOneTimeOver) {
			SAFE_DELETE(*miVOneTimeEffectAni);
			miVOneTimeEffectAni = mVOneTimeEffectAni.erase(miVOneTimeEffectAni);
		} else {
			++miVOneTimeEffectAni;
		}
	}

	for (miVLoopEffectAni = mLoopEffectAniList.begin(); miVLoopEffectAni != mLoopEffectAniList.end();++miVLoopEffectAni) {
		if (miVLoopEffectAni->second->IsPause) continue;
		auto ani = miVLoopEffectAni->second;
		ani->ElapsedSec += TIMEMANAGER->getElapsedTime();

		if (ani->ElapsedSec > ani->FrameUpdateSec) {
			ani->ElapsedSec = 0;

			ani->CurFrame++;
			if (ani->CurFrame >= ani->MaxFrame) {
				ani->CurFrame = 0;
			}
		}
	}
}

void EffectManager::render()
{
	for (miVOneTimeEffectAni = mVOneTimeEffectAni.begin(); miVOneTimeEffectAni != mVOneTimeEffectAni.end(); ++miVOneTimeEffectAni) {
		auto ani = *miVOneTimeEffectAni;
		if (!ani->isOneTimeOver) {
			mVEffectImg[ani->AniType][ani->CurFrame]->render(ani->AbsX - CAMERA->getX(), ani->AbsY - CAMERA->getY());
		}
	}
	for (miVLoopEffectAni = mLoopEffectAniList.begin(); miVLoopEffectAni != mLoopEffectAniList.end(); ++miVLoopEffectAni) {
		if (miVLoopEffectAni->second->IsPause) continue;
		auto ani = miVLoopEffectAni->second;
		mVEffectImg[ani->AniType][ani->CurFrame]->render(ani->AbsX - CAMERA->getX(), ani->AbsY - CAMERA->getY());
	}
	for (miVPlayingDamage = mVPlayingDamage.begin(); miVPlayingDamage != mVPlayingDamage.end(); ++miVPlayingDamage) {
		auto& damage = miVPlayingDamage;
		FONTMANAGER->drawText(getMemDc(), to_string(damage->Damage), damage->CurX, damage->CurY, 0 ,RGB(255,0,0));
	}
}
