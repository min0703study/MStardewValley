#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class EffectManager: public SingletonBase<EffectManager>, public GameNode
{
public:
	typedef struct tagEffectAni {
		eEffectAniType Type;
		float AbsX;
		float AbsY;

		bool isLoop;
		bool isOver;

		float CurFrame;
		float MaxFrame;

		float ElapsedSec;
		float FrameUpdateSec;

	} EffectAni;

	typedef struct tagEffectSound {
		eEffectSoundType Type;

	} EffectSound;

	HRESULT init();
	void playEffectOneTime(float x, float y, eEffectAniType type);
	void update();
	void render();
private:
	vector<ImageGp*> mVAllEffectAni[eEffectAniType::EAT_END];
	vector<string> mVAllEffectSound[eEffectSoundType::EST_END];

	vector<EffectAni> mVEffectAni[eEffectAniType::EAT_END];
	vector<EffectSound> mVEffectSound[eEffectSoundType::EST_END];

	vector<EffectAni> mVPlayingEffectAni;
	vector<EffectAni>::iterator miVPlayingEffectAni;

	vector<EffectSound> mVPlayingEffectSound;
	vector<EffectSound>::iterator miVPlayingEffectSound;

	ImageGp* mBaseSprite;
};

