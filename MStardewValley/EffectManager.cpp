#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init()
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->EffectSprite);

	EffectAni effect;
	effect.MaxFrame = 9;
	effect.CurFrame = 0;
	effect.ElapsedSec = 0;
	effect.FrameUpdateSec = 1.0f / 7.0f;

	for (int i = 0; i < effect.MaxFrame; i++) {
		ImageGp* tempEffectImg = new ImageGp;
		tempEffectImg->init(getMemDc(), mBaseSprite->getFrameBitmap(i, 13), TILE_SIZE, TILE_SIZE);
		effect.mVAni.push_back(tempEffectImg);
	}

	mEffectAniList[EAT_USE_WATERING_CAN] = effect;


	EffectAni effectWeed;
	effectWeed.MaxFrame = 9;
	effectWeed.CurFrame = 0;
	effectWeed.ElapsedSec = 0;
	effectWeed.FrameUpdateSec = 1.0f / 7.0f;

	for (int i = 0; i < effectWeed.MaxFrame; i++) {
		ImageGp* tempEffectImg = new ImageGp;
		tempEffectImg->init(getMemDc(), mBaseSprite->getFrameBitmap(i, 17), TILE_SIZE, TILE_SIZE);
		effectWeed.mVAni.push_back(tempEffectImg);
	}

	mEffectAniList[EAT_WEED_CRUSH] = effectWeed;

	EffectAni effectRock;
	effectRock.MaxFrame = 9;
	effectRock.CurFrame = 0;
	effectRock.ElapsedSec = 0;
	effectRock.FrameUpdateSec = 1.0f / 7.0f;

	for (int i = 0; i < effectRock.MaxFrame; i++) {
		ImageGp* tempEffectImg = new ImageGp;
		tempEffectImg->init(getMemDc(), mBaseSprite->getFrameBitmap(i, 12), TILE_SIZE, TILE_SIZE);
		effectRock.mVAni.push_back(tempEffectImg);
	}

	mEffectAniList[EAT_ROCK_CRUSH] = effectRock;

	EffectSound sound;

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

void EffectManager::playEffectAni(float x, float y, eEffectAniType type)
{
	EffectAni ani = mEffectAniList[type];
	ani.AbsX = x;
	ani.AbsY = y;
	ani.isOneTimeOver = false;
	mVPlayingEffectAni.push_back(ani);
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
	for (miVPlayingEffectAni = mVPlayingEffectAni.begin(); miVPlayingEffectAni != mVPlayingEffectAni.end();) {
		auto& eft = miVPlayingEffectAni;
		eft->ElapsedSec += TIMEMANAGER->getElapsedTime();

		if (eft->ElapsedSec > eft->FrameUpdateSec) {
			eft->ElapsedSec = 0;

			eft->CurFrame++;
			if (eft->CurFrame >= eft->MaxFrame) {
				eft->CurFrame = 0;
				eft->isOneTimeOver = true;
			}
		}

		if (eft->isOneTimeOver) {
			//mVPlayingEffectAni.erase(miVPlayingEffectAni++);
		}
		else {
			//++miVPlayingEffectAni;
		}
		++miVPlayingEffectAni;
	}
}

void EffectManager::render()
{
	for (miVPlayingEffectAni = mVPlayingEffectAni.begin(); miVPlayingEffectAni != mVPlayingEffectAni.end(); ++miVPlayingEffectAni) {
		if(!miVPlayingEffectAni->isOneTimeOver) miVPlayingEffectAni->mVAni[miVPlayingEffectAni->CurFrame]->render(miVPlayingEffectAni->AbsX, miVPlayingEffectAni->AbsY);
	}

	for (miVPlayingDamage = mVPlayingDamage.begin(); miVPlayingDamage != mVPlayingDamage.end(); ++miVPlayingDamage) {
		auto& damage = miVPlayingDamage;
		FONTMANAGER->drawText(getMemDc(), to_string(damage->Damage), damage->CurX, damage->CurY, 0 ,RGB(255,0,0));
	}
}
