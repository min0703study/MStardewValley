#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init()
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->EffectSprite);

	for (int i = 0; i < 7; i++) {
		ImageGp* tempEffectImg = new ImageGp;
		tempEffectImg->init(getMemDc(), mBaseSprite->getFrameBitmap(i, 7));
		mVAllEffectAni[eEffectAniType::EAT_ROCK_CRUSH].push_back(tempEffectImg);
	}

	EffectAni effect;
	effect.Type = eEffectAniType::EAT_ROCK_CRUSH;
	effect.MaxFrame = 7;
	effect.CurFrame = 0;
	effect.ElapsedSec = 0;
	effect.FrameUpdateSec = 1.0f/ 7.0f;

	mVEffectAni->push_back(effect);

	EffectSound sound;
	
	mVAllEffectSound->push_back(SOUNDCLASS->StepWood);
	return S_OK;
}

void EffectManager::playEffectOneTime(float x, float y, eEffectAniType type)
{
}

void EffectManager::update()
{
	for (miVPlayingEffectAni = mVPlayingEffectAni.begin(); miVPlayingEffectAni != mVPlayingEffectAni.end(); ++miVPlayingEffectAni) {
		auto& eft = miVPlayingEffectAni;
		eft->ElapsedSec += TIMEMANAGER->getElapsedTime();

		if (eft->ElapsedSec > eft->FrameUpdateSec) {
			eft->ElapsedSec = 0;

			eft->CurFrame++;
			if (eft->CurFrame >= eft->MaxFrame) {
				eft->CurFrame = 0;
			}
		}
	}
}

void EffectManager::render()
{
	for (miVPlayingEffectAni = mVPlayingEffectAni.begin(); miVPlayingEffectAni != mVPlayingEffectAni.end(); ++miVPlayingEffectAni) {
		mVAllEffectAni[miVPlayingEffectAni->Type][miVPlayingEffectAni->CurFrame]->render(miVPlayingEffectAni->AbsX, miVPlayingEffectAni->AbsY);
	}

	if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->StepWood)) {
		SOUNDMANAGER->play(SOUNDCLASS->StepWood);
	};
}
