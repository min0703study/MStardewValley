#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class EffectManager: public SingletonBase<EffectManager>, public GameNode
{
public:
	typedef struct tagEffectAni {
		vector<ImageGp*> mVAni;

		float AbsX;
		float AbsY;

		bool isLoop;
		bool isOneTimeOver;

		float CurFrame;
		float MaxFrame;

		float ElapsedSec;
		float FrameUpdateSec;
	} EffectAni;

	typedef struct tagEffectSound {
		string EffectKey;
	} EffectSound;

	HRESULT init();
	void playEffectAni(float x, float y, eEffectAniType type);
	void playEffectSound(eEffectSoundType type);

	void update();
	void render();
private:
	EffectAni mEffectAniList[eEffectAniType::EAT_END];
	EffectSound mEffectSoundList[eEffectSoundType::EST_END];

	vector<EffectAni> mVPlayingEffectAni;
	vector<EffectAni>::iterator miVPlayingEffectAni;

	vector<EffectSound> mVPlayingEffectSound;
	vector<EffectSound>::iterator miVPlayingEffectSound;

	ImageGp* mBaseSprite;
};

