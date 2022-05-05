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

	typedef struct tagEffectDamage {
		const int Damage;

		float Gravity;
		int AniDirection;

		bool IsEndAni;
		
		float CurX;
		float CurY;

		tagEffectDamage(const int damage, float curX, float curY) : Damage(damage), Gravity(4.0f), CurX(curX), CurY(curY), IsEndAni(false) {};
			
	} EffectDamage;

	HRESULT init();
	void playEffectAni(float x, float y, eEffectAniType type);
	void playEffectDemage(float x, float y, int damage);
	void playEffectSound(eEffectSoundType type);

	void playRegularSound(eEffectSoundType type);

	void update();
	void render();
private:
	EffectAni mEffectAniList[eEffectAniType::EAT_END];
	EffectSound mEffectSoundList[eEffectSoundType::EST_END];

	vector<EffectAni> mVPlayingEffectAni;
	vector<EffectAni>::iterator miVPlayingEffectAni;

	vector<EffectSound> mVPlayingEffectSound;
	vector<EffectSound>::iterator miVPlayingEffectSound;

	vector<EffectDamage> mVPlayingDamage;
	vector<EffectDamage>::iterator miVPlayingDamage;

	ImageGp* mBaseSprite;
};
